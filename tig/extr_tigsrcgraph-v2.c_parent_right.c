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
struct TYPE_2__ {scalar_t__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  graph_column_has_commit (TYPE_1__*) ; 

__attribute__((used)) static bool
parent_right(struct graph_row *parents, struct graph_row *row, struct graph_row *next_row, int pos)
{
	int parent, i;

	for (parent = 0; parent < parents->size; parent++) {
		if (!graph_column_has_commit(&parents->columns[parent]))
			continue;

		for (i = pos + 1; i < next_row->size; i++) {
			if (parents->columns[parent].id != next_row->columns[i].id)
				continue;

			if (parents->columns[parent].id != row->columns[i].id)
				return true;
		}
	}

	return false;
}