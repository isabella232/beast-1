/* BEAST - Bedevilled Audio System
 * Copyright (C) 2004 Tim Janik
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.
 */
#include "bstpatternctrl.h"
#include "bstkeybindings.h"
#include <gdk/gdkkeysyms.h>
#include <string.h>


/* --- prototypes --- */
static gboolean pattern_controller_key_press    (BstPatternController   *self,
                                                 GdkEventKey            *event);


/* --- functions --- */
BstPatternController*
bst_pattern_controller_new (BstPatternView         *pview,
                            GxkActionGroup         *quant_rtools)
{
  BstPatternController *self;

  g_return_val_if_fail (BST_IS_PATTERN_VIEW (pview), NULL);

  self = g_new0 (BstPatternController, 1);
  self->steps = gxk_param_new_value (sfi_pspec_int ("steps", _("Steps"),
                                                    _("The number of cells to move across each time "
                                                      "an event or note was edited"),
                                                    1, 0, 384, 4, SFI_PARAM_STANDARD),
                                     NULL, NULL);
  self->step_dir = gxk_param_new_value (sfi_pspec_choice ("step_dir", _("Direction"),
                                                          _("The direction of cell movement each time "
                                                            "an event or note was edited"),
                                                          "down", bst_direction_get_values(), SFI_PARAM_STANDARD),
                                        NULL, NULL);
  self->hwrap = gxk_param_new_value (sfi_pspec_bool ("hwrap", _("HWrap"),
                                                     _("Toggle whether horizontal movement of the focus cell will "
                                                       "wrap around edges"), FALSE, SFI_PARAM_STANDARD),
                                     NULL, NULL);
  self->pview = pview;
  self->ref_count = 1;

  self->ref_count++;
  g_signal_connect_data (pview, "key-press-event",
                         G_CALLBACK (pattern_controller_key_press),
                         self, (GClosureNotify) bst_pattern_controller_unref,
                         G_CONNECT_SWAPPED);
  self->quant_rtools = quant_rtools ? g_object_ref (quant_rtools) : NULL;

  gxk_scroll_canvas_set_canvas_cursor (GXK_SCROLL_CANVAS (pview), GDK_XTERM);

  return self;
}

BstPatternController*
bst_pattern_controller_ref (BstPatternController   *self)
{
  g_return_val_if_fail (self != NULL, NULL);
  g_return_val_if_fail (self->ref_count >= 1, NULL);

  self->ref_count++;

  return self;
}

void
bst_pattern_controller_unref (BstPatternController   *self)
{
  g_return_if_fail (self != NULL);
  g_return_if_fail (self->ref_count >= 1);

  self->ref_count--;
  if (!self->ref_count)
    {
      if (self->quant_rtools)
        {
          gxk_action_group_dispose (self->quant_rtools);
          g_object_unref (self->quant_rtools);
        }
      gxk_param_destroy (self->steps);
      gxk_param_destroy (self->step_dir);
      g_free (self);
    }
}

