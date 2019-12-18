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
struct window_pane {struct window* window; } ;
struct window {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  layout_close_pane (struct window_pane*) ; 
 int /*<<< orphan*/  recalculate_sizes () ; 
 int /*<<< orphan*/  server_kill_window (struct window*) ; 
 int /*<<< orphan*/  server_redraw_window (struct window*) ; 
 int /*<<< orphan*/  server_unzoom_window (struct window*) ; 
 int window_count_panes (struct window*) ; 
 int /*<<< orphan*/  window_remove_pane (struct window*,struct window_pane*) ; 

void
server_kill_pane(struct window_pane *wp)
{
	struct window	*w = wp->window;

	if (window_count_panes(w) == 1) {
		server_kill_window(w);
		recalculate_sizes();
	} else {
		server_unzoom_window(w);
		layout_close_pane(wp);
		window_remove_pane(w, wp);
		server_redraw_window(w);
	}
}