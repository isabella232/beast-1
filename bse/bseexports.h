/* BSE - Bedevilled Sound Engine
 * Copyright (C) 1998, 1999 Olaf Hoehmann and Tim Janik
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.
 *
 * bseexports.h: export declarations for external plugins
 */
#ifndef __BSE_EXPORTS_H__
#define __BSE_EXPORTS_H__

#include	<bse/bseprocedure.h>
#include	<bse/bseconfig.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



/* --- plugin export macros --- */
/* (implementations reside in bseplugin.h) */
/* start export section,
 * provide a unique plugin here
 */
#define BSE_EXPORTS_BEGIN(UniqueName)   BSE_EXPORT_IMPL_B (UniqueName)
/* list procedure types as BseExportProcedure array
 */
#define BSE_EXPORT_PROCEDURES           BSE_EXPORT_IMPL_A (Procedure)
/* list object types as BseExportObject array
 */
#define BSE_EXPORT_OBJECTS              BSE_EXPORT_IMPL_A (Object)
/* list enum types as BseExportEnum array
 */
#define BSE_EXPORT_STATIC_ENUMS		static const BseExportEnum \
                                        BSE_EXPORT_IMPL_S (MkEnums_built) []
#define BSE_EXPORT_AND_GENERATE_ENUMS() BSE_EXPORT_IMPL_P (Enum) = \
                                        BSE_EXPORT_IMPL_S (MkEnums_built)
/* end export section
 */
#define BSE_EXPORTS_END                 BSE_EXPORT_IMPL_E


/* --- typedefs --- */
typedef const gchar*                        BseExportBegin;
typedef union  _BseExportSpec               BseExportSpec;
typedef struct _BseExportAny                BseExportAny;
typedef struct _BseExportObject             BseExportObject;
typedef struct _BseExportEnum               BseExportEnum;
typedef struct _BseExportProcedure     	    BseExportProcedure;
typedef guint                               BseExportEnd;
typedef void         (*BseProcedureInit)   (BseProcedureClass *proc,
					    BseParamSpec     **ipspecs,
					    BseParamSpec     **opspecs);
typedef void         (*BseProcedureUnload) (BseProcedureClass *procedure);


/* --- export types --- */
typedef enum			/*< skip >*/
{
  BSE_EXPORT_TYPE_PROCS		= 1,
  BSE_EXPORT_TYPE_OBJECTS	= 2,
  BSE_EXPORT_TYPE_ENUMS		= 3
} BseExportType;


/* --- export declarations --- */
struct _BseExportAny
{
  GType              *type_p;
  const gchar  	     *name;
};
struct _BseExportProcedure
{
  GType              *type_p;	   /* obligatory */
  const gchar  	     *name;	   /* obligatory */
  const gchar  	     *blurb;	   /* optional */
  const guint  	      private_id;  /* optional */

  BseProcedureInit    init;	   /* obligatory */
  BseProcedureExec    exec;	   /* obligatory */
  BseProcedureUnload  unload;	   /* optional */
  
  const gchar  	     *category;	   /* recommended */
  const BsePixdata    pixdata;     /* optional */
};
struct _BseExportObject
{
  GType              *type_p;	   /* obligatory */
  const gchar  	     *name;	   /* obligatory */
  const gchar  	     *parent_type; /* obligatory */
  const gchar  	     *blurb;	   /* optional */

  const GTypeInfo  *object_info; /* obligatory */

  const gchar  	     *category;	   /* recommended */
  const BsePixdata    pixdata;     /* optional */
};
struct _BseExportEnum
{
  GType              *type_p;	   /* obligatory */
  const gchar  	     *name;	   /* obligatory */
  GType               parent_type; /* obligatory */
  gpointer            values;      /* obligatory */
};


/* --- export union --- */
union _BseExportSpec
{
  GType  		 *type_p; /* common to all members */
  BseExportAny		  any;
  BseExportProcedure	  s_proc;
  BseExportObject	  s_object;
  BseExportEnum		  s_enum;
};


/* --- internal prototypes --- */
void	bse_procedure_complete_info	(const BseExportSpec *spec,
					 GTypeInfo         *info);
void	bse_object_complete_info	(const BseExportSpec *spec,
					 GTypeInfo         *info);
void	bse_enum_complete_info		(const BseExportSpec *spec,
					 GTypeInfo         *info);





#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __BSE_EXPORTS_H__ */
