#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {float x; float y; } ;
struct TYPE_4__ {float x0; float x1; float y0; float y1; } ;
struct sctx {int toggle; int cap; float phase; float dash_total; int dash_len; float* dash_list; size_t offset; TYPE_3__ dash_cur; TYPE_1__ rect; TYPE_2__* stroke; } ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_5__ {int dash_cap; } ;

/* Variables and functions */
 int /*<<< orphan*/  fz_stroke_flush (int /*<<< orphan*/ *,struct sctx*,int,int) ; 
 int /*<<< orphan*/  fz_stroke_lineto (int /*<<< orphan*/ *,struct sctx*,float,float,int) ; 
 int /*<<< orphan*/  fz_stroke_moveto (int /*<<< orphan*/ *,struct sctx*,float,float) ; 
 float sqrtf (float) ; 

__attribute__((used)) static void
fz_dash_lineto(fz_context *ctx, struct sctx *s, float bx, float by, int from_bezier)
{
	float dx, dy, d;
	float total, used, ratio, tail;
	float ax, ay;
	float mx, my;
	float old_bx, old_by;
	int n;
	int dash_cap = s->stroke->dash_cap;

	ax = s->dash_cur.x;
	ay = s->dash_cur.y;
	dx = bx - ax;
	dy = by - ay;
	used = 0;
	tail = 0;
	total = sqrtf(dx * dx + dy * dy);

	/* If a is off screen, bring it onto the screen. First
	 * horizontally... */
	if ((d = s->rect.x0 - ax) > 0)
	{
		if (bx < s->rect.x0)
		{
			/* Entirely off screen */
			tail = total;
			old_bx = bx;
			old_by = by;
			goto adjust_for_tail;
		}
		ax = s->rect.x0;	/* d > 0, dx > 0 */
		goto a_moved_horizontally;
	}
	else if (d < 0 && (d = (s->rect.x1 - ax)) < 0)
	{
		if (bx > s->rect.x1)
		{
			/* Entirely off screen */
			tail = total;
			old_bx = bx;
			old_by = by;
			goto adjust_for_tail;
		}
		ax = s->rect.x1;	/* d < 0, dx < 0 */
a_moved_horizontally:	/* d and dx have the same sign */
		ay += dy * d/dx;
		used = total * d/dx;
		total -= used;
		dx = bx - ax;
		dy = by - ay;
	}
	/* Then vertically... */
	if ((d = s->rect.y0 - ay) > 0)
	{
		if (by < s->rect.y0)
		{
			/* Entirely off screen */
			tail = total;
			old_bx = bx;
			old_by = by;
			goto adjust_for_tail;
		}
		ay = s->rect.y0;	/* d > 0, dy > 0 */
		goto a_moved_vertically;
	}
	else if (d < 0 && (d = (s->rect.y1 - ay)) < 0)
	{
		if (by > s->rect.y1)
		{
			/* Entirely off screen */
			tail = total;
			old_bx = bx;
			old_by = by;
			goto adjust_for_tail;
		}
		ay = s->rect.y1;	/* d < 0, dy < 0 */
a_moved_vertically:	/* d and dy have the same sign */
		ax += dx * d/dy;
		d = total * d/dy;
		total -= d;
		used += d;
		dx = bx - ax;
		dy = by - ay;
	}
	if (used != 0.0f)
	{
		/* Update the position in the dash array */
		if (s->toggle)
		{
			fz_stroke_lineto(ctx, s, ax, ay, from_bezier);
		}
		else
		{
			fz_stroke_flush(ctx, s, s->cap, s->stroke->dash_cap);
			s->cap = s->stroke->dash_cap;
			fz_stroke_moveto(ctx, s, ax, ay);
		}
		used += s->phase;
		n = used/s->dash_total;
		used -= n*s->dash_total;
		if (n & s->dash_len & 1)
			s->toggle = !s->toggle;
		while (used >= s->dash_list[s->offset])
		{
			used -= s->dash_list[s->offset];
			s->offset++;
			if (s->offset == s->dash_len)
				s->offset = 0;
			s->toggle = !s->toggle;
		}
		if (s->toggle)
		{
			fz_stroke_lineto(ctx, s, ax, ay, from_bezier);
		}
		else
		{
			fz_stroke_flush(ctx, s, s->cap, s->stroke->dash_cap);
			s->cap = s->stroke->dash_cap;
			fz_stroke_moveto(ctx, s, ax, ay);
		}
		s->phase = used;
		used = 0;
	}

	/* Now if bx is off screen, bring it back */
	if ((d = bx - s->rect.x0) < 0)
	{
		old_bx = bx;
		old_by = by;
		bx = s->rect.x0;	/* d < 0, dx < 0 */
		goto b_moved_horizontally;
	}
	else if (d > 0 && (d = (bx - s->rect.x1)) > 0)
	{
		old_bx = bx;
		old_by = by;
		bx = s->rect.x1;	/* d > 0, dx > 0 */
b_moved_horizontally:	/* d and dx have the same sign */
		by -= dy * d/dx;
		tail = total * d/dx;
		total -= tail;
		dx = bx - ax;
		dy = by - ay;
	}
	/* Then vertically... */
	if ((d = by - s->rect.y0) < 0)
	{
		old_bx = bx;
		old_by = by;
		by = s->rect.y0;	/* d < 0, dy < 0 */
		goto b_moved_vertically;
	}
	else if (d > 0 && (d = (by - s->rect.y1)) > 0)
	{
		float t;
		old_bx = bx;
		old_by = by;
		by = s->rect.y1;	/* d > 0, dy > 0 */
b_moved_vertically:	/* d and dy have the same sign */
		bx -= dx * d/dy;
		t = total * d/dy;
		tail += t;
		total -= t;
		dx = bx - ax;
		dy = by - ay;
	}

	while (total - used > s->dash_list[s->offset] - s->phase)
	{
		used += s->dash_list[s->offset] - s->phase;
		ratio = used / total;
		mx = ax + ratio * dx;
		my = ay + ratio * dy;

		if (s->toggle)
		{
			fz_stroke_lineto(ctx, s, mx, my, from_bezier);
		}
		else
		{
			fz_stroke_flush(ctx, s, s->cap, dash_cap);
			s->cap = dash_cap;
			fz_stroke_moveto(ctx, s, mx, my);
		}

		s->toggle = !s->toggle;
		s->phase = 0;
		s->offset ++;
		if (s->offset == s->dash_len)
			s->offset = 0;
	}

	s->phase += total - used;

	if (tail == 0.0f)
	{
		s->dash_cur.x = bx;
		s->dash_cur.y = by;

		if (s->toggle)
		{
			fz_stroke_lineto(ctx, s, bx, by, from_bezier);
		}
	}
	else
	{
adjust_for_tail:
		s->dash_cur.x = old_bx;
		s->dash_cur.y = old_by;
		/* Update the position in the dash array */
		if (s->toggle)
		{
			fz_stroke_lineto(ctx, s, old_bx, old_by, from_bezier);
		}
		else
		{
			fz_stroke_flush(ctx, s, s->cap, dash_cap);
			s->cap = dash_cap;
			fz_stroke_moveto(ctx, s, old_bx, old_by);
		}
		tail += s->phase;
		n = tail/s->dash_total;
		tail -= n*s->dash_total;
		if (n & s->dash_len & 1)
			s->toggle = !s->toggle;
		while (tail > s->dash_list[s->offset])
		{
			tail -= s->dash_list[s->offset];
			s->offset++;
			if (s->offset == s->dash_len)
				s->offset = 0;
			s->toggle = !s->toggle;
		}
		if (s->toggle)
		{
			fz_stroke_lineto(ctx, s, old_bx, old_by, from_bezier);
		}
		else
		{
			fz_stroke_flush(ctx, s, s->cap, dash_cap);
			s->cap = dash_cap;
			fz_stroke_moveto(ctx, s, old_bx, old_by);
		}
		s->phase = tail;
	}
}