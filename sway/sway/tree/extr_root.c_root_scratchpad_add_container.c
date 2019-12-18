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
struct sway_workspace {int /*<<< orphan*/  node; } ;
struct sway_seat {int dummy; } ;
struct sway_node {int dummy; } ;
struct sway_container {int scratchpad; scalar_t__ fullscreen_mode; int /*<<< orphan*/  node; struct sway_workspace* workspace; struct sway_container* parent; } ;
struct TYPE_2__ {int /*<<< orphan*/  scratchpad; } ;

/* Variables and functions */
 scalar_t__ FULLSCREEN_NONE ; 
 int /*<<< orphan*/  arrange_container (struct sway_container*) ; 
 int /*<<< orphan*/  arrange_workspace (struct sway_workspace*) ; 
 int /*<<< orphan*/  container_detach (struct sway_container*) ; 
 int /*<<< orphan*/  container_floating_move_to_center (struct sway_container*) ; 
 int /*<<< orphan*/  container_floating_set_default_size (struct sway_container*) ; 
 int /*<<< orphan*/  container_fullscreen_disable (struct sway_container*) ; 
 int /*<<< orphan*/  container_is_floating (struct sway_container*) ; 
 int /*<<< orphan*/  container_set_floating (struct sway_container*,int) ; 
 struct sway_seat* input_manager_current_seat () ; 
 int /*<<< orphan*/  ipc_event_window (struct sway_container*,char*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ ,struct sway_container*) ; 
 TYPE_1__* root ; 
 struct sway_node* seat_get_focus_inactive (struct sway_seat*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seat_set_focus (struct sway_seat*,struct sway_node*) ; 
 int /*<<< orphan*/  sway_assert (int,char*) ; 
 int /*<<< orphan*/  workspace_add_floating (struct sway_workspace*,struct sway_container*) ; 

void root_scratchpad_add_container(struct sway_container *con, struct sway_workspace *ws) {
	if (!sway_assert(!con->scratchpad, "Container is already in scratchpad")) {
		return;
	}

	struct sway_container *parent = con->parent;
	struct sway_workspace *workspace = con->workspace;

	// Clear the fullscreen mode when sending to the scratchpad
	if (con->fullscreen_mode != FULLSCREEN_NONE) {
		container_fullscreen_disable(con);
	}

	// When a tiled window is sent to scratchpad, center and resize it.
	if (!container_is_floating(con)) {
		container_set_floating(con, true);
		container_floating_set_default_size(con);
		container_floating_move_to_center(con);
	}

	container_detach(con);
	con->scratchpad = true;
	list_add(root->scratchpad, con);
	if (ws) {
		workspace_add_floating(ws, con);
	}

	if (!ws) {
		struct sway_seat *seat = input_manager_current_seat();
		struct sway_node *new_focus = NULL;
		if (parent) {
			arrange_container(parent);
			new_focus = seat_get_focus_inactive(seat, &parent->node);
		}
		if (!new_focus) {
			arrange_workspace(workspace);
			new_focus = seat_get_focus_inactive(seat, &workspace->node);
		}
		seat_set_focus(seat, new_focus);
	}

	ipc_event_window(con, "move");
}