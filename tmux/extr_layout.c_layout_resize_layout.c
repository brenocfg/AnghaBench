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
struct window {int dummy; } ;
struct layout_cell {int dummy; } ;
typedef  enum layout_type { ____Placeholder_layout_type } layout_type ;

/* Variables and functions */
 int /*<<< orphan*/  layout_fix_offsets (struct window*) ; 
 int /*<<< orphan*/  layout_fix_panes (struct window*) ; 
 int layout_resize_pane_grow (struct window*,struct layout_cell*,int,int,int) ; 
 int layout_resize_pane_shrink (struct window*,struct layout_cell*,int,int) ; 
 int /*<<< orphan*/  notify_window (char*,struct window*) ; 

void
layout_resize_layout(struct window *w, struct layout_cell *lc,
    enum layout_type type, int change, int opposite)
{
	int	needed, size;

	/* Grow or shrink the cell. */
	needed = change;
	while (needed != 0) {
		if (change > 0) {
			size = layout_resize_pane_grow(w, lc, type, needed,
			    opposite);
			needed -= size;
		} else {
			size = layout_resize_pane_shrink(w, lc, type, needed);
			needed += size;
		}

		if (size == 0)	/* no more change possible */
			break;
	}

	/* Fix cell offsets. */
	layout_fix_offsets(w);
	layout_fix_panes(w);
	notify_window("window-layout-changed", w);
}