/* GLib Extra - Tentative GLib code and GLib supplements
 * Copyright (C) 1997-2002 Tim Janik
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
#ifndef __SFI_GLIB_EXTRA_H__
#define __SFI_GLIB_EXTRA_H__

#define	__G_SCANNER_H__	/* prevent inclusion of pre-2.0.7 GLib GScanner */
#include	<glib.h>
#include	<glib-object.h>


G_BEGIN_DECLS


/* --- macros --- */
#if (GLIB_SIZEOF_LONG > 4)
#define G_HASH_LONG(l)	((l) + ((l) >> 32))
#else
#define G_HASH_LONG(l)	(l)
#endif


/* --- provide (historic) aliases --- */
#define	g_string_printfa	g_string_append_printf
#define	g_string_aprintf	g_string_append_printf
#define	g_scanner_add_symbol( scanner, symbol, value )	G_STMT_START { \
  g_scanner_scope_add_symbol ((scanner), 0, (symbol), (value)); \
} G_STMT_END
#define	g_scanner_remove_symbol( scanner, symbol )	G_STMT_START { \
  g_scanner_scope_remove_symbol ((scanner), 0, (symbol)); \
} G_STMT_END


/* --- abandon typesafety for some frequently used functions --- */
#define g_object_notify(o,s)		  g_object_notify ((gpointer) o, s)
#define	g_object_get_qdata(o,q)		  g_object_get_qdata ((gpointer) o, q)
#define	g_object_set_qdata(o,q,d)	  g_object_set_qdata ((gpointer) o, q, d)
#define	g_object_set_qdata_full(o,q,d,f)  g_object_set_qdata_full ((gpointer) o, q, d, (gpointer) f)
#define	g_object_steal_qdata(o,q)	  g_object_steal_qdata ((gpointer) o, q)
#define	g_object_get_data(o,k)		  g_object_get_data ((gpointer) o, k)
#define	g_object_set_data(o,k,d)	  g_object_set_data ((gpointer) o, k, d)
#define	g_object_set_data_full(o,k,d,f)	  g_object_set_data_full ((gpointer) o, k, d, (gpointer) f)
#define	g_object_steal_data(o,k)	  g_object_steal_data ((gpointer) o, k)


/* --- string functions --- */
gchar**		g_straddv	  (gchar	**str_array,
				   const gchar	 *new_str);
gchar**		g_strslistv	  (GSList	 *slist);
guint		g_strlenv	  (gchar	**str_array);
gchar*		g_strdup_stripped (const gchar	 *string);
gchar*		g_strdup_rstrip   (const gchar	 *string);
gchar*		g_strdup_lstrip   (const gchar	 *string);
     

/* --- list extensions --- */
gpointer	g_slist_pop_head	(GSList	     **slist_p);
gpointer	g_list_pop_head		(GList	     **list_p);
GSList*		g_slist_append_uniq	(GSList	      *slist,
					 gpointer      data);
void            g_slist_free_deep       (GSList	      *slist,
					 GDestroyNotify data_destroy);
void            g_list_free_deep        (GList	       *list,
					 GDestroyNotify data_destroy);


/* --- name conversions --- */
gchar*  g_type_name_to_cname            (const gchar    *type_name);
gchar*  g_type_name_to_sname            (const gchar    *type_name);
gchar*  g_type_name_to_cupper           (const gchar    *type_name);
gchar*  g_type_name_to_type_macro       (const gchar    *type_name);


/* --- simple main loop source --- */
typedef gboolean (*GSourcePending)  (gpointer	 data,
				     gint	*timeout);
typedef void     (*GSourceDispatch) (gpointer	 data);
GSource*	g_source_simple	(gint		 priority,
				 GSourcePending  pending,
				 GSourceDispatch dispatch,
				 gpointer	 data,
				 GDestroyNotify	 destroy,
				 GPollFD	*first_pfd,
				 ...);


/* --- unix signal queue --- */
#if 0
typedef gboolean (*GUSignalFunc) (gint8          usignal,
			 	  gpointer       data);
guint   g_usignal_add            (gint8          usignal,
				  GUSignalFunc   function,
				  gpointer       data);
guint   g_usignal_add_full       (gint           priority,
				  gint8          usignal,
				  GUSignalFunc   function,
				  gpointer       data,
				  GDestroyNotify destroy);
