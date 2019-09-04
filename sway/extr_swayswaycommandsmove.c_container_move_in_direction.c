#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sway_workspace {int layout; int /*<<< orphan*/  output; } ;
struct sway_output {int dummy; } ;
struct sway_container {scalar_t__ fullscreen_mode; struct sway_workspace* workspace; struct sway_container* parent; } ;
struct TYPE_4__ {int length; int /*<<< orphan*/ * items; } ;
typedef  TYPE_1__ list_t ;
typedef  enum wlr_direction { ____Placeholder_wlr_direction } wlr_direction ;
typedef  enum sway_container_layout { ____Placeholder_sway_container_layout } sway_container_layout ;

/* Variables and functions */
 scalar_t__ FULLSCREEN_GLOBAL ; 
 scalar_t__ FULLSCREEN_WORKSPACE ; 
 scalar_t__ L_STACKED ; 
 scalar_t__ L_TABBED ; 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int WLR_DIRECTION_LEFT ; 
 int WLR_DIRECTION_UP ; 
 struct sway_container* container_flatten (struct sway_container*) ; 
 TYPE_1__* container_get_siblings (struct sway_container*) ; 
 int /*<<< orphan*/  container_insert_child (struct sway_container*,struct sway_container*,int) ; 
 scalar_t__ container_is_floating (struct sway_container*) ; 
 int /*<<< orphan*/  container_move_to_container_from_direction (struct sway_container*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  container_move_to_workspace (struct sway_container*,struct sway_workspace*) ; 
 int /*<<< orphan*/  container_move_to_workspace_from_direction (struct sway_container*,struct sway_workspace*,int) ; 
 int container_parent_layout (struct sway_container*) ; 
 scalar_t__ is_parallel (int,int) ; 
 int list_find (TYPE_1__*,struct sway_container*) ; 
 struct sway_workspace* output_get_active_workspace (struct sway_output*) ; 
 struct sway_output* output_get_in_direction (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sway_assert (struct sway_workspace*,char*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  workspace_insert_tiling (struct sway_workspace*,struct sway_container*,int) ; 
 int /*<<< orphan*/  workspace_rejigger (struct sway_workspace*,struct sway_container*,int) ; 

__attribute__((used)) static bool container_move_in_direction(struct sway_container *container,
		enum wlr_direction move_dir) {
	// If moving a fullscreen view, only consider outputs
	if (container->fullscreen_mode == FULLSCREEN_WORKSPACE) {
		struct sway_output *new_output =
			output_get_in_direction(container->workspace->output, move_dir);
		if (!new_output) {
			return false;
		}
		struct sway_workspace *ws = output_get_active_workspace(new_output);
		if (!sway_assert(ws, "Expected output to have a workspace")) {
			return false;
		}
		container_move_to_workspace(container, ws);
		return true;
	}
	if (container->fullscreen_mode == FULLSCREEN_GLOBAL) {
		return false;
	}

	// If container is in a split container by itself, move out of the split
	if (container->parent) {
		struct sway_container *new_parent =
			container_flatten(container->parent);
		if (new_parent != container->parent) {
			return true;
		}
	}

	// Look for a suitable *container* sibling or parent.
	// The below loop stops once we hit the workspace because current->parent
	// is NULL for the topmost containers in a workspace.
	struct sway_container *current = container;
	int offs =
		move_dir == WLR_DIRECTION_LEFT || move_dir == WLR_DIRECTION_UP ? -1 : 1;

	while (current) {
		list_t *siblings = container_get_siblings(current);
		if (siblings) {
			enum sway_container_layout layout = container_parent_layout(current);
			int index = list_find(siblings, current);
			int desired = index + offs;

			// Don't allow containers to move out of their
			// fullscreen or floating parent
			if (current->fullscreen_mode || container_is_floating(current)) {
				return false;
			}

			if (is_parallel(layout, move_dir)) {
				if (desired == -1 || desired == siblings->length) {
					if (current->parent == container->parent) {
						current = current->parent;
						continue;
					} else {
						// Reparenting
						if (current->parent) {
							container_insert_child(current->parent, container,
									index + (offs < 0 ? 0 : 1));
						} else {
							workspace_insert_tiling(current->workspace, container,
									index + (offs < 0 ? 0 : 1));
						}
						return true;
					}
				} else {
					// Container can move within its siblings
					container_move_to_container_from_direction(container,
							siblings->items[desired], move_dir);
					return true;
				}
			}
		}

		current = current->parent;
	}

	// Maybe rejigger the workspace
	struct sway_workspace *ws = container->workspace;
	if (ws) {
		if (!is_parallel(ws->layout, move_dir)) {
			workspace_rejigger(ws, container, move_dir);
			return true;
		} else if (ws->layout == L_TABBED || ws->layout == L_STACKED) {
			workspace_rejigger(ws, container, move_dir);
			return true;
		}

		// Try adjacent output
		struct sway_output *output =
			output_get_in_direction(container->workspace->output, move_dir);
		if (output) {
			struct sway_workspace *ws = output_get_active_workspace(output);
			if (!sway_assert(ws, "Expected output to have a workspace")) {
				return false;
			}
			container_move_to_workspace_from_direction(container, ws, move_dir);
			return true;
		}
		sway_log(SWAY_DEBUG, "Hit edge of output, nowhere else to go");
	}
	return false;
}