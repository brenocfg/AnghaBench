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
struct window_pane {TYPE_1__* window; } ;
struct mode_tree_data {int zoomed; struct window_pane* wp; } ;
struct args {int dummy; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int WINDOW_ZOOMED ; 
 scalar_t__ args_has (struct args*,char) ; 
 int /*<<< orphan*/  server_redraw_window (TYPE_1__*) ; 
 scalar_t__ window_zoom (struct window_pane*) ; 

void
mode_tree_zoom(struct mode_tree_data *mtd, struct args *args)
{
	struct window_pane	*wp = mtd->wp;

	if (args_has(args, 'Z')) {
		mtd->zoomed = (wp->window->flags & WINDOW_ZOOMED);
		if (!mtd->zoomed && window_zoom(wp) == 0)
			server_redraw_window(wp->window);
	} else
		mtd->zoomed = -1;
}