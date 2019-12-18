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
struct graph_v2 {TYPE_1__ parents; scalar_t__ has_parents; } ;
struct graph {struct graph_v2* private; } ;

/* Variables and functions */
 int /*<<< orphan*/ * graph_insert_column (struct graph_v2*,TYPE_1__*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static bool
graph_add_parent(struct graph *graph_ref, const char *parent)
{
	struct graph_v2 *graph = graph_ref->private;

	if (graph->has_parents)
		return true;
	return graph_insert_column(graph, &graph->parents, graph->parents.size, parent) != NULL;
}