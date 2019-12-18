#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct screen {TYPE_1__* grid; int /*<<< orphan*/  cy; int /*<<< orphan*/  cx; } ;
struct window_pane {int /*<<< orphan*/  flags; struct screen base; int /*<<< orphan*/  saved_cell; int /*<<< orphan*/  saved_cy; int /*<<< orphan*/  saved_cx; int /*<<< orphan*/ * saved_grid; int /*<<< orphan*/  options; } ;
struct grid_cell {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRID_HISTORY ; 
 int /*<<< orphan*/  PANE_REDRAW ; 
 int /*<<< orphan*/ * grid_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grid_duplicate_lines (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grid_view_clear (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct grid_cell*,int) ; 
 int /*<<< orphan*/  options_get_number (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  screen_hsize (struct screen*) ; 
 int /*<<< orphan*/  screen_size_x (struct screen*) ; 
 int /*<<< orphan*/  screen_size_y (struct screen*) ; 

void
window_pane_alternate_on(struct window_pane *wp, struct grid_cell *gc,
    int cursor)
{
	struct screen	*s = &wp->base;
	u_int		 sx, sy;

	if (wp->saved_grid != NULL)
		return;
	if (!options_get_number(wp->options, "alternate-screen"))
		return;
	sx = screen_size_x(s);
	sy = screen_size_y(s);

	wp->saved_grid = grid_create(sx, sy, 0);
	grid_duplicate_lines(wp->saved_grid, 0, s->grid, screen_hsize(s), sy);
	if (cursor) {
		wp->saved_cx = s->cx;
		wp->saved_cy = s->cy;
	}
	memcpy(&wp->saved_cell, gc, sizeof wp->saved_cell);

	grid_view_clear(s->grid, 0, 0, sx, sy, 8);

	wp->base.grid->flags &= ~GRID_HISTORY;

	wp->flags |= PANE_REDRAW;
}