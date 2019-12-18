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
struct grid {int hsize; int hlimit; int hscrolled; } ;

/* Variables and functions */
 int /*<<< orphan*/  grid_trim_history (struct grid*,int) ; 

void
grid_collect_history(struct grid *gd)
{
	u_int	ny;

	if (gd->hsize == 0 || gd->hsize < gd->hlimit)
		return;

	ny = gd->hlimit / 10;
	if (ny < 1)
		ny = 1;
	if (ny > gd->hsize)
		ny = gd->hsize;

	/*
	 * Free the lines from 0 to ny then move the remaining lines over
	 * them.
	 */
	grid_trim_history(gd, ny);

	gd->hsize -= ny;
	if (gd->hscrolled > gd->hsize)
		gd->hscrolled = gd->hsize;
}