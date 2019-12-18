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
typedef  int /*<<< orphan*/  time_t ;
struct window_pane {int fd; int flags; int /*<<< orphan*/  status; int /*<<< orphan*/  base; int /*<<< orphan*/  options; int /*<<< orphan*/ * event; struct window* window; } ;
struct window {int /*<<< orphan*/  panes; } ;
struct screen_write_ctx {int /*<<< orphan*/  s; } ;
struct grid_cell {int dummy; } ;

/* Variables and functions */
 int PANE_REDRAW ; 
 int PANE_STATUSDRAWN ; 
 int PANE_STATUSREADY ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WEXITSTATUS (int /*<<< orphan*/ ) ; 
 scalar_t__ WIFEXITED (int /*<<< orphan*/ ) ; 
 scalar_t__ WIFSIGNALED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WTERMSIG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  ctime_r (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  grid_default_cell ; 
 int /*<<< orphan*/  layout_close_pane (struct window_pane*) ; 
 int /*<<< orphan*/  memcpy (struct grid_cell*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  notify_pane (char*,struct window_pane*) ; 
 scalar_t__ options_get_number (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ screen_size_y (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_write_cursormove (struct screen_write_ctx*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_write_linefeed (struct screen_write_ctx*,int,int) ; 
 int /*<<< orphan*/  screen_write_nputs (struct screen_write_ctx*,int,struct grid_cell*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  screen_write_scrollregion (struct screen_write_ctx*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  screen_write_start (struct screen_write_ctx*,struct window_pane*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  screen_write_stop (struct screen_write_ctx*) ; 
 int /*<<< orphan*/  server_kill_window (struct window*) ; 
 int /*<<< orphan*/  server_redraw_window (struct window*) ; 
 int /*<<< orphan*/  server_unzoom_window (struct window*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  utempter_remove_record (int) ; 
 int /*<<< orphan*/  window_remove_pane (struct window*,struct window_pane*) ; 

void
server_destroy_pane(struct window_pane *wp, int notify)
{
	struct window		*w = wp->window;
	struct screen_write_ctx	 ctx;
	struct grid_cell	 gc;
	time_t			 t;
	char			 tim[26];

	if (wp->fd != -1) {
#ifdef HAVE_UTEMPTER
		utempter_remove_record(wp->fd);
#endif
		bufferevent_free(wp->event);
		wp->event = NULL;
		close(wp->fd);
		wp->fd = -1;
	}

	if (options_get_number(wp->options, "remain-on-exit")) {
		if (~wp->flags & PANE_STATUSREADY)
			return;

		if (wp->flags & PANE_STATUSDRAWN)
			return;
		wp->flags |= PANE_STATUSDRAWN;

		if (notify)
			notify_pane("pane-died", wp);

		screen_write_start(&ctx, wp, &wp->base);
		screen_write_scrollregion(&ctx, 0, screen_size_y(ctx.s) - 1);
		screen_write_cursormove(&ctx, 0, screen_size_y(ctx.s) - 1, 0);
		screen_write_linefeed(&ctx, 1, 8);
		memcpy(&gc, &grid_default_cell, sizeof gc);

		time(&t);
		ctime_r(&t, tim);

		if (WIFEXITED(wp->status)) {
			screen_write_nputs(&ctx, -1, &gc,
			    "Pane is dead (status %d, %s)",
			    WEXITSTATUS(wp->status),
			    tim);
		} else if (WIFSIGNALED(wp->status)) {
			screen_write_nputs(&ctx, -1, &gc,
			    "Pane is dead (signal %d, %s)",
			    WTERMSIG(wp->status),
			    tim);
		}

		screen_write_stop(&ctx);
		wp->flags |= PANE_REDRAW;
		return;
	}

	if (notify)
		notify_pane("pane-exited", wp);

	server_unzoom_window(w);
	layout_close_pane(wp);
	window_remove_pane(w, wp);

	if (TAILQ_EMPTY(&w->panes))
		server_kill_window(w);
	else
		server_redraw_window(w);
}