#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int n; int alpha; int s; int /*<<< orphan*/ * colorspace; int /*<<< orphan*/  seps; } ;
typedef  TYPE_1__ fz_pixmap ;
typedef  int /*<<< orphan*/  fz_overprint ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;
struct TYPE_10__ {int opm; scalar_t__ op; } ;
typedef  TYPE_2__ fz_color_params ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int FZ_MAX_COLORS ; 
 scalar_t__ colors_supported (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int fz_colorspace_is_device_gray (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int fz_colorspace_is_device_n (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_colorspace_is_subtractive (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_convert_color (int /*<<< orphan*/ *,int /*<<< orphan*/ *,float const*,int /*<<< orphan*/ *,float*,int /*<<< orphan*/ *,TYPE_2__) ; 
 int /*<<< orphan*/  fz_convert_separation_colors (int /*<<< orphan*/ *,int /*<<< orphan*/ *,float const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,float*,TYPE_2__) ; 
 int /*<<< orphan*/ * fz_device_gray (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_set_overprint (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * set_op_from_spaces (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static fz_overprint *
resolve_color(fz_context *ctx,
	fz_overprint *op,
	const float *color,
	fz_colorspace *colorspace,
	float alpha,
	fz_color_params color_params,
	unsigned char *colorbv,
	fz_pixmap *dest)
{
	float colorfv[FZ_MAX_COLORS];
	int i;
	int n = dest->n - dest->alpha;
	fz_colorspace *model = dest->colorspace;
	int devn, devgray;
	int effective_opm;

	if (colorspace == NULL && model != NULL)
		fz_throw(ctx, FZ_ERROR_GENERIC, "color destination requires source color");

	effective_opm = color_params.opm;
	devn = fz_colorspace_is_device_n(ctx, colorspace);
	devgray = fz_colorspace_is_device_gray(ctx, colorspace);

	/* We can only overprint when enabled, and when we are in a subtractive colorspace */
	if (color_params.op == 0 || !fz_colorspace_is_subtractive(ctx, dest->colorspace))
		op = NULL;

	/* Device Gray is additive, but seems to still be counted for overprint
	 * (see Ghent_V3.0/030_Gray_K_black_OP_x1a.pdf 030.pdf). */
	else if (devgray)
	{
	}

	/* If we are in a CMYK space (i.e. not a devn one, given we know we are subtractive at this point),
	 * then we only adhere to overprint mode if it's the same space as the destination. */
	/* FIXME: Possibly we need a better equivalency test here. */
	else if (!devn && colorspace != dest->colorspace)
	{
		effective_opm = 0;
	}

	if (n == 0)
		i = 0;
	else if (devn && colors_supported(ctx, colorspace, dest))
	{
		fz_convert_separation_colors(ctx, colorspace, color, dest->seps, dest->colorspace, colorfv, color_params);
		for (i = 0; i < n; i++)
			colorbv[i] = colorfv[i] * 255;
		op = set_op_from_spaces(ctx, op, dest, colorspace, effective_opm);
	}
	else
	{
		int c = n - dest->s;
		fz_convert_color(ctx, colorspace, color, dest->colorspace, colorfv, NULL, color_params);
		for (i = 0; i < c; i++)
			colorbv[i] = colorfv[i] * 255;
		for (; i < n; i++)
		{
			colorfv[i] = 0;
			colorbv[i] = 0;
		}
	}
	colorbv[i] = alpha * 255;

	/* op && !devn => overprinting in cmyk or devicegray. */
	if (op && !devn)
	{
		/* We are overprinting, so protect all spots. */
		for (i = 4; i < n; i++)
			fz_set_overprint(op, i);
		/* If OPM, then protect all components for which the color values are zero.
		 * (but only if we're in devicecmyk). */
		if (effective_opm == 1 && colorspace != fz_device_gray(ctx))
			for (i = 0; i < n; i++)
				if (colorfv[i] == 0)
					fz_set_overprint(op, i);
	}

	return op;
}