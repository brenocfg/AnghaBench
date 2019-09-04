#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct screen {int cx; int cy; TYPE_2__* grid; } ;
struct window_pane {int saved_cx; int saved_cy; int /*<<< orphan*/  flags; TYPE_3__* saved_grid; struct screen base; int /*<<< orphan*/  saved_cell; TYPE_1__* window; } ;
struct grid_cell {int dummy; } ;
struct TYPE_7__ {scalar_t__ sy; scalar_t__ sx; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  options; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRID_HISTORY ; 
 int /*<<< orphan*/  PANE_REDRAW ; 
 int /*<<< orphan*/  grid_destroy (TYPE_3__*) ; 
 int /*<<< orphan*/  grid_duplicate_lines (TYPE_2__*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (struct grid_cell*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  options_get_number (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  screen_hsize (struct screen*) ; 
 int /*<<< orphan*/  screen_resize (struct screen*,scalar_t__,scalar_t__,int) ; 
 int screen_size_x (struct screen*) ; 
 int screen_size_y (struct screen*) ; 

void
window_pane_alternate_off(struct window_pane *wp, struct grid_cell *gc,
    int cursor)
{
	struct screen	*s = &wp->base;
	u_int		 sx, sy;

	if (wp->saved_grid == NULL)
		return;
	if (!options_get_number(wp->window->options, "alternate-screen"))
		return;
	sx = screen_size_x(s);
	sy = screen_size_y(s);

	/*
	 * If the current size is bigger, temporarily resize to the old size
	 * before copying back.
	 */
	if (sy > wp->saved_grid->sy)
		screen_resize(s, sx, wp->saved_grid->sy, 1);

	/* Restore the grid, cursor position and cell. */
	grid_duplicate_lines(s->grid, screen_hsize(s), wp->saved_grid, 0, sy);
	if (cursor)
		s->cx = wp->saved_cx;
	if (s->cx > screen_size_x(s) - 1)
		s->cx = screen_size_x(s) - 1;
	if (cursor)
		s->cy = wp->saved_cy;
	if (s->cy > screen_size_y(s) - 1)
		s->cy = screen_size_y(s) - 1;
	memcpy(gc, &wp->saved_cell, sizeof *gc);

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