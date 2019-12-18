#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {float x; float y; } ;
struct TYPE_8__ {TYPE_2__ cur; TYPE_1__* stroke; } ;
typedef  TYPE_3__ sctx ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_6__ {int /*<<< orphan*/  end_cap; int /*<<< orphan*/  start_cap; } ;

/* Variables and functions */
 int /*<<< orphan*/  fz_stroke_flush (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_stroke_moveto (int /*<<< orphan*/ *,TYPE_3__*,float,float) ; 

__attribute__((used)) static void
stroke_moveto(fz_context *ctx, void *s_, float x, float y)
{
	sctx *s = (sctx *)s_;

	fz_stroke_flush(ctx, s, s->stroke->start_cap, s->stroke->end_cap);
	fz_stroke_moveto(ctx, s, x, y);
	s->cur.x = x;
	s->cur.y = y;
}