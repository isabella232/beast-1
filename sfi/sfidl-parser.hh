/* SFI - Synthesis Fusion Kit Interface
 * Copyright (C) 2002 Stefan Westerfeld
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef _SFIDL_PARSER_H_
#define _SFIDL_PARSER_H_

#include <sfi/glib-extra.h>
#include <vector>
#include <map>
#include <string>

namespace Sfidl {

/* we implement a get() function since operator[] is not const */
template<typename Key, typename Value>
class Map : public std::map<Key,Value> {
private:
  Value default_value;

public:
  const Value& get(const Key& k) const {
    typename std::map<Key,Value>::const_iterator i = find(k);
    if (i != end())
      return i->second;
    else
      return default_value;
  }
};

/*
 * internationalized string: can store a conventional string,
 * however it can also store whether the string was given in
 * conventional form    "foo"     (i18n = false)
 * on in the i18n form  _("foo")  (i18n = true)
 */
class IString : public std::string {
public:
  bool i18n;

  IString() : i18n (false) {
  }
  
  IString(const char *str) : std::string (str), i18n (false) {
  }

  /* produces an escaped version "foo" or _("foo") */
  std::string escaped () const
  {
    std::string result;
    char *x = g_strescape (c_str(), 0);
    if (i18n)
      result = "_(\"" + std::string(x) + "\")";
    else
      result = "\"" + std::string(x) + "\"";
    g_free (x);
    return result;
  }
};

struct LineInfo {
  bool isInclude;
  int line;
  std::string filename;
};

struct Constant {
  std::string name;
  std::string file;
  enum { tString = 1, tFloat = 2, tInt = 3 } type;

  std::string str;
  float f;
  int i;
};

struct Param {
  std::string type;
  std::string name;
  std::string file;
  
  IString     group;
  std::string pspec;
  int         line;
  std::string args;
};

struct Stream {
  enum Type { IStream, JStream, OStream } type;
  std::string ident;
  IString     name;
  std::string file;
  IString     blurb;
  int         line;
};
 
struct ChoiceValue {
  std::string name;
  std::string file;
  std::string text;
  
  int         value;
  int         sequentialValue;
  bool        neutral;
};

struct Choice {
  /*
   * name if the enum, "_anonymous_" for anonymous enum - of course, when
   * using namespaces, this can also lead to things like "Arts::_anonymous_",
   * which would mean an anonymous enum in the Arts namespace
   */
  std::string name;
  std::string file;
  
  std::vector<ChoiceValue> contents;
  Map<std::string, IString> infos;
};

struct Record {
  std::string name;
  std::string file;
  
  std::vector<Param> contents;
  Map<std::string, IString> infos;
};

struct Sequence {
  std::string name;
  std::string file;
  Param content;
  Map<std::string, IString> infos;
};

struct Method {
  std::string name;
  std::string file;
  
  std::vector<Param> params;
  Param result;
  Map<std::string, IString> infos;
};

struct Class {
  std::string name;
  std::string file;
  std::string inherits;
  
  std::vector<Method> methods;
  std::vector<Method> signals;
  std::vector<Param> properties;
  std::vector<Stream> istreams, jstreams, ostreams;
  Map<std::string, IString> infos;
};

enum TypeDeclaration {
  tdChoice        = 1,
  tdRecord        = 2,
  tdSequence      = 3,
  tdClass         = 4,
  tdProto         = 8,
  tdChoiceProto   = tdChoice | tdProto,
  tdRecordProto   = tdRecord | tdProto,
  tdSequenceProto = tdSequence | tdProto,
  tdClassProto    = tdClass | tdProto,
};

enum Type {
  // primitive types
  VOID,
  BOOL,
  INT,
  NUM,
  REAL,
  STRING,
  // enums
  CHOICE,
  // blocks of byte/float
  BBLOCK,
  FBLOCK,
  // generic types: param spec, record
  PSPEC,
  REC,
  // user defined types
  SEQUENCE,
  RECORD,
  OBJECT,     /* PROXY */
};

class Parser {
protected:
  const class Options&      options;

  GScanner                 *scanner;
  std::vector<char>         scannerInputData;
  std::vector<LineInfo>     scannerLineInfo;

  std::vector<std::string>  includedNames;
  std::vector<std::string>  types;
  std::map<std::string,int> typeMap;

  std::vector<std::string>  includes;          // files to include
  std::vector<Constant>	    constants;
  std::vector<Choice>	    choices;
  std::vector<Sequence>	    sequences;
  std::vector<Record>	    records;
  std::vector<Class>	    classes;
  std::vector<Method>	    procedures;
  
  static void scannerMsgHandler (GScanner *scanner, gchar *message, gboolean is_error);
  void printError (const gchar *format, ...);

  void preprocess (const std::string& filename);
  bool haveIncluded (const std::string& filename) const;
  bool insideInclude () const;
  
  void addConstantTodo(const Constant& cdef);
  void addChoiceTodo(const Choice& cdef);
  void addRecordTodo(const Record& rdef);
  void addSequenceTodo(const Sequence& sdef);
  void addClassTodo(const Class& cdef);
  void addProcedureTodo(const Method& pdef);

  void addPrototype (const std::string& type, TypeDeclaration typeDecl);
  void addType (const std::string& type, TypeDeclaration typeDecl);

  GTokenType parseTypeName (std::string& s);
  GTokenType parseStringOrConst (std::string &s);
  GTokenType parseConstant ();
  GTokenType parseNamespace ();
  GTokenType parseChoice ();
  GTokenType parseChoiceValue (ChoiceValue& comp, int& value, int& sequentialValue);
  GTokenType parseRecord ();
  GTokenType parseRecordField (Param& comp, const IString& group);
  GTokenType parseStream (Stream& stream, Stream::Type);
  GTokenType parseSequence ();
  GTokenType parseParamHints (Param &def);
  GTokenType parseClass ();
  GTokenType parseMethod (Method& def);
  GTokenType parseInfoOptional (Map<std::string,IString>& infos);
public:
  Parser ();
  
  bool parse (const std::string& fileName);
 
  std::string fileName() const				  { return scanner->input_name; }
  const std::vector<std::string>& getIncludes () const	  { return includes; }
  const std::vector<Constant>& getConstants () const	  { return constants; }
  const std::vector<Choice>& getChoices () const	  { return choices; }
  const std::vector<Sequence>& getSequences () const	  { return sequences; }
  const std::vector<Record>& getRecords () const	  { return records; }
  const std::vector<Class>& getClasses () const 	  { return classes; }
  const std::vector<Method>& getProcedures () const	  { return procedures; }
  const std::vector<std::string>& getTypes () const       { return types; }
  
  Sequence findSequence (const std::string& name) const;
  Record findRecord (const std::string& name) const;
  
  bool isChoice(const std::string& type) const;
  bool isSequence(const std::string& type) const;
  bool isRecord(const std::string& type) const;
  bool isClass(const std::string& type) const;
  Type typeOf(const std::string& type) const;
  bool fromInclude(const std::string& type) const;
};

}
#endif /* _SFIDL_PARSER_H_ */

/* vim:set ts=8 sts=2 sw=2: */
