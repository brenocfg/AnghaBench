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
struct grid {int sx; } ;

/* Variables and functions */
 int /*<<< orphan*/  grid_clear (struct grid*,int,int,int,int,int) ; 
 int /*<<< orphan*/  grid_move_cells (struct grid*,int,int,int,int,int) ; 
 int grid_view_x (struct grid*,int) ; 
 int grid_view_y (struct grid*,int) ; 

void
grid_view_insert_cells(struct grid *gd, u_int px, u_int py, u_int nx, u_int bg)
{
	u_int	sx;

	px = grid_view_x(gd, px);
	py = grid_view_y(gd, py);

	sx = grid_view_x(gd, gd->sx);

	if (px >= sx - 1)
		grid_clear(gd, px, py, 1, 1, bg);
	else
		grid_move_cells(gd, px + nx, px, py, sx - px - nx, bg);
}