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
struct TYPE_8__ {int sn; scalar_t__ dot; int /*<<< orphan*/  rast; scalar_t__ from_bezier; TYPE_1__* beg; TYPE_1__* seg; } ;
typedef  TYPE_2__ sctx ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_7__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 scalar_t__ NULL_LINE ; 
 scalar_t__ ONLY_MOVES ; 
 int /*<<< orphan*/  fz_add_line_dot (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_add_line_join (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_gap_rasterizer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_stroke_lineto (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fz_stroke_closepath(fz_context *ctx, sctx *s)
{
	if (s->sn == 2)
	{
		fz_stroke_lineto(ctx, s, s->beg[0].x, s->beg[0].y, 0);
		/* fz_stroke_lineto will *normally* end up with s->seg[1] being the x,y coords passed in.
		 * As such, the following line should draw a linejoin between the closing segment of this
		 * subpath (seg[0]->seg[1]) == (seg[0]->beg[0]) and the first segment of this subpath
		 * (beg[0]->beg[1]).
		 * In cases where the line was already at an x,y infinitesimally close to s->beg[0],
		 * fz_stroke_lineto may exit without doing any processing. This leaves seg[0]->seg[1]
		 * pointing at the penultimate line segment. Thus this draws a linejoin between that
		 * penultimate segment and the end segment. This is what we want. */
		fz_add_line_join(ctx, s, s->seg[0].x, s->seg[0].y, s->beg[0].x, s->beg[0].y, s->beg[1].x, s->beg[1].y, 0);
	}
	else if (s->dot == NULL_LINE)
		fz_add_line_dot(ctx, s, s->beg[0].x, s->beg[0].y);

	s->seg[0] = s->beg[0];
	s->sn = 1;
	s->dot = ONLY_MOVES;
	s->from_bezier = 0;

	fz_gap_rasterizer(ctx, s->rast);
}