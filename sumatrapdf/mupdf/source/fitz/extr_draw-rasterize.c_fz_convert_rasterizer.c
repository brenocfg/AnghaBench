#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  (* convert ) (int /*<<< orphan*/ *,TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ;} ;
struct TYPE_8__ {TYPE_1__ fns; } ;
typedef  TYPE_2__ fz_rasterizer ;
typedef  int /*<<< orphan*/  fz_pixmap ;
typedef  int /*<<< orphan*/  fz_overprint ;
typedef  int /*<<< orphan*/  fz_irect ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_bound_rasterizer (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  fz_clip_rasterizer (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  fz_intersect_irect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_is_empty_irect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_pixmap_bbox_no_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 

void fz_convert_rasterizer(fz_context *ctx, fz_rasterizer *r, int eofill, fz_pixmap *pix, unsigned char *colorbv, fz_overprint *eop)
{
	fz_irect clip = fz_bound_rasterizer(ctx, r);
	clip = fz_intersect_irect(clip, fz_pixmap_bbox_no_ctx(pix));
	clip = fz_intersect_irect(clip, fz_clip_rasterizer(ctx, r));
	if (!fz_is_empty_irect(clip))
		r->fns.convert(ctx, r, eofill, &clip, pix, colorbv, eop);
}