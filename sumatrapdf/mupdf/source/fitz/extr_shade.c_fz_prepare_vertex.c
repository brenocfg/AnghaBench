#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  p; } ;
typedef  TYPE_1__ fz_vertex ;
struct TYPE_7__ {int /*<<< orphan*/  process_arg; int /*<<< orphan*/  (* prepare ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,float*) ;} ;
typedef  TYPE_2__ fz_mesh_processor ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_transform_point_xy (float,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,float*) ; 

__attribute__((used)) static inline void
fz_prepare_vertex(fz_context *ctx, fz_mesh_processor *painter, fz_vertex *v, fz_matrix ctm, float x, float y, float *c)
{
	v->p = fz_transform_point_xy(x, y, ctm);
	if (painter->prepare)
	{
		painter->prepare(ctx, painter->process_arg, v, c);
	}
}