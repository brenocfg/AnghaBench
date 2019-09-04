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
struct sway_container {TYPE_1__* workspace; struct sway_container* parent; } ;
struct TYPE_2__ {int /*<<< orphan*/  node; int /*<<< orphan*/  floating; } ;

/* Variables and functions */
 scalar_t__ container_is_floating (struct sway_container*) ; 
 int /*<<< orphan*/  list_move_to_end (int /*<<< orphan*/ ,struct sway_container*) ; 
 int /*<<< orphan*/  node_set_dirty (int /*<<< orphan*/ *) ; 

void container_raise_floating(struct sway_container *con) {
	// Bring container to front by putting it at the end of the floating list.
	struct sway_container *floater = con;
	while (floater->parent) {
		floater = floater->parent;
	}
	if (container_is_floating(floater) && floater->workspace) {
		list_move_to_end(floater->workspace->floating, floater);
		node_set_dirty(&floater->workspace->node);
	}
}