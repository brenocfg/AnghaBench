#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int sn; scalar_t__ dot; int /*<<< orphan*/  rast; TYPE_2__* beg; TYPE_1__* seg; } ;
typedef  TYPE_3__ sctx ;
typedef  int /*<<< orphan*/  fz_linecap ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_8__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_7__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 scalar_t__ NULL_LINE ; 
 int /*<<< orphan*/  fz_add_line_cap (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fz_add_line_dot (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_gap_rasterizer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fz_stroke_flush(fz_context *ctx, sctx *s, fz_linecap start_cap, fz_linecap end_cap)
{
	if (s->sn == 2)
	{
		fz_add_line_cap(ctx, s, s->beg[1].x, s->beg[1].y, s->beg[0].x, s->beg[0].y, start_cap, 2);
		fz_add_line_cap(ctx, s, s->seg[0].x, s->seg[0].y, s->seg[1].x, s->seg[1].y, end_cap, 0);
	}
	else if (s->dot == NULL_LINE)
		fz_add_line_dot(ctx, s, s->beg[0].x, s->beg[0].y);
	fz_gap_rasterizer(ctx, s->rast);
}