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
struct sway_workspace {int dummy; } ;
struct sway_container {struct sway_workspace* workspace; scalar_t__ view; scalar_t__ height_fraction; scalar_t__ width_fraction; scalar_t__ height; scalar_t__ width; } ;

/* Variables and functions */
 int /*<<< orphan*/  container_add_child (struct sway_container*,struct sway_container*) ; 
 int /*<<< orphan*/  container_add_sibling (struct sway_container*,struct sway_container*,int) ; 
 int /*<<< orphan*/  container_detach (struct sway_container*) ; 
 scalar_t__ container_has_ancestor (struct sway_container*,struct sway_container*) ; 
 scalar_t__ container_is_floating (struct sway_container*) ; 
 int /*<<< orphan*/  container_move_to_workspace (struct sway_container*,struct sway_workspace*) ; 
 int /*<<< orphan*/  ipc_event_window (struct sway_container*,char*) ; 
 int /*<<< orphan*/  workspace_detect_urgent (struct sway_workspace*) ; 
 int /*<<< orphan*/  workspace_focus_fullscreen (struct sway_workspace*) ; 

__attribute__((used)) static void container_move_to_container(struct sway_container *container,
		struct sway_container *destination) {
	if (container == destination
			|| container_has_ancestor(container, destination)
			|| container_has_ancestor(destination, container)) {
		return;
	}
	if (container_is_floating(container)) {
		container_move_to_workspace(container, destination->workspace);
		return;
	}
	struct sway_workspace *old_workspace = container->workspace;

	container_detach(container);
	container->width = container->height = 0;
	container->width_fraction = container->height_fraction = 0;

	if (destination->view) {
		container_add_sibling(destination, container, 1);
	} else {
		container_add_child(destination, container);
	}

	if (container->view) {
		ipc_event_window(container, "move");
	}

	workspace_focus_fullscreen(destination->workspace);

	// Update workspace urgent state
	workspace_detect_urgent(destination->workspace);
	if (old_workspace && old_workspace != destination->workspace) {
		workspace_detect_urgent(old_workspace);
	}
}