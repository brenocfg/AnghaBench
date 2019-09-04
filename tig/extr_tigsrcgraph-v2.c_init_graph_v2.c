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
struct graph {int /*<<< orphan*/  symbol_to_chtype; int /*<<< orphan*/  symbol_to_utf8; int /*<<< orphan*/  symbol_to_ascii; int /*<<< orphan*/  foreach_symbol; int /*<<< orphan*/  render_parents; int /*<<< orphan*/  is_merge; int /*<<< orphan*/  add_parent; int /*<<< orphan*/  add_commit; int /*<<< orphan*/  done_rendering; int /*<<< orphan*/  done; struct graph_v2* private; } ;
struct graph_v2 {struct graph api; } ;

/* Variables and functions */
 struct graph_v2* calloc (int,int) ; 
 int /*<<< orphan*/  done_graph ; 
 int /*<<< orphan*/  done_graph_rendering ; 
 int /*<<< orphan*/  graph_add_commit ; 
 int /*<<< orphan*/  graph_add_parent ; 
 int /*<<< orphan*/  graph_foreach_symbol ; 
 int /*<<< orphan*/  graph_is_merge ; 
 int /*<<< orphan*/  graph_render_parents ; 
 int /*<<< orphan*/  graph_symbol_to_ascii ; 
 int /*<<< orphan*/  graph_symbol_to_chtype ; 
 int /*<<< orphan*/  graph_symbol_to_utf8 ; 

struct graph *
init_graph_v2(void)
{
	struct graph_v2 *graph = calloc(1, sizeof(*graph));
	struct graph *api;

	if (!graph)
		return NULL;

	api = &graph->api;
	api->private = graph;
	api->done = done_graph;
	api->done_rendering = done_graph_rendering;
	api->add_commit = graph_add_commit;
	api->add_parent = graph_add_parent;
	api->is_merge = graph_is_merge;
	api->render_parents = graph_render_parents;
	api->foreach_symbol = graph_foreach_symbol;
	api->symbol_to_ascii = graph_symbol_to_ascii;
	api->symbol_to_utf8 = graph_symbol_to_utf8;
	api->symbol_to_chtype = graph_symbol_to_chtype;

	return api;
}