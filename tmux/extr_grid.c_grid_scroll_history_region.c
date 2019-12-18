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
typedef  size_t u_int ;
struct grid_line {int dummy; } ;
struct grid {size_t hsize; size_t sy; int /*<<< orphan*/  hscrolled; struct grid_line* linedata; } ;

/* Variables and functions */
 int /*<<< orphan*/  grid_empty_line (struct grid*,size_t,size_t) ; 
 int /*<<< orphan*/  memcpy (struct grid_line*,struct grid_line*,int) ; 
 int /*<<< orphan*/  memmove (struct grid_line*,struct grid_line*,size_t) ; 
 struct grid_line* xreallocarray (struct grid_line*,size_t,int) ; 

void
grid_scroll_history_region(struct grid *gd, u_int upper, u_int lower, u_int bg)
{
	struct grid_line	*gl_history, *gl_upper;
	u_int			 yy;

	/* Create a space for a new line. */
	yy = gd->hsize + gd->sy;
	gd->linedata = xreallocarray(gd->linedata, yy + 1,
	    sizeof *gd->linedata);

	/* Move the entire screen down to free a space for this line. */
	gl_history = &gd->linedata[gd->hsize];
	memmove(gl_history + 1, gl_history, gd->sy * sizeof *gl_history);

	/* Adjust the region and find its start and end. */
	upper++;
	gl_upper = &gd->linedata[upper];
	lower++;

	/* Move the line into the history. */
	memcpy(gl_history, gl_upper, sizeof *gl_history);

	/* Then move the region up and clear the bottom line. */
	memmove(gl_upper, gl_upper + 1, (lower - upper) * sizeof *gl_upper);
	grid_empty_line(gd, lower, bg);

	/* Move the history offset down over the line. */
	gd->hscrolled++;
	gd->hsize++;
}