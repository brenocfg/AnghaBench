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
struct sway_node {int dirty; } ;
struct TYPE_2__ {int /*<<< orphan*/  dirty_nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ ,struct sway_node*) ; 
 TYPE_1__ server ; 

void node_set_dirty(struct sway_node *node) {
	if (node->dirty) {
		return;
	}
	node->dirty = true;
	list_add(server.dirty_nodes, node);
}