static gboolean
pattern_controller_key_press (BstPatternController *self,
                              GdkEventKey          *event)
{
  BstPatternView *pview = self->pview;
  gdouble param = 0;
  BstPatternFunction ftype = 0;
  BstPatternFunction action;
  BstPatternFunction movement;
  BstPatternColumn *col = bst_pattern_view_get_focus_cell (pview, NULL, NULL);
  gboolean handled;
  guint state = event->state, g = col->klass->collision_group;
  if (!ftype && g)
    ftype = bst_key_binding_lookup_id (bst_pattern_controller_piano_keys(), event->keyval, state, g, &param);
  if (!ftype)
    ftype = bst_key_binding_lookup_id (bst_pattern_controller_piano_keys(), event->keyval, state, 0, &param);
  if (!ftype && g)
    ftype = bst_key_binding_lookup_id (bst_pattern_controller_generic_keys(), event->keyval, state, g, &param);
  if (!ftype)
    ftype = bst_key_binding_lookup_id (bst_pattern_controller_generic_keys(), event->keyval, state, 0, &param);
  state = event->state & ~GDK_SHIFT_MASK;
  if (!ftype && g)
    ftype = bst_key_binding_lookup_id (bst_pattern_controller_piano_keys(), event->keyval, state, g, &param);
  if (!ftype)
    ftype = bst_key_binding_lookup_id (bst_pattern_controller_piano_keys(), event->keyval, state, 0, &param);
  if (!ftype && g)
    ftype = bst_key_binding_lookup_id (bst_pattern_controller_generic_keys(), event->keyval, state, g, &param);
  if (!ftype)
    ftype = bst_key_binding_lookup_id (bst_pattern_controller_generic_keys(), event->keyval, state, 0, &param);
  action = ftype & BST_PATTERN_MASK_ACTION;
  movement = ftype & BST_PATTERN_MASK_MOVEMENT;
  handled = bst_pattern_view_dispatch_key (pview, event->keyval, event->state, action, param, &movement);
  if (movement == BST_PATTERN_MOVE_NEXT &&      /* if the standard step-next movement */
      (event->state & GDK_SHIFT_MASK) &&        /* is blocked by shift */
      (movement != ftype || handled))           /* and this is not purely "next" */
    movement = 0;       /* honour the block */
  if (movement)
    {
      const guint channel_page = 2, row_page = 4;
      gboolean hwrap = sfi_value_get_bool (&self->hwrap->value);
      gint focus_col = pview->focus_col;
      gint focus_row = pview->focus_row;
      /* movement */
      switch (movement)
        {
          guint d;
        case BST_PATTERN_MOVE_LEFT:     focus_col--;                                            break;
        case BST_PATTERN_MOVE_RIGHT:    focus_col++;                                            break;
        case BST_PATTERN_MOVE_UP:       focus_row--;                                            break;
        case BST_PATTERN_MOVE_DOWN:     focus_row++;                                            break;
        case BST_PATTERN_PAGE_LEFT:     focus_col -= channel_page;                              break;
        case BST_PATTERN_PAGE_RIGHT:    focus_col += channel_page;                              break;
        case BST_PATTERN_PAGE_UP:       focus_row -= row_page;                                  break;
        case BST_PATTERN_PAGE_DOWN:     focus_row += row_page;                                  break;
        case BST_PATTERN_JUMP_LEFT:     focus_col = 0;                                          break;
        case BST_PATTERN_JUMP_RIGHT:    focus_col = pview->n_focus_cols - 1;                    break;
        case BST_PATTERN_JUMP_TOP:      focus_row = 0;                                          break;
        case BST_PATTERN_JUMP_BOTTOM:   focus_row = bst_pattern_view_get_last_row (pview);      break;
        case BST_PATTERN_MOVE_NEXT:
          d = bst_direction_from_choice (sfi_value_get_choice (&self->step_dir->value));
          if (d == BST_LEFT || d == BST_RIGHT)
            focus_col += (d == BST_LEFT ? -1 : +1) * g_value_get_int (&self->steps->value);
          else /* UP/DOWN */
            focus_row += (d == BST_UP ? -1 : +1) * g_value_get_int (&self->steps->value);
          break;
        case BST_PATTERN_SET_STEP_WIDTH:
          g_value_set_int (&self->steps->value, param);
          gxk_param_update (self->steps);       /* we poked the params value */
          break;
        default: ;
        }
      /* wrapping */
      if (focus_col < 0)
        focus_col = hwrap ? pview->n_focus_cols - 1 : 0;
      if (focus_col >= pview->n_focus_cols)
        focus_col = hwrap ? 0 : pview->n_focus_cols - 1;
      if (focus_row < 0)
        focus_row = 0;
      if (focus_row > bst_pattern_view_get_last_row (pview))
        focus_row = bst_pattern_view_get_last_row (pview);
      /* update focus */
      bst_pattern_view_set_focus (self->pview, focus_col, focus_row);
      handled = TRUE;
    }
  return handled;
}

