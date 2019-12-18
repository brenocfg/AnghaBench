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
struct grid {size_t hsize; size_t sy; int /*<<< orphan*/ * linedata; } ;

/* Variables and functions */
 int /*<<< orphan*/  grid_free_lines (struct grid*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void
grid_trim_history(struct grid *gd, u_int ny)
{
	grid_free_lines(gd, 0, ny);
	memmove(&gd->linedata[0], &gd->linedata[ny],
	    (gd->hsize + gd->sy - ny) * (sizeof *gd->linedata));
}