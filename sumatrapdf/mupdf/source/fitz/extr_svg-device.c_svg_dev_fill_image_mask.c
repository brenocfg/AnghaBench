#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ svg_device ;
typedef  int /*<<< orphan*/  fz_output ;
struct TYPE_17__ {float a; float d; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ fz_matrix ;
struct TYPE_18__ {float w; float h; } ;
typedef  TYPE_3__ fz_image ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;
typedef  int /*<<< orphan*/  fz_color_params ;

/* Variables and functions */
 int /*<<< orphan*/ * end_def (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_2__ fz_concat (TYPE_2__,TYPE_2__) ; 
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/ * start_def (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  svg_dev_ctm (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__) ; 
 int /*<<< orphan*/  svg_dev_fill_color (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,float const*,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svg_send_image (int /*<<< orphan*/ *,TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
svg_dev_fill_image_mask(fz_context *ctx, fz_device *dev, fz_image *image, fz_matrix ctm,
	fz_colorspace *colorspace, const float *color, float alpha, fz_color_params color_params)
{
	svg_device *sdev = (svg_device*)dev;
	fz_output *out;
	fz_matrix local_ctm = ctm;
	fz_matrix scale = { 0 };
	int mask = sdev->id++;

	scale.a = 1.0f / image->w;
	scale.d = 1.0f / image->h;

	local_ctm = fz_concat(scale, ctm);
	out = start_def(ctx, sdev);
	fz_write_printf(ctx, out, "<mask id=\"ma%d\">\n", mask);
	svg_send_image(ctx, sdev, image, color_params);
	fz_write_printf(ctx, out, "</mask>\n");
	out = end_def(ctx, sdev);
	fz_write_printf(ctx, out, "<rect x=\"0\" y=\"0\" width=\"%d\" height=\"%d\"", image->w, image->h);
	svg_dev_fill_color(ctx, sdev, colorspace, color, alpha, color_params);
	svg_dev_ctm(ctx, sdev, local_ctm);
	fz_write_printf(ctx, out, " mask=\"url(#ma%d)\"/>\n", mask);
}