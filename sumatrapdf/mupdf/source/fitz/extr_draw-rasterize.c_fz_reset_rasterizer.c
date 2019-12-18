#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int (* reset ) (int /*<<< orphan*/ *,TYPE_4__*) ;} ;
struct TYPE_13__ {void* y1; void* x1; void* y0; void* x0; } ;
struct TYPE_12__ {int x0; int y0; int x1; int y1; } ;
struct TYPE_15__ {TYPE_3__ fns; TYPE_2__ bbox; TYPE_1__ clip; } ;
typedef  TYPE_4__ fz_rasterizer ;
struct TYPE_16__ {int const x0; int const x1; int const y0; int const y1; } ;
typedef  TYPE_5__ fz_irect ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 void* BBOX_MAX ; 
 void* BBOX_MIN ; 
 scalar_t__ fz_is_infinite_irect (TYPE_5__) ; 
 int fz_rasterizer_aa_hscale (TYPE_4__*) ; 
 int fz_rasterizer_aa_vscale (TYPE_4__*) ; 
 int stub1 (int /*<<< orphan*/ *,TYPE_4__*) ; 

int fz_reset_rasterizer(fz_context *ctx, fz_rasterizer *rast, fz_irect clip)
{
	const int hscale = fz_rasterizer_aa_hscale(rast);
	const int vscale = fz_rasterizer_aa_vscale(rast);

	if (fz_is_infinite_irect(clip))
	{
		rast->clip.x0 = rast->clip.y0 = BBOX_MIN;
		rast->clip.x1 = rast->clip.y1 = BBOX_MAX;
	}
	else {
		rast->clip.x0 = clip.x0 * hscale;
		rast->clip.x1 = clip.x1 * hscale;
		rast->clip.y0 = clip.y0 * vscale;
		rast->clip.y1 = clip.y1 * vscale;
	}

	rast->bbox.x0 = rast->bbox.y0 = BBOX_MAX;
	rast->bbox.x1 = rast->bbox.y1 = BBOX_MIN;
	if (rast->fns.reset)
		return rast->fns.reset(ctx, rast);
	return 0;
}