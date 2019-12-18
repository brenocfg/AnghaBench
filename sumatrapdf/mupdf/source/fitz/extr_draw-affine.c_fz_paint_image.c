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
typedef  int /*<<< orphan*/  fz_pixmap ;
typedef  int /*<<< orphan*/  fz_overprint ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_irect ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_paint_image_imp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/  const*) ; 

void
fz_paint_image(fz_context *ctx, fz_pixmap *dst, const fz_irect *scissor, fz_pixmap *shape, fz_pixmap *group_alpha, fz_pixmap *img, fz_matrix ctm, int alpha, int lerp_allowed, int as_tiled, const fz_overprint *eop)
{
	fz_paint_image_imp(ctx, dst, scissor, shape, group_alpha, img, ctm, NULL, alpha, lerp_allowed, as_tiled, eop);
}