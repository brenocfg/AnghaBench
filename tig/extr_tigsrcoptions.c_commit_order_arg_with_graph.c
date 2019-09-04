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
typedef  enum graph_display { ____Placeholder_graph_display } graph_display ;
typedef  enum commit_order { ____Placeholder_commit_order } commit_order ;
struct TYPE_2__ {char const* name; } ;

/* Variables and functions */
 int COMMIT_ORDER_AUTO ; 
 int COMMIT_ORDER_TOPO ; 
 int GRAPH_DISPLAY_NO ; 
 TYPE_1__* commit_order_arg_map ; 
 int opt_commit_order ; 

const char *
commit_order_arg_with_graph(enum graph_display graph_display)
{
	enum commit_order commit_order = opt_commit_order;

	if (commit_order == COMMIT_ORDER_AUTO &&
	    graph_display != GRAPH_DISPLAY_NO)
		commit_order = COMMIT_ORDER_TOPO;

	return commit_order_arg_map[commit_order].name;
}