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
struct grid {size_t hsize; int /*<<< orphan*/ * linedata; int /*<<< orphan*/  hscrolled; scalar_t__ sy; } ;

/* Variables and functions */
 int /*<<< orphan*/  grid_compact_line (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  grid_empty_line (struct grid*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * xreallocarray (int /*<<< orphan*/ *,scalar_t__,int) ; 

void
grid_scroll_history(struct grid *gd, u_int bg)
{
	u_int	yy;

	yy = gd->hsize + gd->sy;
	gd->linedata = xreallocarray(gd->linedata, yy + 1,
	    sizeof *gd->linedata);
	grid_empty_line(gd, yy, bg);

	gd->hscrolled++;
	grid_compact_line(&gd->linedata[gd->hsize]);
	gd->hsize++;
}