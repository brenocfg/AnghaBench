#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int h; int stride; int /*<<< orphan*/  samples; int /*<<< orphan*/  alpha; int /*<<< orphan*/  seps; int /*<<< orphan*/  w; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  colorspace; } ;
typedef  TYPE_1__ fz_pixmap ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_make_irect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* fz_new_pixmap_with_bbox (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

fz_pixmap *fz_clone_pixmap(fz_context *ctx, fz_pixmap *old)
{
	fz_pixmap *pix = fz_new_pixmap_with_bbox(ctx, old->colorspace, fz_make_irect(old->x, old->y, old->w, old->h), old->seps, old->alpha);
	memcpy(pix->samples, old->samples, pix->stride * pix->h);
	return pix;
}