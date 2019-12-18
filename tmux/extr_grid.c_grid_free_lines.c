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
struct grid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  grid_free_line (struct grid*,scalar_t__) ; 

__attribute__((used)) static void
grid_free_lines(struct grid *gd, u_int py, u_int ny)
{
	u_int	yy;

	for (yy = py; yy < py + ny; yy++)
		grid_free_line(gd, yy);
}