#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct screen {int cx; int cy; TYPE_1__* grid; } ;
struct window_pane {scalar_t__ saved_cx; scalar_t__ saved_cy; int /*<<< orphan*/  flags; TYPE_2__* saved_grid; struct screen base; int /*<<< orphan*/  saved_cell; int /*<<< orphan*/  options; } ;
struct grid_cell {int dummy; } ;
struct TYPE_5__ {int sy; int sx; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRID_HISTORY ; 
 int /*<<< orphan*/  PANE_REDRAW ; 
 scalar_t__ UINT_MAX ; 
 int /*<<< orphan*/  grid_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  grid_duplicate_lines (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (struct grid_cell*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  options_get_number (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  screen_hsize (struct screen*) ; 
 int /*<<< orphan*/  screen_resize (struct screen*,int,int,int) ; 
 int screen_size_x (struct screen*) ; 
 int screen_size_y (struct screen*) ; 

void
window_pane_alternate_off(struct window_pane *wp, struct grid_cell *gc,
    int cursor)
{
	struct screen	*s = &wp->base;
	u_int		 sx, sy;

	if (!options_get_number(wp->options, "alternate-screen"))
		return;

	/*
	 * Restore the cursor position and cell. This happens even if not
	 * currently in the alternate screen.
	 */
	if (cursor && wp->saved_cx != UINT_MAX && wp->saved_cy != UINT_MAX) {
		s->cx = wp->saved_cx;
		if (s->cx > screen_size_x(s) - 1)
			s->cx = screen_size_x(s) - 1;
		s->cy = wp->saved_cy;
		if (s->cy > screen_size_y(s) - 1)
			s->cy = screen_size_y(s) - 1;
		memcpy(gc, &wp->saved_cell, sizeof *gc);
	}

	if (wp->saved_grid == NULL)
		return;
	sx = screen_size_x(s);
	sy = screen_size_y(s);

	/*
	 * If the current size is bigger, temporarily resize to the old size
	 * before copying back.
	 */
	if (sy > wp->saved_grid->sy)
		screen_resize(s, sx, wp->saved_grid->sy, 1);

	/* Restore the saved grid. */
	grid_duplicate_lines(s->grid, screen_hsize(s), wp->saved_grid, 0, sy);

	/*
	 * Turn history back on (so resize can use it) and then resize back to
	 * the current size.
	 */
	wp->base.grid->flags |= GRID_HISTORY;
	if (sy > wp->saved_grid->sy || sx != wp->saved_grid->sx)
		screen_resize(s, sx, sy, 1);

	grid_destroy(wp->saved_grid);
	wp->saved_grid = NULL;

	wp->flags |= PANE_REDRAW;
}