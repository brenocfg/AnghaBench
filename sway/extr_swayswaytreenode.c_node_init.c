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
struct TYPE_2__ {int /*<<< orphan*/  destroy; } ;
struct sway_node {int type; TYPE_1__ events; void* sway_root; int /*<<< orphan*/  id; } ;
typedef  enum sway_node_type { ____Placeholder_sway_node_type } sway_node_type ;

/* Variables and functions */
 int /*<<< orphan*/  wl_signal_init (int /*<<< orphan*/ *) ; 

void node_init(struct sway_node *node, enum sway_node_type type, void *thing) {
	static size_t next_id = 1;
	node->id = next_id++;
	node->type = type;
	node->sway_root = thing;
	wl_signal_init(&node->events.destroy);
}