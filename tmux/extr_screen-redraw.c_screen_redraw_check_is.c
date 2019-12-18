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
struct window_pane {scalar_t__ xoff; int sx; scalar_t__ yoff; int sy; } ;
struct window {int sx; int sy; } ;

/* Variables and functions */
 int CELL_INSIDE ; 
 int CELL_OUTSIDE ; 
 int PANE_STATUS_BOTTOM ; 
 int PANE_STATUS_OFF ; 
 int PANE_STATUS_TOP ; 
 int screen_redraw_cell_border1 (struct window_pane*,int,int) ; 
 int window_count_panes (struct window*) ; 

__attribute__((used)) static int
screen_redraw_check_is(u_int px, u_int py, int type, int pane_status,
    struct window *w, struct window_pane *wantwp, struct window_pane *wp)
{
	int	border;

	/* Is this off the active pane border? */
	border = screen_redraw_cell_border1(wantwp, px, py);
	if (border == 0 || border == -1)
		return (0);
	if (pane_status == PANE_STATUS_TOP && border == 4)
		return (0);
	if (pane_status == PANE_STATUS_BOTTOM && border == 3)
		return (0);

	/* If there are more than two panes, that's enough. */
	if (window_count_panes(w) != 2)
		return (1);

	/* Else if the cell is not a border cell, forget it. */
	if (wp == NULL || (type == CELL_OUTSIDE || type == CELL_INSIDE))
		return (1);

	/* With status lines mark the entire line. */
	if (pane_status != PANE_STATUS_OFF)
		return (1);

	/* Check if the pane covers the whole width. */
	if (wp->xoff == 0 && wp->sx == w->sx) {
		/* This can either be the top pane or the bottom pane. */
		if (wp->yoff == 0) { /* top pane */
			if (wp == wantwp)
				return (px <= wp->sx / 2);
			return (px > wp->sx / 2);
		}
		return (0);
	}

	/* Check if the pane covers the whole height. */
	if (wp->yoff == 0 && wp->sy == w->sy) {
		/* This can either be the left pane or the right pane. */
		if (wp->xoff == 0) { /* left pane */
			if (wp == wantwp)
				return (py <= wp->sy / 2);
			return (py > wp->sy / 2);
		}
		return (0);
	}

	return (1);
}