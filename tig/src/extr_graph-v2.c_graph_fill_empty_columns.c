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
struct graph_row {int size; int /*<<< orphan*/ * columns; } ;
struct graph_v2 {struct graph_row next_row; } ;

/* Variables and functions */
 int /*<<< orphan*/  graph_column_has_commit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
graph_fill_empty_columns(struct graph_v2 *graph)
{
	struct graph_row *row = &graph->next_row;
	int i;

	for (i = row->size - 2; i >= 0; i--) {
		if (!graph_column_has_commit(&row->columns[i])) {
			row->columns[i] = row->columns[i + 1];
		}
	}
}