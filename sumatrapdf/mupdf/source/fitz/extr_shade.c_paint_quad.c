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
typedef  int /*<<< orphan*/  fz_vertex ;
struct TYPE_3__ {int /*<<< orphan*/  process_arg; int /*<<< orphan*/  (* process ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ fz_mesh_processor ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
paint_quad(fz_context *ctx, fz_mesh_processor *painter, fz_vertex *v0, fz_vertex *v1, fz_vertex *v2, fz_vertex *v3)
{
	/* For a quad with corners (in clockwise or anticlockwise order) are
	 * v0, v1, v2, v3. We can choose to split in in various different ways.
	 * Arbitrarily we can pick v0, v1, v3 for the first triangle. We then
	 * have to choose between v1, v2, v3 or v3, v2, v1 (or their equivalent
	 * rotations) for the second triangle.
	 *
	 * v1, v2, v3 has the property that both triangles share the same
	 * winding (useful if we were ever doing simple back face culling).
	 *
	 * v3, v2, v1 has the property that all the 'shared' edges (both
	 * within this quad, and with adjacent quads) are walked in the same
	 * direction every time. This can be useful in that depending on the
	 * implementation/rounding etc walking from A -> B can hit different
	 * pixels than walking from B->A.
	 *
	 * In the event neither of these things matter at the moment, as all
	 * the process functions where it matters order the edges from top to
	 * bottom before walking them.
	 */
	if (painter->process)
	{
		painter->process(ctx, painter->process_arg, v0, v1, v3);
		painter->process(ctx, painter->process_arg, v3, v2, v1);
	}
}