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
struct view_column {int /*<<< orphan*/  opt; int /*<<< orphan*/  prev_opt; struct view_column* next; } ;
struct view {struct view_column* columns; } ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

bool
view_column_info_changed(struct view *view, bool update)
{
	struct view_column *column;
	bool changed = false;

	for (column = view->columns; column; column = column->next) {
		if (memcmp(&column->prev_opt, &column->opt, sizeof(column->opt))) {
			if (!update)
				return true;
			column->prev_opt = column->opt;
			changed = true;
		}
	}

	return changed;
}