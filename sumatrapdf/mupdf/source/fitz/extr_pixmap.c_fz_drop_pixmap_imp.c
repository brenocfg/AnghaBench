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
typedef  int /*<<< orphan*/  fz_storable ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  underlying; struct TYPE_3__* samples; int /*<<< orphan*/  seps; int /*<<< orphan*/  colorspace; } ;
typedef  TYPE_1__ fz_pixmap ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int FZ_PIXMAP_FLAG_FREE_SAMPLES ; 
 int /*<<< orphan*/  fz_drop_colorspace (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_pixmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_separations (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_1__*) ; 

void
fz_drop_pixmap_imp(fz_context *ctx, fz_storable *pix_)
{
	fz_pixmap *pix = (fz_pixmap *)pix_;

	fz_drop_colorspace(ctx, pix->colorspace);
	fz_drop_separations(ctx, pix->seps);
	if (pix->flags & FZ_PIXMAP_FLAG_FREE_SAMPLES)
		fz_free(ctx, pix->samples);
	fz_drop_pixmap(ctx, pix->underlying);
	fz_free(ctx, pix);
}