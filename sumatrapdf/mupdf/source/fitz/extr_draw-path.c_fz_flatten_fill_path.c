#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_rasterizer ;
typedef  int /*<<< orphan*/  fz_path ;
typedef  void* fz_matrix ;
typedef  int /*<<< orphan*/  fz_irect ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_6__ {scalar_t__ x; scalar_t__ y; } ;
struct TYPE_5__ {scalar_t__ x; scalar_t__ y; } ;
struct TYPE_7__ {float flatness; TYPE_2__ b; TYPE_1__ c; void* ctm; int /*<<< orphan*/ * rast; } ;
typedef  TYPE_3__ flatten_arg ;

/* Variables and functions */
 int /*<<< orphan*/  flatten_proc ; 
 int /*<<< orphan*/  fz_bound_rasterizer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_gap_rasterizer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_intersect_irect (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int fz_is_empty_irect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_postindex_rasterizer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ fz_reset_rasterizer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  fz_walk_path (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  line (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

int
fz_flatten_fill_path(fz_context *ctx, fz_rasterizer *rast, const fz_path *path, fz_matrix ctm, float flatness, const fz_irect *scissor, fz_irect *bbox)
{
	flatten_arg arg;

	if (fz_reset_rasterizer(ctx, rast, *scissor))
	{
		arg.rast = rast;
		arg.ctm = ctm;
		arg.flatness = flatness;
		arg.b.x = arg.b.y = arg.c.x = arg.c.y = 0;

		fz_walk_path(ctx, path, &flatten_proc, &arg);
		if (arg.c.x != arg.b.x || arg.c.y != arg.b.y)
			line(ctx, rast, ctm, arg.c.x, arg.c.y, arg.b.x, arg.b.y);

		fz_gap_rasterizer(ctx, rast);

		fz_postindex_rasterizer(ctx, rast);
	}

	arg.rast = rast;
	arg.ctm = ctm;
	arg.flatness = flatness;
	arg.b.x = arg.b.y = arg.c.x = arg.c.y = 0;

	fz_walk_path(ctx, path, &flatten_proc, &arg);
	if (arg.c.x != arg.b.x || arg.c.y != arg.b.y)
		line(ctx, rast, ctm, arg.c.x, arg.c.y, arg.b.x, arg.b.y);

	fz_gap_rasterizer(ctx, rast);

	if (!bbox)
		return 0;

	*bbox = fz_bound_rasterizer(ctx, rast);
	return fz_is_empty_irect(fz_intersect_irect(*bbox, *scissor));
}