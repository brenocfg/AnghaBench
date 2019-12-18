#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct window_pane {int dummy; } ;
struct window {struct window_pane* active; } ;
struct tty {int dummy; } ;
struct session {TYPE_1__* curw; } ;
struct screen_redraw_ctx {size_t ox; size_t oy; int pane_status; size_t statuslines; scalar_t__ statustop; struct client* c; } ;
struct grid_cell {int dummy; } ;
struct client {struct tty tty; struct session* session; } ;
struct TYPE_4__ {struct window_pane* wp; } ;
struct TYPE_3__ {struct window* window; } ;

/* Variables and functions */
 int /*<<< orphan*/ * CELL_BORDERS ; 
 size_t CELL_INSIDE ; 
 TYPE_2__ marked_pane ; 
 size_t screen_redraw_check_cell (struct client*,size_t,size_t,int,struct window_pane**) ; 
 int screen_redraw_check_is (size_t,size_t,size_t,int,struct window*,struct window_pane*,struct window_pane*) ; 
 scalar_t__ server_is_marked (struct session*,TYPE_1__*,struct window_pane*) ; 
 int /*<<< orphan*/  tty_attributes (struct tty*,struct grid_cell*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_cursor (struct tty*,size_t,size_t) ; 
 int /*<<< orphan*/  tty_putc (struct tty*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
screen_redraw_draw_borders_cell(struct screen_redraw_ctx *ctx, u_int i, u_int j,
    struct grid_cell *m_active_gc, struct grid_cell *active_gc,
    struct grid_cell *m_other_gc, struct grid_cell *other_gc)
{
	struct client		*c = ctx->c;
	struct session		*s = c->session;
	struct window		*w = s->curw->window;
	struct tty		*tty = &c->tty;
	struct window_pane	*wp;
	struct window_pane	*active = w->active;
	struct window_pane	*marked = marked_pane.wp;
	u_int			 type, x = ctx->ox + i, y = ctx->oy + j;
	int			 flag, pane_status = ctx->pane_status;

	type = screen_redraw_check_cell(c, x, y, pane_status, &wp);
	if (type == CELL_INSIDE)
		return;
	flag = screen_redraw_check_is(x, y, type, pane_status, w, active, wp);

	if (server_is_marked(s, s->curw, marked_pane.wp) &&
	    screen_redraw_check_is(x, y, type, pane_status, w, marked, wp)) {
		if (flag)
			tty_attributes(tty, m_active_gc, NULL);
		else
			tty_attributes(tty, m_other_gc, NULL);
	} else if (flag)
		tty_attributes(tty, active_gc, NULL);
	else
		tty_attributes(tty, other_gc, NULL);
	if (ctx->statustop)
		tty_cursor(tty, i, ctx->statuslines + j);
	else
		tty_cursor(tty, i, j);
	tty_putc(tty, CELL_BORDERS[type]);
}