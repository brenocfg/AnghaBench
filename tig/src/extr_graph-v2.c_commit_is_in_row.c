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
struct graph_row {int size; TYPE_1__* columns; } ;
struct TYPE_2__ {char const* id; } ;

/* Variables and functions */
 int /*<<< orphan*/  graph_column_has_commit (TYPE_1__*) ; 

__attribute__((used)) static bool
commit_is_in_row(const char *id, struct graph_row *row)
{
	int i;

	for (i = 0; i < row->size; i++) {
		if (!graph_column_has_commit(&row->columns[i]))
			continue;

		if (id == row->columns[i].id)
			return true;
	}
	return false;
}