static const BstKeyBindingFunction*
pattern_controller_get_functions (gboolean want_piano,
                                  guint   *n_p)
{
  static BstKeyBindingFunction generic_funcs[] = {
    /* movement */
    { BST_PATTERN_MOVE_NEXT,    "next",         0, N_("Move focus to the next cell (up/left/right/down according to configuration)") },
    { BST_PATTERN_MOVE_UP,      "move-up",      0, N_("Move focus cell upwards") },
    { BST_PATTERN_MOVE_LEFT,    "move-left",    0, N_("Move focus cell to the left") },
    { BST_PATTERN_MOVE_RIGHT,   "move-right",   0, N_("Move focus cell to the right") },
    { BST_PATTERN_MOVE_DOWN,    "move-down",    0, N_("Move focus cell downwards") },
    { BST_PATTERN_PAGE_UP,      "page-up",      0, N_("Move focus cell upwards page-wise") },
    { BST_PATTERN_PAGE_LEFT,    "page-left",    0, N_("Move focus cell to the left page-wise") },
    { BST_PATTERN_PAGE_RIGHT,   "page-right",   0, N_("Move focus cell to the right page-wise") },
    { BST_PATTERN_PAGE_DOWN,    "page-down",    0, N_("Move focus cell downwards page-wise") },
    { BST_PATTERN_JUMP_TOP,     "jump-top",     0, N_("Set the focus cell to the topmost position possible") },
    { BST_PATTERN_JUMP_LEFT,    "jump-left",    0, N_("Set the focus cell to the leftmost position possible") },
    { BST_PATTERN_JUMP_RIGHT,   "jump-right",   0, N_("Set the focus cell to the rightmost position possible") },
    { BST_PATTERN_JUMP_BOTTOM,  "jump-bottom",  0, N_("Set the focus cell to the bottommost position possible") },
    { BST_PATTERN_SET_STEP_WIDTH,
      "set-step-width",                         BST_KEY_BINDING_PARAM_SHORT,
      N_("Set the number of steps to make when moving to the next cell") },
    /* base octave */
    { BST_PATTERN_SET_BASE_OCTAVE | BST_PATTERN_MOVE_NEXT,
      "set-base-octave",                        BST_KEY_BINDING_PARAM_SHORT,
      N_("Set the base octave") },
    { BST_PATTERN_CHANGE_BASE_OCTAVE,
      "change-base-octave",                     BST_KEY_BINDING_PARAM_SHORT,
      N_("Change the base octave by a given amount") },
    /* numeric changes */
    { BST_PATTERN_NUMERIC_CHANGE | BST_PATTERN_MOVE_NEXT,
      "numeric-change",                         BST_KEY_BINDING_PARAM_SHORT,
      N_("Change the numeric focus cell contents (e.g. octave) by a given amount") },
    /* octaves */
    { BST_PATTERN_SET_OCTAVE | BST_PATTERN_MOVE_NEXT,
      "set-octave",                             BST_KEY_BINDING_PARAM_SHORT,
      N_("Set the focus cell octave") },
    /* events */
    { BST_PATTERN_REMOVE_EVENTS | BST_PATTERN_MOVE_NEXT,
      "remove-events",                          0,
      N_("Remove any events in the focus cell"), 0 },
    /* notes */
    { BST_PATTERN_SET_NOTE | BST_PATTERN_MOVE_NEXT,
      "set-note",                               BST_KEY_BINDING_PARAM_NOTE,
      N_("Set the focus cell note"), 1 },
    /* digits */
    { BST_PATTERN_SET_DIGIT | BST_PATTERN_MOVE_NEXT,
      "set-digit",                              BST_KEY_BINDING_PARAM_USHORT,
      N_("Sets the value of the focus digit"), 2 },
  };
  static BstKeyBindingFunction piano_funcs[] = {
    /* events */
    { BST_PATTERN_REMOVE_EVENTS | BST_PATTERN_MOVE_NEXT,
      "remove-events",                          0,
      N_("Remove any events in the focus cell"), 0 },
    /* notes */
    { BST_PATTERN_SET_NOTE | BST_PATTERN_MOVE_NEXT,
      "set-note",                               BST_KEY_BINDING_PARAM_NOTE,
      N_("Set the focus cell note"), 1 },
    /* digits */
    { BST_PATTERN_SET_DIGIT | BST_PATTERN_MOVE_NEXT,
      "set-digit",                              BST_KEY_BINDING_PARAM_USHORT,
      N_("Sets the value of the focus digit"), 2 },
  };
  static gboolean initialized = FALSE;
  if (!initialized)
    {
      guint i;
      initialized = TRUE;
      for (i = 0; i < G_N_ELEMENTS (generic_funcs); i++)
        generic_funcs[i].function_blurb = _(generic_funcs[i].function_blurb);
      for (i = 0; i < G_N_ELEMENTS (piano_funcs); i++)
        piano_funcs[i].function_blurb = _(piano_funcs[i].function_blurb);
    }
  if (want_piano)
    {
      *n_p = G_N_ELEMENTS (piano_funcs);
      return piano_funcs;
    }
  else
    {
      *n_p = G_N_ELEMENTS (generic_funcs);
      return generic_funcs;
    }
}

