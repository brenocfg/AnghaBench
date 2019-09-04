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
typedef  scalar_t__ u_int ;
struct grid_line {scalar_t__ cellused; } ;
struct grid {scalar_t__ sy; scalar_t__ hscrolled; int /*<<< orphan*/  sx; } ;

/* Variables and functions */
 int /*<<< orphan*/  grid_collect_history (struct grid*) ; 
 struct grid_line* grid_get_line (struct grid*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grid_scroll_history (struct grid*,scalar_t__) ; 
 int /*<<< orphan*/  grid_view_clear (struct grid*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  grid_view_y (struct grid*,scalar_t__) ; 

void
grid_view_clear_history(struct grid *gd, u_int bg)
{
	struct grid_line	*gl;
	u_int			 yy, last;

	/* Find the last used line. */
	last = 0;
	for (yy = 0; yy < gd->sy; yy++) {
		gl = grid_get_line(gd, grid_view_y(gd, yy));
		if (gl->cellused != 0)
			last = yy + 1;
	}
	if (last == 0) {
		grid_view_clear(gd, 0, 0, gd->sx, gd->sy, bg);
		return;
	}

	/* Scroll the lines into the history. */
	for (yy = 0; yy < last; yy++) {
		grid_collect_history(gd);
		grid_scroll_history(gd, bg);
	}
	if (last < gd->sy)
		grid_view_clear(gd, 0, 0, gd->sx, gd->sy - last, bg);
	gd->hscrolled = 0;
}