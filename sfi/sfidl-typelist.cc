/* SFI - Synthesis Fusion Kit Interface                 -*-mode: c++;-*-
 * Copyright (C) 2004 Stefan Westerfeld
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

#include "sfidl-typelist.h"
#include "sfidl-factory.h"

using namespace Sfidl;
using namespace std;

namespace {

class TypeListFactory : public Factory {
public:
  string option() const	      { return "--list-types"; }
  string description() const  { return "print all types defined in the idlfile"; }
  
  void init (Options& options) const
  {
    options.doImplementation = true;
    options.doInterface = false;
    options.doHeader = true;
    options.doSource = false;
  }
  
  CodeGenerator *create (const Parser& parser) const
  {
    return new CodeGeneratorTypeList (parser);
  }
} typelist_factory;

} // anon

/* vim:set ts=8 sts=2 sw=2: */