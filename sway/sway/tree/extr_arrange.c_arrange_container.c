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
struct wlr_box {int dummy; } ;
struct sway_container {int /*<<< orphan*/  node; int /*<<< orphan*/  layout; int /*<<< orphan*/  children; scalar_t__ view; } ;
struct TYPE_2__ {scalar_t__ reloading; } ;

/* Variables and functions */
 int /*<<< orphan*/  arrange_children (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wlr_box*) ; 
 TYPE_1__* config ; 
 int /*<<< orphan*/  container_get_box (struct sway_container*,struct wlr_box*) ; 
 int /*<<< orphan*/  node_set_dirty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  view_autoconfigure (scalar_t__) ; 

void arrange_container(struct sway_container *container) {
	if (config->reloading) {
		return;
	}
	if (container->view) {
		view_autoconfigure(container->view);
		node_set_dirty(&container->node);
		return;
	}
	struct wlr_box box;
	container_get_box(container, &box);
	arrange_children(container->children, container->layout, &box);
	node_set_dirty(&container->node);
}