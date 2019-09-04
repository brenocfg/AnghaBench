#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct grid {TYPE_1__* linedata; } ;
struct TYPE_2__ {int /*<<< orphan*/ * extddata; int /*<<< orphan*/ * celldata; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
grid_free_line(struct grid *gd, u_int py)
{
	free(gd->linedata[py].celldata);
	gd->linedata[py].celldata = NULL;
	free(gd->linedata[py].extddata);
	gd->linedata[py].extddata = NULL;
}