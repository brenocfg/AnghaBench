#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_rect ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;
typedef  int /*<<< orphan*/  fz_color_params ;
struct TYPE_2__ {int /*<<< orphan*/  ignore; } ;
typedef  TYPE_1__ fz_bbox_device ;

/* Variables and functions */
 int /*<<< orphan*/  fz_bbox_add_rect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
fz_bbox_begin_mask(fz_context *ctx, fz_device *dev, fz_rect rect, int luminosity, fz_colorspace *colorspace, const float *color, fz_color_params color_params)
{
	fz_bbox_device *bdev = (fz_bbox_device*)dev;
	fz_bbox_add_rect(ctx, dev, rect, 1);
	bdev->ignore++;
}