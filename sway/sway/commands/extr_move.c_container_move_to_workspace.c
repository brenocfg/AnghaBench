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
struct sway_workspace {struct sway_output* output; } ;
struct sway_output {int dummy; } ;
struct sway_container {scalar_t__ view; scalar_t__ height_fraction; scalar_t__ width_fraction; scalar_t__ height; scalar_t__ width; int /*<<< orphan*/  fullscreen_mode; struct sway_workspace* workspace; } ;

/* Variables and functions */
 int /*<<< orphan*/  container_detach (struct sway_container*) ; 
 int /*<<< orphan*/  container_floating_move_to_center (struct sway_container*) ; 
 int /*<<< orphan*/  container_handle_fullscreen_reparent (struct sway_container*) ; 
 scalar_t__ container_is_floating (struct sway_container*) ; 
 int /*<<< orphan*/  container_update_representation (struct sway_container*) ; 
 int /*<<< orphan*/  ipc_event_window (struct sway_container*,char*) ; 
 int /*<<< orphan*/  workspace_add_floating (struct sway_workspace*,struct sway_container*) ; 
 int /*<<< orphan*/  workspace_add_tiling (struct sway_workspace*,struct sway_container*) ; 
 int /*<<< orphan*/  workspace_detect_urgent (struct sway_workspace*) ; 
 int /*<<< orphan*/  workspace_focus_fullscreen (struct sway_workspace*) ; 

__attribute__((used)) static void container_move_to_workspace(struct sway_container *container,
		struct sway_workspace *workspace) {
	if (container->workspace == workspace) {
		return;
	}
	struct sway_workspace *old_workspace = container->workspace;
	if (container_is_floating(container)) {
		struct sway_output *old_output = container->workspace->output;
		container_detach(container);
		workspace_add_floating(workspace, container);
		container_handle_fullscreen_reparent(container);
		// If changing output, center it within the workspace
		if (old_output != workspace->output && !container->fullscreen_mode) {
			container_floating_move_to_center(container);
		}
	} else {
		container_detach(container);
		container->width = container->height = 0;
		container->width_fraction = container->height_fraction = 0;
		workspace_add_tiling(workspace, container);
		container_update_representation(container);
	}
	if (container->view) {
		ipc_event_window(container, "move");
	}
	workspace_detect_urgent(old_workspace);
	workspace_detect_urgent(workspace);
	workspace_focus_fullscreen(workspace);
}