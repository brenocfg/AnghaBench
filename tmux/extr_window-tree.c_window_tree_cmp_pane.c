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
struct window_pane {int active_point; int id; } ;
struct TYPE_2__ {scalar_t__ field; scalar_t__ reversed; } ;

/* Variables and functions */
 scalar_t__ WINDOW_TREE_BY_TIME ; 
 TYPE_1__* window_tree_sort ; 

__attribute__((used)) static int
window_tree_cmp_pane(const void *a0, const void *b0)
{
	const struct window_pane *const	*a = a0;
	const struct window_pane *const	*b = b0;
	int				 result;

	if (window_tree_sort->field == WINDOW_TREE_BY_TIME)
		result = (*a)->active_point - (*b)->active_point;
	else {
		/*
		 * Panes don't have names, so use number order for any other
		 * sort field.
		 */
		result = (*a)->id - (*b)->id;
	}
	if (window_tree_sort->reversed)
		result = -result;
	return (result);
}