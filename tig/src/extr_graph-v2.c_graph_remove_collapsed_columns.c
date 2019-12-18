#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_4__* columns; } ;
struct graph_row {int size; TYPE_3__* columns; } ;
struct graph_v2 {int position; scalar_t__ id; TYPE_2__ prev_row; int /*<<< orphan*/  parents; struct graph_row next_row; } ;
struct TYPE_5__ {scalar_t__ shift_left; } ;
struct TYPE_8__ {scalar_t__ id; TYPE_1__ symbol; } ;
struct TYPE_7__ {scalar_t__ id; } ;

/* Variables and functions */
 scalar_t__ commit_is_in_row (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  graph_column_has_commit (TYPE_4__*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
graph_remove_collapsed_columns(struct graph_v2 *graph)
{
	struct graph_row *row = &graph->next_row;
	int i;

	for (i = row->size - 1; i > 0; i--) {
		if (i == graph->position)
			continue;

		if (i == graph->position + 1)
			continue;

		if (row->columns[i].id == graph->id)
			continue;

		if (row->columns[i].id != row->columns[i - 1].id)
			continue;

		if (commit_is_in_row(row->columns[i].id, &graph->parents) && !graph_column_has_commit(&graph->prev_row.columns[i]))
			continue;

		if (row->columns[i - 1].id != graph->prev_row.columns[i - 1].id || graph->prev_row.columns[i - 1].symbol.shift_left) {
			if (i + 1 >= row->size)
				memset(&row->columns[i], 0, sizeof(row->columns[i]));
			else
				row->columns[i] = row->columns[i + 1];
		}
	}
}