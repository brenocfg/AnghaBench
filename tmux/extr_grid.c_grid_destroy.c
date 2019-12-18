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
struct grid {struct grid* linedata; scalar_t__ sy; scalar_t__ hsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct grid*) ; 
 int /*<<< orphan*/  grid_free_lines (struct grid*,int /*<<< orphan*/ ,scalar_t__) ; 

void
grid_destroy(struct grid *gd)
{
	grid_free_lines(gd, 0, gd->hsize + gd->sy);

	free(gd->linedata);

	free(gd);
}