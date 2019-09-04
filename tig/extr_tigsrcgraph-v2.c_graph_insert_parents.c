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
struct graph_row {int size; struct graph_column* columns; } ;
struct graph_v2 {struct graph_row parents; struct graph_row next_row; struct graph_row row; struct graph_row prev_row; } ;
struct graph_column {int /*<<< orphan*/ * id; } ;

/* Variables and functions */
 scalar_t__ graph_column_has_commit (struct graph_column*) ; 
 size_t graph_find_free_column (struct graph_row*) ; 
 int /*<<< orphan*/  graph_insert_column (struct graph_v2*,struct graph_row*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
graph_insert_parents(struct graph_v2 *graph)
{
	struct graph_row *prev_row = &graph->prev_row;
	struct graph_row *row = &graph->row;
	struct graph_row *next_row = &graph->next_row;
	struct graph_row *parents = &graph->parents;
	int i;

	for (i = 0; i < parents->size; i++) {
		struct graph_column *new = &parents->columns[i];

		if (graph_column_has_commit(new)) {
			size_t match = graph_find_free_column(next_row);

			if (match == next_row->size && graph_column_has_commit(&next_row->columns[next_row->size - 1])) {
				graph_insert_column(graph, next_row, next_row->size, new->id);
				graph_insert_column(graph, row, row->size, NULL);
				graph_insert_column(graph, prev_row, prev_row->size, NULL);
			} else {
				next_row->columns[match] = *new;
			}
		}
	}
}