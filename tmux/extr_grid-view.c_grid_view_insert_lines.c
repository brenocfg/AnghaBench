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
struct grid {scalar_t__ sy; } ;

/* Variables and functions */
 int /*<<< orphan*/  grid_move_lines (struct grid*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ grid_view_y (struct grid*,scalar_t__) ; 

void
grid_view_insert_lines(struct grid *gd, u_int py, u_int ny, u_int bg)
{
	u_int	sy;

	py = grid_view_y(gd, py);

	sy = grid_view_y(gd, gd->sy);

	grid_move_lines(gd, py + ny, py, sy - py - ny, bg);
}