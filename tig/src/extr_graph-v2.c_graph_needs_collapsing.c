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
struct TYPE_2__ {int size; int /*<<< orphan*/ * columns; } ;
struct graph_v2 {TYPE_1__ row; } ;

/* Variables and functions */
 int /*<<< orphan*/  graph_column_has_commit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
graph_needs_collapsing(struct graph_v2 *graph)
{
	return graph->row.size > 1
	    && !graph_column_has_commit(&graph->row.columns[graph->row.size - 1]);
}