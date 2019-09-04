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
struct graph_v2 {int /*<<< orphan*/  id; int /*<<< orphan*/  next_row; } ;

/* Variables and functions */
 int /*<<< orphan*/  graph_fill_empty_columns (struct graph_v2*) ; 
 int /*<<< orphan*/  graph_insert_parents (struct graph_v2*) ; 
 int /*<<< orphan*/  graph_remove_collapsed_columns (struct graph_v2*) ; 
 int /*<<< orphan*/  graph_row_clear_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
graph_generate_next_row(struct graph_v2 *graph)
{
	graph_row_clear_commit(&graph->next_row, graph->id);
	graph_insert_parents(graph);
	graph_remove_collapsed_columns(graph);
	graph_fill_empty_columns(graph);
}