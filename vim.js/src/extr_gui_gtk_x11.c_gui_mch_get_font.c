#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  char_u ;
struct TYPE_5__ {int /*<<< orphan*/  text_context; int /*<<< orphan*/  in_use; } ;
struct TYPE_4__ {scalar_t__ vc_type; } ;
typedef  int /*<<< orphan*/  PangoFontDescription ;
typedef  int /*<<< orphan*/  PangoFont ;
typedef  int /*<<< orphan*/ * GuiFont ;

/* Variables and functions */
 scalar_t__ CONV_NONE ; 
 int /*<<< orphan*/  EMSG2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int PANGO_SCALE ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ e_font ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 TYPE_3__ gui ; 
 TYPE_1__ output_conv ; 
 int /*<<< orphan*/ * pango_context_load_font (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pango_font_description_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pango_font_description_from_string (char const*) ; 
 scalar_t__ pango_font_description_get_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pango_font_description_set_size (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * string_convert (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vim_free (int /*<<< orphan*/ *) ; 

GuiFont
gui_mch_get_font(char_u *name, int report_error)
{
    PangoFontDescription    *font;

    /* can't do this when GUI is not running */
    if (!gui.in_use || name == NULL)
	return NULL;

    if (output_conv.vc_type != CONV_NONE)
    {
	char_u *buf;

	buf = string_convert(&output_conv, name, NULL);
	if (buf != NULL)
	{
	    font = pango_font_description_from_string((const char *)buf);
	    vim_free(buf);
	}
	else
	    font = NULL;
    }
    else
	font = pango_font_description_from_string((const char *)name);

    if (font != NULL)
    {
	PangoFont *real_font;

	/* pango_context_load_font() bails out if no font size is set */
	if (pango_font_description_get_size(font) <= 0)
	    pango_font_description_set_size(font, 10 * PANGO_SCALE);

	real_font = pango_context_load_font(gui.text_context, font);

	if (real_font == NULL)
	{
	    pango_font_description_free(font);
	    font = NULL;
	}
	else
	    g_object_unref(real_font);
    }

    if (font == NULL)
    {
	if (report_error)
	    EMSG2(_((char *)e_font), name);
	return NULL;
    }

    return font;
}