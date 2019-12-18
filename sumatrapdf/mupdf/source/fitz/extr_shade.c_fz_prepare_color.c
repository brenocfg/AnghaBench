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
struct TYPE_3__ {int /*<<< orphan*/  process_arg; int /*<<< orphan*/  (* prepare ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,float*) ;} ;
typedef  TYPE_1__ fz_mesh_processor ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,float*) ; 

__attribute__((used)) static inline void
fz_prepare_color(fz_context *ctx, fz_mesh_processor *painter, fz_vertex *v, float *c)
{
	if (painter->prepare)
	{
		painter->prepare(ctx, painter->process_arg, v, c);
	}
}