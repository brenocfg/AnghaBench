#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u_int ;
struct window_pane {struct window* window; } ;
struct window {int /*<<< orphan*/  offset_timer; } ;
struct timeval {int tv_usec; } ;
struct screen_write_ctx {struct screen* s; struct window_pane* wp; } ;
struct screen {int cx; int cy; } ;

/* Variables and functions */
 int /*<<< orphan*/  event_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evtimer_add (int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  evtimer_pending (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evtimer_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct window*) ; 
 int screen_size_x (struct screen*) ; 
 int screen_size_y (struct screen*) ; 
 int /*<<< orphan*/  screen_write_offset_timer ; 

__attribute__((used)) static void
screen_write_set_cursor(struct screen_write_ctx *ctx, int cx, int cy)
{
	struct window_pane	*wp = ctx->wp;
	struct window		*w;
	struct screen		*s = ctx->s;
	struct timeval		 tv = { .tv_usec = 10000 };

	if (cx != -1 && (u_int)cx == s->cx && cy != -1 && (u_int)cy == s->cy)
		return;

	if (cx != -1) {
		if ((u_int)cx > screen_size_x(s)) /* allow last column */
			cx = screen_size_x(s) - 1;
		s->cx = cx;
	}
	if (cy != -1) {
		if ((u_int)cy > screen_size_y(s) - 1)
			cy = screen_size_y(s) - 1;
		s->cy = cy;
	}

	if (wp == NULL)
		return;
	w = wp->window;

	if (!event_initialized(&w->offset_timer))
		evtimer_set(&w->offset_timer, screen_write_offset_timer, w);
	if (!evtimer_pending(&w->offset_timer, NULL))
		evtimer_add(&w->offset_timer, &tv);
}