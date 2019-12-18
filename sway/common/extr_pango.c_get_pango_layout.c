#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cairo_t ;
struct TYPE_4__ {int /*<<< orphan*/  message; } ;
typedef  int /*<<< orphan*/  PangoLayout ;
typedef  int /*<<< orphan*/  PangoFontDescription ;
typedef  int /*<<< orphan*/  PangoAttrList ;
typedef  TYPE_1__ GError ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_ERROR ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  g_error_free (TYPE_1__*) ; 
 int /*<<< orphan*/  pango_attr_list_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pango_attr_list_new () ; 
 int /*<<< orphan*/  pango_attr_list_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pango_attr_scale_new (double) ; 
 int /*<<< orphan*/ * pango_cairo_create_layout (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pango_font_description_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pango_font_description_from_string (char const*) ; 
 int /*<<< orphan*/  pango_layout_set_attributes (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pango_layout_set_font_description (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pango_layout_set_single_paragraph_mode (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pango_layout_set_text (int /*<<< orphan*/ *,char const*,int) ; 
 scalar_t__ pango_parse_markup (char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **,char**,int /*<<< orphan*/ *,TYPE_1__**) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 

PangoLayout *get_pango_layout(cairo_t *cairo, const char *font,
		const char *text, double scale, bool markup) {
	PangoLayout *layout = pango_cairo_create_layout(cairo);
	PangoAttrList *attrs;
	if (markup) {
		char *buf;
		GError *error = NULL;
		if (pango_parse_markup(text, -1, 0, &attrs, &buf, NULL, &error)) {
			pango_layout_set_text(layout, buf, -1);
			free(buf);
		} else {
			sway_log(SWAY_ERROR, "pango_parse_markup '%s' -> error %s", text,
					error->message);
			g_error_free(error);
			markup = false; // fallback to plain text
		}
	}
	if (!markup) {
		attrs = pango_attr_list_new();
		pango_layout_set_text(layout, text, -1);
	}

	pango_attr_list_insert(attrs, pango_attr_scale_new(scale));
	PangoFontDescription *desc = pango_font_description_from_string(font);
	pango_layout_set_font_description(layout, desc);
	pango_layout_set_single_paragraph_mode(layout, 1);
	pango_layout_set_attributes(layout, attrs);
	pango_attr_list_unref(attrs);
	pango_font_description_free(desc);
	return layout;
}