void    g_usignal_notify         (gint8          usignal);
#endif


/* --- FIXME: roll our own 64Bit GScanner --- */
typedef struct _GScanner	GScanner;
typedef struct _GScannerConfig	GScannerConfig;
typedef union  _GTokenValue     GTokenValue;
typedef void		(*GScannerMsgFunc)	(GScanner      *scanner,
						 gchar	       *message,
						 gboolean	error);
#define G_CSET_A_2_Z	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define G_CSET_a_2_z	"abcdefghijklmnopqrstuvwxyz"
#define G_CSET_DIGITS	"0123456789"
#define G_CSET_LATINC	"\300\301\302\303\304\305\306"\
			"\307\310\311\312\313\314\315\316\317\320"\
			"\321\322\323\324\325\326"\
			"\330\331\332\333\334\335\336"
#define G_CSET_LATINS	"\337\340\341\342\343\344\345\346"\
			"\347\350\351\352\353\354\355\356\357\360"\
			"\361\362\363\364\365\366"\
			"\370\371\372\373\374\375\376\377"
typedef enum
{
  G_ERR_UNKNOWN,
  G_ERR_UNEXP_EOF,
  G_ERR_UNEXP_EOF_IN_STRING,
  G_ERR_UNEXP_EOF_IN_COMMENT,
  G_ERR_NON_DIGIT_IN_CONST,
  G_ERR_DIGIT_RADIX,
  G_ERR_FLOAT_RADIX,
  G_ERR_FLOAT_MALFORMED
} GErrorType;
typedef enum
{
  G_TOKEN_EOF			=   0,
  
  G_TOKEN_LEFT_PAREN		= '(',
  G_TOKEN_RIGHT_PAREN		= ')',
  G_TOKEN_LEFT_CURLY		= '{',
  G_TOKEN_RIGHT_CURLY		= '}',
  G_TOKEN_LEFT_BRACE		= '[',
  G_TOKEN_RIGHT_BRACE		= ']',
  G_TOKEN_EQUAL_SIGN		= '=',
  G_TOKEN_COMMA			= ',',
  
  G_TOKEN_NONE			= 256,
  
  G_TOKEN_ERROR,
  
  G_TOKEN_CHAR,
  G_TOKEN_BINARY,
  G_TOKEN_OCTAL,
  G_TOKEN_INT,
  G_TOKEN_HEX,
  G_TOKEN_FLOAT,
  G_TOKEN_STRING,
  
  G_TOKEN_SYMBOL,
  G_TOKEN_IDENTIFIER,
  G_TOKEN_IDENTIFIER_NULL,
  
  G_TOKEN_COMMENT_SINGLE,
  G_TOKEN_COMMENT_MULTI,
  G_TOKEN_LAST
} GTokenType;
union	_GTokenValue
{
  gpointer	v_symbol;
  gchar		*v_identifier;
  gulong	v_binary;
  gulong	v_octal;
  gulong	v_int;
  guint64	v_int64;
  gdouble	v_float;
  gulong	v_hex;
  gchar		*v_string;
  gchar		*v_comment;
  guchar	v_char;
  guint		v_error;
};
struct	_GScannerConfig
{
  /* Character sets
   */
  gchar		*cset_skip_characters;		/* default: " \t\n" */
  gchar		*cset_identifier_first;
  gchar		*cset_identifier_nth;
  gchar		*cpair_comment_single;		/* default: "#\n" */
  
  /* Should symbol lookup work case sensitive?
   */
  guint		case_sensitive : 1;
  
