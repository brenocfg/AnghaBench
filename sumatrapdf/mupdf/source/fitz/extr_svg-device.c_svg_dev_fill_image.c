#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/ * out; } ;
typedef  TYPE_1__ svg_device ;
typedef  int /*<<< orphan*/  fz_output ;
struct TYPE_14__ {float a; float d; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ fz_matrix ;
struct TYPE_15__ {float w; float h; } ;
typedef  TYPE_3__ fz_image ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_color_params ;

/* Variables and functions */
 TYPE_2__ fz_concat (TYPE_2__,TYPE_2__) ; 
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  svg_dev_ctm (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__) ; 
 int /*<<< orphan*/  svg_send_image (int /*<<< orphan*/ *,TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
svg_dev_fill_image(fz_context *ctx, fz_device *dev, fz_image *image, fz_matrix ctm, float alpha, fz_color_params color_params)
{
	svg_device *sdev = (svg_device*)dev;
	fz_output *out = sdev->out;

	fz_matrix local_ctm = ctm;
	fz_matrix scale = { 0 };

	scale.a = 1.0f / image->w;
	scale.d = 1.0f / image->h;

	local_ctm = fz_concat(scale, ctm);
	fz_write_printf(ctx, out, "<g");
	if (alpha != 1.0f)
		fz_write_printf(ctx, out, " opacity=\"%g\"", alpha);
	svg_dev_ctm(ctx, sdev, local_ctm);
	fz_write_printf(ctx, out, ">\n");
	svg_send_image(ctx, sdev, image, color_params);
	fz_write_printf(ctx, out, "</g>\n");
}