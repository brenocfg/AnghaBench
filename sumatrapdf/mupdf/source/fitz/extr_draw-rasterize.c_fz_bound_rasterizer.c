#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ x1; scalar_t__ x0; scalar_t__ y1; scalar_t__ y0; } ;
struct TYPE_10__ {TYPE_1__ bbox; } ;
typedef  TYPE_2__ fz_rasterizer ;
struct TYPE_11__ {void* y1; void* x1; void* y0; void* x0; } ;
typedef  TYPE_3__ fz_irect ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 TYPE_3__ fz_empty_irect ; 
 void* fz_idiv (scalar_t__,int const) ; 
 void* fz_idiv_up (scalar_t__,int const) ; 
 int fz_rasterizer_aa_hscale (TYPE_2__ const*) ; 
 int fz_rasterizer_aa_vscale (TYPE_2__ const*) ; 

fz_irect
fz_bound_rasterizer(fz_context *ctx, const fz_rasterizer *rast)
{
	fz_irect bbox;
	const int hscale = fz_rasterizer_aa_hscale(rast);
	const int vscale = fz_rasterizer_aa_vscale(rast);

	if (rast->bbox.x1 < rast->bbox.x0 || rast->bbox.y1 < rast->bbox.y0)
	{
		bbox = fz_empty_irect;
	}
	else
	{
		bbox.x0 = fz_idiv(rast->bbox.x0, hscale);
		bbox.y0 = fz_idiv(rast->bbox.y0, vscale);
		bbox.x1 = fz_idiv_up(rast->bbox.x1, hscale);
		bbox.y1 = fz_idiv_up(rast->bbox.y1, vscale);
	}
	return bbox;
}