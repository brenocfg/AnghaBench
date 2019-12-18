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
struct TYPE_2__ {int /*<<< orphan*/  size; } ;
struct graph_v2 {TYPE_1__ next_row; TYPE_1__ row; TYPE_1__ prev_row; } ;

/* Variables and functions */
 int /*<<< orphan*/  graph_insert_column (struct graph_v2*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ graph_needs_expansion (struct graph_v2*) ; 

__attribute__((used)) static bool
graph_expand(struct graph_v2 *graph)
{
	while (graph_needs_expansion(graph)) {
		if (!graph_insert_column(graph, &graph->prev_row, graph->prev_row.size, NULL))
			return false;

		if (!graph_insert_column(graph, &graph->row, graph->row.size, NULL))
			return false;

		if (!graph_insert_column(graph, &graph->next_row, graph->next_row.size, NULL))
			return false;
	}

	return true;
}