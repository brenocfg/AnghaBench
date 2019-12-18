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
struct TYPE_3__ {scalar_t__ resolved; scalar_t__ passthrough; } ;
typedef  TYPE_1__ fz_test_device ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_image ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;
typedef  int /*<<< orphan*/  fz_color_params ;

/* Variables and functions */
 int /*<<< orphan*/  fz_fill_image_mask (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,float const*,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_test_color (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,float const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fz_test_fill_image_mask(fz_context *ctx, fz_device *dev_, fz_image *image, fz_matrix ctm,
	fz_colorspace *colorspace, const float *color, float alpha, fz_color_params color_params)
{
	fz_test_device *dev = (fz_test_device*)dev_;

	if (dev->resolved == 0)
	{
		/* We assume that at least some of the image pixels are non-zero */
		fz_test_color(ctx, dev, colorspace, color, color_params);
	}
	if (dev->passthrough)
		fz_fill_image_mask(ctx, dev->passthrough, image, ctm, colorspace, color, alpha, color_params);
}