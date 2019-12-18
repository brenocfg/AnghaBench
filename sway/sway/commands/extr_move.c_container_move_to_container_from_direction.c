#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sway_node {struct sway_container* sway_container; } ;
struct sway_container {scalar_t__ parent; scalar_t__ workspace; struct sway_node node; scalar_t__ height_fraction; scalar_t__ width_fraction; scalar_t__ height; scalar_t__ width; TYPE_1__* children; int /*<<< orphan*/  layout; scalar_t__ view; } ;
typedef  int /*<<< orphan*/  list_t ;
typedef  enum wlr_direction { ____Placeholder_wlr_direction } wlr_direction ;
struct TYPE_5__ {int /*<<< orphan*/  seat; } ;
struct TYPE_6__ {TYPE_2__ handler_context; } ;
struct TYPE_4__ {int length; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int WLR_DIRECTION_DOWN ; 
 int WLR_DIRECTION_LEFT ; 
 int WLR_DIRECTION_RIGHT ; 
 int WLR_DIRECTION_UP ; 
 TYPE_3__* config ; 
 int /*<<< orphan*/  container_add_child (struct sway_container*,struct sway_container*) ; 
 int /*<<< orphan*/ * container_get_siblings (struct sway_container*) ; 
 int /*<<< orphan*/  container_insert_child (struct sway_container*,struct sway_container*,int) ; 
 int container_sibling_index (struct sway_container*) ; 
 scalar_t__ is_parallel (int /*<<< orphan*/ ,int) ; 
 int list_find (int /*<<< orphan*/ *,struct sway_container*) ; 
 int /*<<< orphan*/  list_swap (int /*<<< orphan*/ *,int,int) ; 
 struct sway_node* seat_get_active_tiling_child (int /*<<< orphan*/ ,struct sway_node*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  workspace_insert_tiling (scalar_t__,struct sway_container*,int) ; 

__attribute__((used)) static void container_move_to_container_from_direction(
		struct sway_container *container, struct sway_container *destination,
		enum wlr_direction move_dir) {
	if (destination->view) {
		if (destination->parent == container->parent &&
				destination->workspace == container->workspace) {
			sway_log(SWAY_DEBUG, "Swapping siblings");
			list_t *siblings = container_get_siblings(container);
			int container_index = list_find(siblings, container);
			int destination_index = list_find(siblings, destination);
			list_swap(siblings, container_index, destination_index);
		} else {
			sway_log(SWAY_DEBUG, "Promoting to sibling of cousin");
			int offset =
				move_dir == WLR_DIRECTION_LEFT || move_dir == WLR_DIRECTION_UP;
			int index = container_sibling_index(destination) + offset;
			if (destination->parent) {
				container_insert_child(destination->parent, container, index);
			} else {
				workspace_insert_tiling(destination->workspace,
						container, index);
			}
			container->width = container->height = 0;
			container->width_fraction = container->height_fraction = 0;
		}
		return;
	}

	if (is_parallel(destination->layout, move_dir)) {
		sway_log(SWAY_DEBUG, "Reparenting container (parallel)");
		int index =
			move_dir == WLR_DIRECTION_RIGHT || move_dir == WLR_DIRECTION_DOWN ?
			0 : destination->children->length;
		container_insert_child(destination, container, index);
		container->width = container->height = 0;
		container->width_fraction = container->height_fraction = 0;
		return;
	}

	sway_log(SWAY_DEBUG, "Reparenting container (perpendicular)");
	struct sway_node *focus_inactive = seat_get_active_tiling_child(
			config->handler_context.seat, &destination->node);
	if (!focus_inactive || focus_inactive == &destination->node) {
		// The container has no children
		container_add_child(destination, container);
		return;
	}

	// Try again but with the child
	container_move_to_container_from_direction(container,
			focus_inactive->sway_container, move_dir);
}