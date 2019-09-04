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
struct window_pane {int /*<<< orphan*/  window; } ;
struct layout_cell {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  layout_fix_panes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layout_make_leaf (struct layout_cell*,struct window_pane*) ; 

void
layout_assign_pane(struct layout_cell *lc, struct window_pane *wp)
{
	layout_make_leaf(lc, wp);
	layout_fix_panes(wp->window);
}