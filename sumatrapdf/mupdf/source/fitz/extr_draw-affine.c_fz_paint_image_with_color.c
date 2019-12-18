#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int n; } ;
typedef  TYPE_1__ fz_pixmap ;
typedef  int /*<<< orphan*/  fz_overprint ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_irect ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fz_paint_image_imp (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/  const*,TYPE_1__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int,int,int /*<<< orphan*/  const*) ; 

void
fz_paint_image_with_color(fz_context *ctx, fz_pixmap *dst, const fz_irect *scissor, fz_pixmap *shape, fz_pixmap *group_alpha, fz_pixmap *img, fz_matrix ctm, const byte *color, int lerp_allowed, int as_tiled, const fz_overprint *eop)
{
	assert(img->n == 1);
	fz_paint_image_imp(ctx, dst, scissor, shape, group_alpha, img, ctm, color, 255, lerp_allowed, as_tiled, eop);
}