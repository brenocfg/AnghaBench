#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  fz_separations ;
typedef  int /*<<< orphan*/  fz_pixmap ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;

/* Variables and functions */
 int fz_colorspace_n (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int fz_count_active_separations (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fz_new_pixmap_with_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 

fz_pixmap *
fz_new_pixmap(fz_context *ctx, fz_colorspace *colorspace, int w, int h, fz_separations *seps, int alpha)
{
	int stride;
	int s = fz_count_active_separations(ctx, seps);
	if (!colorspace && s == 0) alpha = 1;
	stride = (fz_colorspace_n(ctx, colorspace) + s + alpha) * w;
	return fz_new_pixmap_with_data(ctx, colorspace, w, h, seps, alpha, stride, NULL);
}