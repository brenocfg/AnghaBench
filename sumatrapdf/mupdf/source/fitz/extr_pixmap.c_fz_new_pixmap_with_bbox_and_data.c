#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_separations ;
struct TYPE_6__ {int x; scalar_t__ y; } ;
typedef  TYPE_1__ fz_pixmap ;
struct TYPE_7__ {int x1; int x0; scalar_t__ y0; scalar_t__ y1; } ;
typedef  TYPE_2__ fz_irect ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;

/* Variables and functions */
 int fz_colorspace_n (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int fz_count_active_separations (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* fz_new_pixmap_with_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ *,int,int,unsigned char*) ; 

fz_pixmap *
fz_new_pixmap_with_bbox_and_data(fz_context *ctx, fz_colorspace *colorspace, fz_irect bbox, fz_separations *seps, int alpha, unsigned char *samples)
{
	int w = bbox.x1 - bbox.x0;
	int stride;
	int s = fz_count_active_separations(ctx, seps);
	fz_pixmap *pixmap;
	if (!colorspace && s == 0) alpha = 1;
	stride = (fz_colorspace_n(ctx, colorspace) + s + alpha) * w;
	pixmap = fz_new_pixmap_with_data(ctx, colorspace, w, bbox.y1 - bbox.y0, seps, alpha, stride, samples);
	pixmap->x = bbox.x0;
	pixmap->y = bbox.y0;
	return pixmap;
}