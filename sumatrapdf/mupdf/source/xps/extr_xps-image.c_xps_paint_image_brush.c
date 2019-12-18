#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xps_resource ;
struct TYPE_5__ {size_t opacity_top; int /*<<< orphan*/ * opacity; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ xps_document ;
typedef  int /*<<< orphan*/  fz_xml ;
typedef  int /*<<< orphan*/  fz_rect ;
typedef  int /*<<< orphan*/  fz_matrix ;
struct TYPE_6__ {int xres; int yres; int w; int h; } ;
typedef  TYPE_2__ fz_image ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_default_color_params ; 
 int /*<<< orphan*/  fz_fill_image (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_pre_scale (int /*<<< orphan*/ ,float,float) ; 

__attribute__((used)) static void
xps_paint_image_brush(fz_context *ctx, xps_document *doc, fz_matrix ctm, fz_rect area, char *base_uri, xps_resource *dict,
	fz_xml *root, void *vimage)
{
	fz_image *image = vimage;
	float xs, ys;

	if (image->xres == 0 || image->yres == 0)
		return;
	xs = image->w * 96 / image->xres;
	ys = image->h * 96 / image->yres;
	ctm = fz_pre_scale(ctm, xs, ys);
	fz_fill_image(ctx, doc->dev, image, ctm, doc->opacity[doc->opacity_top], fz_default_color_params);
}