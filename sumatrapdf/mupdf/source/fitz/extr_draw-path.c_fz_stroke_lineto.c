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
struct TYPE_11__ {int sn; scalar_t__ dot; scalar_t__ cap; int from_bezier; TYPE_2__* beg; TYPE_1__* seg; scalar_t__ dash_list; int /*<<< orphan*/  linewidth; } ;
typedef  TYPE_3__ sctx ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_10__ {float x; float y; } ;
struct TYPE_9__ {float x; float y; } ;

/* Variables and functions */
 scalar_t__ FZ_LINECAP_ROUND ; 
 scalar_t__ NON_NULL_LINE ; 
 scalar_t__ NULL_LINE ; 
 scalar_t__ ONLY_MOVES ; 
 scalar_t__ find_normal_vectors (float,float,int /*<<< orphan*/ ,float*,float*) ; 
 int /*<<< orphan*/  fz_add_horiz_rect (int /*<<< orphan*/ *,TYPE_3__*,float,float,float,float) ; 
 int /*<<< orphan*/  fz_add_line (int /*<<< orphan*/ *,TYPE_3__*,float,float,float,float,int) ; 
 int /*<<< orphan*/  fz_add_line_join (int /*<<< orphan*/ *,TYPE_3__*,float,float,float,float,float,float,int) ; 
 int /*<<< orphan*/  fz_add_vert_rect (int /*<<< orphan*/ *,TYPE_3__*,float,float,float,float) ; 

__attribute__((used)) static void
fz_stroke_lineto(fz_context *ctx, sctx *s, float x, float y, int from_bezier)
{
	float ox = s->seg[s->sn-1].x;
	float oy = s->seg[s->sn-1].y;
	float dx = x - ox;
	float dy = y - oy;
	float dlx, dly;

	if (find_normal_vectors(dx, dy, s->linewidth, &dlx, &dly))
	{
		if (s->dot == ONLY_MOVES && (s->cap == FZ_LINECAP_ROUND || s->dash_list))
			s->dot = NULL_LINE;
		return;
	}
	s->dot = NON_NULL_LINE;

	if (s->sn == 2)
		fz_add_line_join(ctx, s, s->seg[0].x, s->seg[0].y, ox, oy, x, y, s->from_bezier & from_bezier);

#if 1
	if (0 && dx == 0)
	{
		fz_add_vert_rect(ctx, s, ox - dlx, oy, x + dlx, y);
	}
	else if (dy == 0)
	{
		fz_add_horiz_rect(ctx, s, ox, oy - dly, x, y + dly);
	}
	else
#endif
	{

		fz_add_line(ctx, s, ox - dlx, oy - dly, x - dlx, y - dly, 0);
		fz_add_line(ctx, s, x + dlx, y + dly, ox + dlx, oy + dly, 1);
	}

	if (s->sn == 2)
	{
		s->seg[0] = s->seg[1];
		s->seg[1].x = x;
		s->seg[1].y = y;
	}
	else
	{
		s->seg[1].x = s->beg[1].x = x;
		s->seg[1].y = s->beg[1].y = y;
		s->sn = 2;
	}
	s->from_bezier = from_bezier;
}