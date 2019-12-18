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
struct TYPE_2__ {scalar_t__ size; } ;
struct graph_v2 {scalar_t__ position; TYPE_1__ parents; } ;
struct graph_canvas {int dummy; } ;
struct graph {struct graph_v2* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  graph_add_parent (struct graph*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  graph_collapse (struct graph_v2*) ; 
 int /*<<< orphan*/  graph_commit_next_row (struct graph_v2*) ; 
 int /*<<< orphan*/  graph_expand (struct graph_v2*) ; 
 int /*<<< orphan*/  graph_generate_next_row (struct graph_v2*) ; 
 int /*<<< orphan*/  graph_generate_symbols (struct graph_v2*,struct graph_canvas*) ; 

__attribute__((used)) static bool
graph_render_parents(struct graph *graph_ref, struct graph_canvas *canvas)
{
	struct graph_v2 *graph = graph_ref->private;

	if (graph->parents.size == 0 &&
	    !graph_add_parent(graph_ref, NULL))
		return false;

	if (!graph_expand(graph))
		return false;

	graph_generate_next_row(graph);
	graph_generate_symbols(graph, canvas);
	graph_commit_next_row(graph);

	graph->parents.size = graph->position = 0;

	if (!graph_collapse(graph))
		return false;

	return true;
}