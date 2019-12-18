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
struct sway_workspace {int /*<<< orphan*/  node; } ;
struct sway_container {double x; double y; scalar_t__ view; struct sway_workspace* workspace; scalar_t__ fullscreen_mode; } ;
struct cmd_results {int dummy; } ;
typedef  enum wlr_direction { ____Placeholder_wlr_direction } wlr_direction ;
struct TYPE_4__ {int /*<<< orphan*/  seat; struct sway_container* container; } ;
struct TYPE_6__ {TYPE_1__ handler_context; } ;
struct TYPE_5__ {scalar_t__ fullscreen_global; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_FAILURE ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
#define  WLR_DIRECTION_DOWN 131 
#define  WLR_DIRECTION_LEFT 130 
#define  WLR_DIRECTION_RIGHT 129 
#define  WLR_DIRECTION_UP 128 
 int /*<<< orphan*/  arrange_root () ; 
 int /*<<< orphan*/  arrange_workspace (struct sway_workspace*) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* config ; 
 int /*<<< orphan*/  container_end_mouse_operation (struct sway_container*) ; 
 int /*<<< orphan*/  container_floating_move_to (struct sway_container*,double,double) ; 
 scalar_t__ container_is_floating (struct sway_container*) ; 
 int /*<<< orphan*/  container_move_in_direction (struct sway_container*,int) ; 
 int /*<<< orphan*/  ipc_event_window (struct sway_container*,char*) ; 
 int /*<<< orphan*/  ipc_event_workspace (struct sway_workspace*,struct sway_workspace*,char*) ; 
 TYPE_2__* root ; 
 int /*<<< orphan*/  seat_set_focus_container (int /*<<< orphan*/ ,struct sway_container*) ; 
 int /*<<< orphan*/  seat_set_raw_focus (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 scalar_t__ strtol (char*,char**,int) ; 
 int /*<<< orphan*/  workspace_detect_urgent (struct sway_workspace*) ; 

__attribute__((used)) static struct cmd_results *cmd_move_in_direction(
		enum wlr_direction direction, int argc, char **argv) {
	int move_amt = 10;
	if (argc) {
		char *inv;
		move_amt = (int)strtol(argv[0], &inv, 10);
		if (*inv != '\0' && strcasecmp(inv, "px") != 0) {
			return cmd_results_new(CMD_FAILURE, "Invalid distance specified");
		}
	}

	struct sway_container *container = config->handler_context.container;
	if (!container) {
		return cmd_results_new(CMD_FAILURE,
				"Cannot move workspaces in a direction");
	}
	if (container_is_floating(container)) {
		if (container->fullscreen_mode) {
			return cmd_results_new(CMD_FAILURE,
					"Cannot move fullscreen floating container");
		}
		double lx = container->x;
		double ly = container->y;
		switch (direction) {
		case WLR_DIRECTION_LEFT:
			lx -= move_amt;
			break;
		case WLR_DIRECTION_RIGHT:
			lx += move_amt;
			break;
		case WLR_DIRECTION_UP:
			ly -= move_amt;
			break;
		case WLR_DIRECTION_DOWN:
			ly += move_amt;
			break;
		}
		container_floating_move_to(container, lx, ly);
		return cmd_results_new(CMD_SUCCESS, NULL);
	}
	struct sway_workspace *old_ws = container->workspace;

	if (!container_move_in_direction(container, direction)) {
		// Container didn't move
		return cmd_results_new(CMD_SUCCESS, NULL);
	}

	struct sway_workspace *new_ws = container->workspace;

	if (root->fullscreen_global) {
		arrange_root();
	} else {
		arrange_workspace(old_ws);
		if (new_ws != old_ws) {
			arrange_workspace(new_ws);
		}
	}

	if (container->view) {
		ipc_event_window(container, "move");
	}

	// Hack to re-focus container
	seat_set_raw_focus(config->handler_context.seat, &new_ws->node);
	seat_set_focus_container(config->handler_context.seat, container);

	if (old_ws != new_ws) {
		ipc_event_workspace(old_ws, new_ws, "focus");
		workspace_detect_urgent(old_ws);
		workspace_detect_urgent(new_ws);
	}
	container_end_mouse_operation(container);

	return cmd_results_new(CMD_SUCCESS, NULL);
}