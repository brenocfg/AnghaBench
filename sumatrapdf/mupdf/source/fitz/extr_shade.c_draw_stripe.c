#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tensor_patch ;
struct TYPE_4__ {int /*<<< orphan*/  ncomp; } ;
typedef  TYPE_1__ fz_mesh_processor ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  split_stripe (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  triangulate_patch (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
draw_stripe(fz_context *ctx, fz_mesh_processor *painter, tensor_patch *p, int depth)
{
	tensor_patch s0, s1;

	/* split patch into two half-height patches */
	split_stripe(p, &s0, &s1, painter->ncomp);

	depth--;
	if (depth == 0)
	{
		/* if no more subdividing, draw two new patches... */
		triangulate_patch(ctx, painter, &s1);
		triangulate_patch(ctx, painter, &s0);
	}
	else
	{
		/* ...otherwise, continue subdividing. */
		draw_stripe(ctx, painter, &s1, depth);
		draw_stripe(ctx, painter, &s0, depth);
	}
}