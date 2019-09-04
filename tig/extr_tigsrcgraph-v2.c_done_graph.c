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
struct graph_v2 {int dummy; } ;
struct graph {struct graph_v2* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct graph_v2*) ; 
 int /*<<< orphan*/  htab_empty (scalar_t__) ; 
 scalar_t__ intern_string_htab ; 

__attribute__((used)) static void
done_graph(struct graph *graph_ref)
{
	struct graph_v2 *graph = graph_ref->private;

	free(graph);

	if (intern_string_htab)
		htab_empty(intern_string_htab);
}