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
struct view_column {int type; struct view_column* next; } ;
struct view {struct view_column* columns; } ;
typedef  enum view_column_type { ____Placeholder_view_column_type } view_column_type ;

/* Variables and functions */

struct view_column *
get_view_column(struct view *view, enum view_column_type type)
{
	struct view_column *column;

	for (column = view->columns; column; column = column->next)
		if (column->type == type)
			return column;
	return NULL;
}