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
typedef  void* u_int ;
struct grid {scalar_t__ sy; int /*<<< orphan*/ * linedata; void* hlimit; scalar_t__ hsize; scalar_t__ hscrolled; int /*<<< orphan*/  flags; void* sx; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRID_HISTORY ; 
 int /*<<< orphan*/ * xcalloc (scalar_t__,int) ; 
 struct grid* xmalloc (int) ; 

struct grid *
grid_create(u_int sx, u_int sy, u_int hlimit)
{
	struct grid	*gd;

	gd = xmalloc(sizeof *gd);
	gd->sx = sx;
	gd->sy = sy;

	gd->flags = GRID_HISTORY;

	gd->hscrolled = 0;
	gd->hsize = 0;
	gd->hlimit = hlimit;

	if (gd->sy != 0)
		gd->linedata = xcalloc(gd->sy, sizeof *gd->linedata);
	else
		gd->linedata = NULL;

	return (gd);
}