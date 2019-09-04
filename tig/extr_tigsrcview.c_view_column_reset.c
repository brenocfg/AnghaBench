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
struct view_column {scalar_t__ width; struct view_column* next; } ;
struct view {struct view_column* columns; } ;

/* Variables and functions */
 int /*<<< orphan*/  view_column_info_changed (struct view*,int) ; 

void
view_column_reset(struct view *view)
{
	struct view_column *column;

	view_column_info_changed(view, true);
	for (column = view->columns; column; column = column->next)
		column->width = 0;
}