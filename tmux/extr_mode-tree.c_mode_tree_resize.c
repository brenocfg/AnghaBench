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
typedef  int /*<<< orphan*/  u_int ;
struct screen {int dummy; } ;
struct mode_tree_data {TYPE_1__* wp; struct screen screen; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PANE_REDRAW ; 
 int /*<<< orphan*/  mode_tree_build (struct mode_tree_data*) ; 
 int /*<<< orphan*/  mode_tree_draw (struct mode_tree_data*) ; 
 int /*<<< orphan*/  screen_resize (struct screen*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
mode_tree_resize(struct mode_tree_data *mtd, u_int sx, u_int sy)
{
	struct screen	*s = &mtd->screen;

	screen_resize(s, sx, sy, 0);

	mode_tree_build(mtd);
	mode_tree_draw(mtd);

	mtd->wp->flags |= PANE_REDRAW;
}