  /* Boolean values to be adjusted "on the fly"
   * to configure scanning behaviour.
   */
  guint		skip_comment_multi : 1;		/* C like comment */
  guint		skip_comment_single : 1;	/* single line comment */
  guint		scan_comment_multi : 1;		/* scan multi line comments? */
  guint		scan_identifier : 1;
  guint		scan_identifier_1char : 1;
  guint		scan_identifier_NULL : 1;
  guint		scan_symbols : 1;
  guint		scan_binary : 1;
  guint		scan_octal : 1;
  guint		scan_float : 1;
  guint		scan_hex : 1;			/* `0x0ff0' */
  guint		scan_hex_dollar : 1;		/* `$0ff0' */
  guint		scan_string_sq : 1;		/* string: 'anything' */
  guint		scan_string_dq : 1;		/* string: "\\-escapes!\n" */
  guint		numbers_2_int : 1;		/* bin, octal, hex => int */
  guint		int_2_float : 1;		/* int => G_TOKEN_FLOAT? */
  guint		identifier_2_string : 1;
  guint		char_2_token : 1;		/* return G_TOKEN_CHAR? */
  guint		symbol_2_token : 1;
  guint		scope_0_fallback : 1;		/* try scope 0 on lookups? */
  guint		store_int64 : 1;
  guint		padding_dummy;
};
struct	_GScanner
{
  gpointer		user_data;
  guint			max_parse_errors;
  guint			parse_errors;
  const gchar		*input_name;
  GData			*qdata;
  GScannerConfig	*config;
  GTokenType		token;
  GTokenValue		value;
  guint			line;
  guint			position;
  GTokenType		next_token;
  GTokenValue		next_value;
  guint			next_line;
  guint			next_position;
  GHashTable		*symbol_table;
  gint			input_fd;
  const gchar		*text;
  const gchar		*text_end;
  gchar			*buffer;
  guint			scope_id;
  GScannerMsgFunc	msg_handler;
};
GScanner*	g_scanner_new			(const GScannerConfig *config_templ);
void		g_scanner_destroy		(GScanner	*scanner);
void		g_scanner_input_file		(GScanner	*scanner,
						 gint		input_fd);
void		g_scanner_sync_file_offset	(GScanner	*scanner);
void		g_scanner_input_text		(GScanner	*scanner,
						 const	gchar	*text,
						 guint		text_len);
GTokenType	g_scanner_get_next_token	(GScanner	*scanner);
GTokenType	g_scanner_peek_next_token	(GScanner	*scanner);
GTokenType	g_scanner_cur_token		(GScanner	*scanner);
GTokenValue	g_scanner_cur_value		(GScanner	*scanner);
guint		g_scanner_cur_line		(GScanner	*scanner);
guint		g_scanner_cur_position		(GScanner	*scanner);
gboolean	g_scanner_eof			(GScanner	*scanner);
guint		g_scanner_set_scope		(GScanner	*scanner,
						 guint		 scope_id);
void		g_scanner_scope_add_symbol	(GScanner	*scanner,
						 guint		 scope_id,
						 const gchar	*symbol,
						 gpointer	value);
void		g_scanner_scope_remove_symbol	(GScanner	*scanner,
						 guint		 scope_id,
						 const gchar	*symbol);
gpointer	g_scanner_scope_lookup_symbol	(GScanner	*scanner,
						 guint		 scope_id,
						 const gchar	*symbol);
void		g_scanner_scope_foreach_symbol	(GScanner	*scanner,
						 guint		 scope_id,
						 GHFunc		 func,
						 gpointer	 user_data);
gpointer	g_scanner_lookup_symbol		(GScanner	*scanner,
						 const gchar	*symbol);
void		g_scanner_unexp_token		(GScanner	*scanner,
						 GTokenType	expected_token,
						 const gchar	*identifier_spec,
						 const gchar	*symbol_spec,
						 const gchar	*symbol_name,
						 const gchar	*message,
						 gint		 is_error);
void		g_scanner_error			(GScanner	*scanner,
						 const gchar	*format,
						 ...) G_GNUC_PRINTF (2,3);
void		g_scanner_warn			(GScanner	*scanner,
						 const gchar	*format,
						 ...) G_GNUC_PRINTF (2,3);

#ifndef G_DISABLE_DEPRECATED
#define		g_scanner_add_symbol( scanner, symbol, value )	G_STMT_START { \
  g_scanner_scope_add_symbol ((scanner), 0, (symbol), (value)); \
} G_STMT_END
#define		g_scanner_remove_symbol( scanner, symbol )	G_STMT_START { \
  g_scanner_scope_remove_symbol ((scanner), 0, (symbol)); \
} G_STMT_END
#define		g_scanner_foreach_symbol( scanner, func, data )	G_STMT_START { \
  g_scanner_scope_foreach_symbol ((scanner), 0, (func), (data)); \
} G_STMT_END
#define g_scanner_freeze_symbol_table(scanner) ((void)0)
#define g_scanner_thaw_symbol_table(scanner) ((void)0)
#endif /* G_DISABLE_DEPRECATED */


G_END_DECLS

#endif /* __SFI_GLIB_EXTRA_H__ */
