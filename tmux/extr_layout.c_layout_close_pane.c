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
struct window_pane {int /*<<< orphan*/  layout_cell; struct window* window; } ;
struct window {int /*<<< orphan*/ * layout_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  layout_destroy_cell (struct window*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  layout_fix_offsets (struct window*) ; 
 int /*<<< orphan*/  layout_fix_panes (struct window*) ; 
 int /*<<< orphan*/  notify_window (char*,struct window*) ; 

void
layout_close_pane(struct window_pane *wp)
{
	struct window	*w = wp->window;

	/* Remove the cell. */
	layout_destroy_cell(w, wp->layout_cell, &w->layout_root);

	/* Fix pane offsets and sizes. */
	if (w->layout_root != NULL) {
		layout_fix_offsets(w);
		layout_fix_panes(w);
	}
	notify_window("window-layout-changed", w);
}