#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  xps_resource ;
typedef  int /*<<< orphan*/  xps_document ;
typedef  int /*<<< orphan*/  fz_xml ;
typedef  int /*<<< orphan*/  fz_text ;
typedef  int /*<<< orphan*/  fz_rect ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_link ;
typedef  int /*<<< orphan*/  fz_font ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int atoi (char*) ; 
 int /*<<< orphan*/  fz_atof (char*) ; 
 int /*<<< orphan*/  fz_bound_text (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_font (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_text (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* fz_xml_att (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * fz_xml_down (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_xml_find_down (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  xps_add_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * xps_lookup_font (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*,char*) ; 
 int /*<<< orphan*/ * xps_parse_glyphs_imp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,char*,char*) ; 
 int /*<<< orphan*/  xps_parse_transform (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xps_resolve_resource_reference (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xps_load_links_in_glyphs(fz_context *ctx, xps_document *doc, fz_matrix ctm,
		char *base_uri, xps_resource *dict, fz_xml *root, fz_link **link)
{
	char *navigate_uri_att = fz_xml_att(root, "FixedPage.NavigateUri");
	if (navigate_uri_att)
	{
		char *transform_att = fz_xml_att(root, "RenderTransform");
		fz_xml *transform_tag = fz_xml_down(fz_xml_find_down(root, "Path.RenderTransform"));

		char *bidi_level_att = fz_xml_att(root, "BidiLevel");
		char *font_size_att = fz_xml_att(root, "FontRenderingEmSize");
		char *font_uri_att = fz_xml_att(root, "FontUri");
		char *origin_x_att = fz_xml_att(root, "OriginX");
		char *origin_y_att = fz_xml_att(root, "OriginY");
		char *is_sideways_att = fz_xml_att(root, "IsSideways");
		char *indices_att = fz_xml_att(root, "Indices");
		char *unicode_att = fz_xml_att(root, "UnicodeString");
		char *style_att = fz_xml_att(root, "StyleSimulations");

		int is_sideways = 0;
		int bidi_level = 0;
		fz_font *font;
		fz_text *text;
		fz_rect area;

		xps_resolve_resource_reference(ctx, doc, dict, &transform_att, &transform_tag, NULL);

		ctm = xps_parse_transform(ctx, doc, transform_att, transform_tag, ctm);

		if (is_sideways_att)
			is_sideways = !strcmp(is_sideways_att, "true");
		if (bidi_level_att)
			bidi_level = atoi(bidi_level_att);

		font = xps_lookup_font(ctx, doc, base_uri, font_uri_att, style_att);
		if (!font)
			return;
		text = xps_parse_glyphs_imp(ctx, doc, ctm, font, fz_atof(font_size_att),
				fz_atof(origin_x_att), fz_atof(origin_y_att),
				is_sideways, bidi_level, indices_att, unicode_att);
		area = fz_bound_text(ctx, text, NULL, ctm);
		fz_drop_text(ctx, text);
		fz_drop_font(ctx, font);

		xps_add_link(ctx, doc, area, base_uri, navigate_uri_att, link);
	}
}