#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * out; } ;
typedef  TYPE_1__ svg_device ;
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;
typedef  int /*<<< orphan*/  fz_color_params ;

/* Variables and functions */
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,...) ; 
 float svg_hex_color (int /*<<< orphan*/ *,int /*<<< orphan*/ *,float const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
svg_dev_stroke_color(fz_context *ctx, svg_device *sdev, fz_colorspace *colorspace, const float *color, float alpha, fz_color_params color_params)
{
	fz_output *out = sdev->out;
	if (colorspace)
		fz_write_printf(ctx, out, " fill=\"none\" stroke=\"#%06x\"", svg_hex_color(ctx, colorspace, color, color_params));
	else
		fz_write_printf(ctx, out, " fill=\"none\" stroke=\"none\"");
	if (alpha != 1)
		fz_write_printf(ctx, out, " stroke-opacity=\"%g\"", alpha);
}