BstKeyBinding*
bst_pattern_controller_default_generic_keys (void)
{
  static BstKeyBindingItem dflt_keys[] = {
    /* move in cells */
    {                   "Up",                   "move-up",      	0 },
    {                   "KP_Up",                "move-up",      	0 },
    {                   "Left",                 "move-left",    	0 },
    {                   "KP_Left",              "move-left",    	0 },
    {                   "Right",                "move-right",   	0 },
    {                   "KP_Right",             "move-right",   	0 },
    {                   "Down",                 "move-down",    	0 },
    {                   "KP_Down",              "move-down",    	0 },
    {                   "KP_Begin"/*5*/,        "move-down",    	0 },
#if 0
    /* move according to configuration */
    {                   "Return",               "next",    	        0 },
    {                   "KP_Enter",             "next",    	        0 },
#endif
    /* move in pages */
    {                   "Page_Up",              "page-up",      	0 },
    {                   "KP_Page_Up",           "page-up",      	0 },
    { "<Control>"       "Left",                 "page-left",    	0 },
    { "<Control>"       "KP_Left",              "page-left",    	0 },
    { "<Control>"       "Right",                "page-right",   	0 },
    { "<Control>"       "KP_Right",             "page-right",   	0 },
    {                   "Page_Down",            "page-down",    	0 },
    {                   "KP_Page_Down",         "page-down",    	0 },
    /* jump to boundary */
    { "<Control>"       "Page_Up",              "jump-top",     	0 },
    { "<Control>"       "KP_Page_Up",           "jump-top",     	0 },
    {                   "Home",                 "jump-left",    	0 },
    {                   "KP_Home",              "jump-left",    	0 },
    {                   "End",                  "jump-right",   	0 },
    {                   "KP_End",               "jump-right",   	0 },
    { "<Control>"       "Page_Down",            "jump-bottom",  	0 },
    { "<Control>"       "KP_Page_Down",         "jump-bottom",  	0 },
#if 0
    /* part movement */
    {                   "Tab",                  "next-part",            0 },
    {                   "KP_Tab",               "next-part",            0 },
    { "<Shift>"         "Tab",                  "prev-part",            0 },
    { "<Shift>"         "KP_Tab",               "prev-part",            0 },
    {                   "ISO_Left_Tab",         "prev-part",            0 },
#endif
    /* set step width for movement */
    { "<Control>"       "0",                    "set-step-width",       0 },
    { "<Control>"       "1",                    "set-step-width",       1 },
    { "<Control>"       "2",                    "set-step-width",       2 },
    { "<Control>"       "3",                    "set-step-width",       3 },
    { "<Control>"       "4",                    "set-step-width",       4 },
    { "<Control>"       "5",                    "set-step-width",       5 },
    { "<Control>"       "6",                    "set-step-width",       6 },
    { "<Control>"       "7",                    "set-step-width",       7 },
    { "<Control>"       "8",                    "set-step-width",       8 },
    { "<Control>"       "9",                    "set-step-width",       9 },
    /* enter numeric values */
    {                   "0",                    "set-digit",            0 },
    {                   "1",                    "set-digit",            1 },
    {                   "2",                    "set-digit",            2 },
    {                   "3",                    "set-digit",            3 },
    {                   "4",                    "set-digit",            4 },
    {                   "5",                    "set-digit",            5 },
    {                   "6",                    "set-digit",            6 },
    {                   "7",                    "set-digit",            7 },
    {                   "8",                    "set-digit",            8 },
    {                   "9",                    "set-digit",            9 },
    {                   "a",                    "set-digit",           10 },
    {                   "b",                    "set-digit",           11 },
    {                   "c",                    "set-digit",           12 },
    {                   "d",                    "set-digit",           13 },
    {                   "e",                    "set-digit",           14 },
    {                   "f",                    "set-digit",           15 },
    /* remove notes/events */
    {                   "space",                "remove-events",        0 },
    {                   "KP_Space",             "remove-events",        0 },
    /* increment cell octave with shift or move */
    {                   "plus",                 "numeric-change",       +1 },
    {                   "KP_Add",               "numeric-change",       +1 },
    {                   "asterisk",             "numeric-change",       +1 },
    {                   "KP_Multiply",          "numeric-change",       +1 },
    /* decrement cell octave with shift or move */
    {                   "minus",                "numeric-change",       -1 },
    {                   "underscore",           "numeric-change",       -1 },
    {                   "KP_Divide",            "numeric-change",       -1 },
    {                   "KP_Subtract",          "numeric-change",       -1 },
    /* increment base octave */
    { "<Control>"       "plus",                 "change-base-octave",      +1 },
    { "<Control>"       "KP_Add",               "change-base-octave",      +1 },
    { "<Control>"       "asterisk",             "change-base-octave",      +1 },
    { "<Control>"       "KP_Multiply",          "change-base-octave",      +1 },
    /* decrement base octave */
    { "<Control>"       "minus",                "change-base-octave",      -1 },
    { "<Control>"       "underscore",           "change-base-octave",      -1 },
    { "<Control>"       "KP_Divide",            "change-base-octave",      -1 },
    { "<Control>"       "KP_Subtract",          "change-base-octave",      -1 },
    // keypad: "KP_Insert"/*0*/, "KP_Delete"/*,*/
  };
  static BstKeyBinding kbinding = { "pattern-controller-default-generic-keys", };
  if (!kbinding.n_funcs)
    {
      BstKeyBindingItemSeq *iseq;
      guint i;
      kbinding.funcs = pattern_controller_get_functions (FALSE, &kbinding.n_funcs);
      /* setup default keys */
      iseq = bst_key_binding_item_seq_new();
      for (i = 0; i < G_N_ELEMENTS (dflt_keys); i++)
        bst_key_binding_item_seq_append (iseq, &dflt_keys[i]);
      bst_key_binding_set_item_seq (&kbinding, iseq);
      bst_key_binding_item_seq_free (iseq);
    }
  return &kbinding;
}

