#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xps_resource ;
struct TYPE_5__ {int opacity_top; float* opacity; int /*<<< orphan*/ * dev; } ;
typedef  TYPE_1__ xps_document ;
typedef  int /*<<< orphan*/  fz_xml ;
typedef  int /*<<< orphan*/  fz_rect ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;

/* Variables and functions */
 int FZ_MAX_COLORS ; 
 float fz_atof (char*) ; 
 int /*<<< orphan*/  fz_begin_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_default_color_params ; 
 int /*<<< orphan*/  fz_end_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* fz_xml_att (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ fz_xml_is_tag (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ nelem (float*) ; 
 int /*<<< orphan*/  xps_parse_brush (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xps_parse_color (int /*<<< orphan*/ *,TYPE_1__*,char*,char*,int /*<<< orphan*/ **,float*) ; 

void
xps_begin_opacity(fz_context *ctx, xps_document *doc, fz_matrix ctm, fz_rect area,
	char *base_uri, xps_resource *dict,
	char *opacity_att, fz_xml *opacity_mask_tag)
{
	fz_device *dev = doc->dev;
	float opacity;

	if (!opacity_att && !opacity_mask_tag)
		return;

	opacity = 1;
	if (opacity_att)
		opacity = fz_atof(opacity_att);

	if (fz_xml_is_tag(opacity_mask_tag, "SolidColorBrush"))
	{
		char *scb_opacity_att = fz_xml_att(opacity_mask_tag, "Opacity");
		char *scb_color_att = fz_xml_att(opacity_mask_tag, "Color");
		if (scb_opacity_att)
			opacity = opacity * fz_atof(scb_opacity_att);
		if (scb_color_att)
		{
			fz_colorspace *colorspace;
			float samples[FZ_MAX_COLORS];
			xps_parse_color(ctx, doc, base_uri, scb_color_att, &colorspace, samples);
			opacity = opacity * samples[0];
		}
		opacity_mask_tag = NULL;
	}

	if (doc->opacity_top + 1 < (int)nelem(doc->opacity))
	{
		doc->opacity[doc->opacity_top + 1] = doc->opacity[doc->opacity_top] * opacity;
		doc->opacity_top++;
	}

	if (opacity_mask_tag)
	{
		fz_begin_mask(ctx, dev, area, 0, NULL, NULL, fz_default_color_params);
		xps_parse_brush(ctx, doc, ctm, area, base_uri, dict, opacity_mask_tag);
		fz_end_mask(ctx, dev);
	}
}