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
struct TYPE_4__ {int blend_bitmask; int /*<<< orphan*/ * out; } ;
typedef  TYPE_1__ svg_device ;
typedef  int /*<<< orphan*/  fz_rect ;
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;

/* Variables and functions */
 int FZ_BLEND_LUMINOSITY ; 
 int FZ_BLEND_NORMAL ; 
 int /*<<< orphan*/ * end_def (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/ * start_def (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
svg_dev_begin_group(fz_context *ctx, fz_device *dev, fz_rect bbox, fz_colorspace *cs, int isolated, int knockout, int blendmode, float alpha)
{
	svg_device *sdev = (svg_device*)dev;
	fz_output *out = sdev->out;

	/* SVG only supports normal/multiply/screen/darken/lighten,
	 * but we'll send them all, as the spec says that unrecognised
	 * ones are treated as normal. */
	static char *blend_names[] = {
		"normal",	/* FZ_BLEND_NORMAL */
		"multiply",	/* FZ_BLEND_MULTIPLY */
		"screen",	/* FZ_BLEND_SCREEN */
		"overlay",	/* FZ_BLEND_OVERLAY */
		"darken",	/* FZ_BLEND_DARKEN */
		"lighten",	/* FZ_BLEND_LIGHTEN */
		"color_dodge",	/* FZ_BLEND_COLOR_DODGE */
		"color_burn",	/* FZ_BLEND_COLOR_BURN */
		"hard_light",	/* FZ_BLEND_HARD_LIGHT */
		"soft_light",	/* FZ_BLEND_SOFT_LIGHT */
		"difference",	/* FZ_BLEND_DIFFERENCE */
		"exclusion",	/* FZ_BLEND_EXCLUSION */
		"hue",		/* FZ_BLEND_HUE */
		"saturation",	/* FZ_BLEND_SATURATION */
		"color",	/* FZ_BLEND_COLOR */
		"luminosity",	/* FZ_BLEND_LUMINOSITY */
	};

	if (blendmode < FZ_BLEND_NORMAL || blendmode > FZ_BLEND_LUMINOSITY)
		blendmode = FZ_BLEND_NORMAL;
	if (blendmode != FZ_BLEND_NORMAL && (sdev->blend_bitmask & (1<<blendmode)) == 0)
	{
		sdev->blend_bitmask |= (1<<blendmode);
		out = start_def(ctx, sdev);
		fz_write_printf(ctx, out,
				"<filter id=\"blend_%d\"><feBlend mode=\"%s\" in2=\"BackgroundImage\" in=\"SourceGraphic\"/></filter>\n",
				blendmode, blend_names[blendmode]);
		out = end_def(ctx, sdev);
	}

	/* SVG 1.1 doesn't support adequate blendmodes/knockout etc, so just ignore it for now */
	if (alpha == 1)
		fz_write_printf(ctx, out, "<g");
	else
		fz_write_printf(ctx, out, "<g opacity=\"%g\"", alpha);
	if (blendmode != FZ_BLEND_NORMAL)
		fz_write_printf(ctx, out, " filter=\"url(#blend_%d)\"", blendmode);
	fz_write_printf(ctx, out, ">\n");
}