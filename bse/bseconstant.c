/* BseConstant - BSE Constant
 * Copyright (C) 1999-2002 Tim Janik
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
#include "bseconstant.h"

#include <bse/bsecategories.h>
#include <bse/gslengine.h>

#define	BSE_DFL_CONSTANT_VOLUME_dB	(BSE_DFL_MASTER_VOLUME_dB)

/* --- parameters --- */
enum
{
  PARAM_0,
  /* don't add params after here */
  PARAM_VALUE,
  PARAM_FREQ,
  PARAM_NOTE
};


/* --- prototypes --- */
static void	 bse_constant_init		(BseConstant	  *constant);
static void	 bse_constant_class_init	(BseConstantClass *class);
static void	 bse_constant_set_property	(GObject	  *object,
						 guint             param_id,
						 const GValue     *value,
						 GParamSpec       *pspec);
static void	 bse_constant_get_property	(GObject	  *object,
						 guint             param_id,
						 GValue           *value,
						 GParamSpec       *pspec);
static void	 bse_constant_context_create	(BseSource        *source,
						 guint             context_handle,
						 GslTrans         *trans);
static void	 bse_constant_update_modules	(BseConstant	  *constant,
						 GslTrans         *trans);


/* --- variables --- */
static gpointer	       parent_class = NULL;


/* --- functions --- */
#include "./icons/const.c"
BSE_BUILTIN_TYPE (BseConstant)
{
  static const GTypeInfo type_info = {
    sizeof (BseConstantClass),
    
    (GBaseInitFunc) NULL,
    (GBaseFinalizeFunc) NULL,
    (GClassInitFunc) bse_constant_class_init,
    (GClassFinalizeFunc) NULL,
    NULL /* class_data */,
    
    sizeof (BseConstant),
    0 /* n_preallocs */,
    (GInstanceInitFunc) bse_constant_init,
  };
  BsePixdata icon = {
    CONST_IMAGE_BYTES_PER_PIXEL | BSE_PIXDATA_1BYTE_RLE,
    CONST_IMAGE_WIDTH, CONST_IMAGE_HEIGHT,
    CONST_IMAGE_RLE_PIXEL_DATA,
  };
  GType type_id;
  
  type_id = bse_type_register_static (BSE_TYPE_SOURCE,
				      "BseConstant",
				      "This module provides constant signal outputs",
				      &type_info);
  bse_categories_register_icon ("/Modules/Other Sources/Constant", type_id, &icon);
  
  return type_id;
}

static void
bse_constant_class_init (BseConstantClass *class)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (class);
  BseObjectClass *object_class = BSE_OBJECT_CLASS (class);
  BseSourceClass *source_class = BSE_SOURCE_CLASS (class);
  guint ochannel, i;
  
  parent_class = g_type_class_peek_parent (class);
  
  gobject_class->set_property = bse_constant_set_property;
  gobject_class->get_property = bse_constant_get_property;
  
  source_class->context_create = bse_constant_context_create;
  
  for (i = 1; i <= BSE_CONSTANT_N_OUTPUTS; i++)
    {
      gchar *string, *name, *group = g_strdup_printf ("Constant Output %u", i);
      
      string = g_strdup_printf ("value_%u", i);
      name = g_strdup_printf ("Value [float]");
      bse_object_class_add_param (object_class, group, PARAM_VALUE + (i - 1) * 3,
				  sfi_pspec_real (string, name, NULL,
						  1.0, -1.0, 1.0, 0.01,
						  SFI_PARAM_DEFAULT SFI_PARAM_HINT_DIAL));
      g_free (string);
      g_free (name);
      string = g_strdup_printf ("frequency_%u", i);
      name = g_strdup_printf ("Frequency");
      bse_object_class_add_param (object_class, group, PARAM_FREQ + (i - 1) * 3,
				  sfi_pspec_real (string, name, NULL,
						  BSE_MAX_FREQUENCY_f,
						  0, BSE_MAX_FREQUENCY_f,
						  10.0,
						  SFI_PARAM_GUI SFI_PARAM_HINT_DIAL));
      bse_object_class_set_param_log_scale (object_class, string, BSE_KAMMER_FREQUENCY_f * 2, 2, 4);
      g_free (string);
      g_free (name);
      string = g_strdup_printf ("note_%u", i);
      name = g_strdup_printf ("Note");
      bse_object_class_add_param (object_class, group, PARAM_NOTE + (i - 1) * 3,
				  bse_param_spec_note_simple (string, name, NULL,
							      SFI_PARAM_GUI));
      g_free (string);
      g_free (name);
      string = g_strdup_printf ("Const Out%u", i);
      name = g_strdup_printf ("Constant Output %u", i);
      ochannel = bse_source_class_add_ochannel (source_class, string, name);
      g_assert (ochannel == i - 1);
      g_free (string);
      g_free (name);
      g_free (group);
    }
}

static void
bse_constant_init (BseConstant *constant)
{
  guint i;
  
  for (i = 0; i < BSE_CONSTANT_N_OUTPUTS; i++)
    constant->constants[i] = 1.0;
}

