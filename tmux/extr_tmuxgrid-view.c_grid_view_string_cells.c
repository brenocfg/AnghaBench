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
typedef  int /*<<< orphan*/  u_int ;
struct grid {int dummy; } ;

/* Variables and functions */
 char* grid_string_cells (struct grid*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grid_view_x (struct grid*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grid_view_y (struct grid*,int /*<<< orphan*/ ) ; 

char *
grid_view_string_cells(struct grid *gd, u_int px, u_int py, u_int nx)
{
	px = grid_view_x(gd, px);
	py = grid_view_y(gd, py);

	return (grid_string_cells(gd, px, py, nx, NULL, 0, 0, 0));
}