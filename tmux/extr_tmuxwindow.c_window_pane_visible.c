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
struct TYPE_2__ {int flags; struct window_pane* active; } ;

/* Variables and functions */
 int WINDOW_ZOOMED ; 

int
window_pane_visible(struct window_pane *wp)
{
	if (~wp->window->flags & WINDOW_ZOOMED)
		return (1);
	return (wp == wp->window->active);
}