BstKeyBinding*
bst_pattern_controller_default_piano_keys (void)
{
  static BstKeyBindingItem dflt_keys[] = {
    /* events */
    {                   "space",                "remove-events",        0 },
  };
  static BstKeyBinding kbinding = { "pattern-controller-default-piano-keys", };
  if (!kbinding.n_funcs)
    {
      BstKeyBindingItemSeq *iseq;
      guint i;
      kbinding.funcs = pattern_controller_get_functions (TRUE, &kbinding.n_funcs);
      /* setup default keys */
      iseq = bst_key_binding_item_seq_new();
      for (i = 0; i < G_N_ELEMENTS (dflt_keys); i++)
        bst_key_binding_item_seq_append (iseq, &dflt_keys[i]);
      bst_key_binding_set_item_seq (&kbinding, iseq);
      bst_key_binding_item_seq_free (iseq);
    }
  return &kbinding;
}

BstKeyBinding*
bst_pattern_controller_generic_keys (void)
{
  static BstKeyBinding kbinding = { "pattern-controller-generic-keys", };
  if (!kbinding.n_funcs)
    {
      BstKeyBinding *dflt_kbinding = bst_pattern_controller_default_generic_keys();
      BstKeyBindingItemSeq *iseq;
      kbinding.funcs = pattern_controller_get_functions (FALSE, &kbinding.n_funcs);
      /* copy keys */
      iseq = bst_key_binding_get_item_seq (dflt_kbinding);
      bst_key_binding_set_item_seq (&kbinding, iseq);
      bst_key_binding_item_seq_free (iseq);
    }
  return &kbinding;
}

BstKeyBinding*
bst_pattern_controller_piano_keys (void)
{
  static BstKeyBinding kbinding = { "pattern-controller-piano-keys", };
  if (!kbinding.n_funcs)
    {
      BstKeyBinding *dflt_kbinding = bst_pattern_controller_default_piano_keys();
      BstKeyBindingItemSeq *iseq;
      kbinding.funcs = pattern_controller_get_functions (TRUE, &kbinding.n_funcs);
      /* copy keys */
      iseq = bst_key_binding_get_item_seq (dflt_kbinding);
      bst_key_binding_set_item_seq (&kbinding, iseq);
      bst_key_binding_item_seq_free (iseq);
    }
  return &kbinding;
}