static void
bse_constant_set_property (GObject      *object,
			   guint         param_id,
			   const GValue *value,
			   GParamSpec   *pspec)
{
  BseConstant *constant = BSE_CONSTANT (object);
  
  switch (param_id)
    {
      guint indx, n;
    default:
      indx = (param_id - PARAM_VALUE) % 3;
      n = (param_id - PARAM_VALUE) / 3;
      switch (indx)
	{
	  gchar *prop;
	case PARAM_VALUE - PARAM_VALUE:
	  constant->constants[n] = sfi_value_get_real (value);
	  bse_constant_update_modules (constant, NULL);
	  prop = g_strdup_printf ("frequency_%u", n + 1);
	  g_object_notify (object, prop);
	  g_free (prop);
	  prop = g_strdup_printf ("note_%u", n + 1);
          g_object_notify (object, prop);
	  g_free (prop);
	  break;
	case PARAM_FREQ - PARAM_VALUE:
	  constant->constants[n] = BSE_VALUE_FROM_FREQ (sfi_value_get_real (value));
          bse_constant_update_modules (constant, NULL);
          prop = g_strdup_printf ("value_%u", n + 1);
	  g_object_notify (object, prop);
	  g_free (prop);
	  prop = g_strdup_printf ("note_%u", n + 1);
	  g_object_notify (object, prop);
	  g_free (prop);
	  break;
	case PARAM_NOTE - PARAM_VALUE:
	  constant->constants[n] = BSE_VALUE_FROM_FREQ (bse_note_to_freq (sfi_value_get_note (value)));
          bse_constant_update_modules (constant, NULL);
	  prop = g_strdup_printf ("value_%u", n + 1);
	  g_object_notify (object, prop);
	  g_free (prop);
          prop = g_strdup_printf ("frequency_%u", n + 1);
	  g_object_notify (object, prop);
	  g_free (prop);
	  break;
	default:
	  G_OBJECT_WARN_INVALID_PROPERTY_ID (constant, param_id, pspec);
	  break;
	}
    }
}

static void
bse_constant_get_property (GObject     *object,
			   guint        param_id,
			   GValue      *value,
			   GParamSpec  *pspec)
{
  BseConstant *constant = BSE_CONSTANT (object);
  
  switch (param_id)
    {
      guint indx, n;
    default:
      indx = (param_id - PARAM_VALUE) % 3;
      n = (param_id - PARAM_VALUE) / 3;
      switch (indx)
	{
        case PARAM_VALUE - PARAM_VALUE:
	  sfi_value_set_real (value, constant->constants[n]);
	  break;
        case PARAM_FREQ - PARAM_VALUE:
	  sfi_value_set_real (value, BSE_FREQ_FROM_VALUE (constant->constants[n]));
	  break;
        case PARAM_NOTE - PARAM_VALUE:
	  sfi_value_set_note (value, bse_note_from_freq (BSE_FREQ_FROM_VALUE (constant->constants[n])));
	  break;
	default:
	  G_OBJECT_WARN_INVALID_PROPERTY_ID (constant, param_id, pspec);
	  break;
	}
    }
}

typedef struct
{
  gfloat constants[BSE_CONSTANT_N_OUTPUTS];
} ConstantModule;

static void
bse_constant_update_modules (BseConstant *constant,
			     GslTrans    *trans)
{
  if (BSE_SOURCE_PREPARED (constant))
    bse_source_update_modules (BSE_SOURCE (constant),
			       G_STRUCT_OFFSET (ConstantModule, constants),
			       constant->constants,
			       sizeof (constant->constants),
			       trans);
}

typedef struct {
  guint  index;
  guint  n_values;
  gfloat constants[BSE_CONSTANT_N_OUTPUTS];
} FlowAccessData;

static void
flow_access (GslModule *module,
	     gpointer   data)
{
  ConstantModule *cmod = module->user_data;
  FlowAccessData *fdata = data;
  
  g_print("FLOWJOBINCONSTANT(%u): %f (%lld)\n", fdata->index, fdata->constants[0], gsl_module_tick_stamp (module));
  
  memcpy (cmod->constants + fdata->index, fdata->constants, sizeof (cmod->constants[0]) * fdata->n_values);
}

static void
constant_process (GslModule *module,
		  guint      n_values)
{
  ConstantModule *cmod = module->user_data;
  guint i;
  
  for (i = 0; i < BSE_CONSTANT_N_OUTPUTS; i++)
    if (GSL_MODULE_OSTREAM (module, i).connected)
      GSL_MODULE_OSTREAM (module, i).values = gsl_engine_const_values (cmod->constants[i]);
}

static void
bse_constant_context_create (BseSource *source,
			     guint      context_handle,
			     GslTrans  *trans)
{
  static const GslClass constant_class = {
    0,				/* n_istreams */
    0,                          /* n_jstreams */
    BSE_CONSTANT_N_OUTPUTS,	/* n_ostreams */
    constant_process,		/* process */
    NULL,                       /* process_defer */
    NULL,                       /* reset */
    (GslModuleFreeFunc) g_free,	/* free */
    GSL_COST_CHEAP,		/* flags */
  };
  ConstantModule *constant = g_new0 (ConstantModule, 1);
  GslModule *module;
  
  module = gsl_module_new (&constant_class, constant);
  
  /* setup module i/o streams with BseSource i/o channels */
  bse_source_set_context_module (source, context_handle, module);
  
  /* commit module to engine */
  gsl_trans_add (trans, gsl_job_integrate (module));
  
  /* chain parent class' handler */
  BSE_SOURCE_CLASS (parent_class)->context_create (source, context_handle, trans);
  
  /* update (initialize) module data */
  bse_constant_update_modules (BSE_CONSTANT (source), trans);
}
