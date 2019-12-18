#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sway_node {scalar_t__ type; int /*<<< orphan*/  destroying; int /*<<< orphan*/  sway_container; struct sway_output* sway_output; struct sway_workspace* sway_workspace; } ;
struct sway_workspace {struct sway_node node; scalar_t__ name; struct sway_output* output; TYPE_1__* tiling; } ;
struct sway_seat {scalar_t__ prev_workspace_name; } ;
struct sway_output {struct sway_node node; } ;
struct sway_container {scalar_t__ fullscreen_mode; struct sway_node node; scalar_t__ scratchpad; scalar_t__ is_sticky; int /*<<< orphan*/  y; int /*<<< orphan*/  x; struct sway_workspace* workspace; struct sway_container* parent; } ;
struct cmd_results {int dummy; } ;
struct TYPE_6__ {struct sway_seat* seat; struct sway_container* container; struct sway_workspace* workspace; struct sway_node* node; } ;
struct TYPE_8__ {scalar_t__ auto_back_and_forth; TYPE_2__ handler_context; } ;
struct TYPE_7__ {scalar_t__ fullscreen_global; } ;
struct TYPE_5__ {scalar_t__ length; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_FAILURE ; 
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_AT_LEAST ; 
 scalar_t__ FULLSCREEN_GLOBAL ; 
#define  N_CONTAINER 131 
#define  N_OUTPUT 130 
#define  N_ROOT 129 
#define  N_WORKSPACE 128 
 int /*<<< orphan*/  arrange_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arrange_root () ; 
 int /*<<< orphan*/  arrange_workspace (struct sway_workspace*) ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_move_to_scratchpad () ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_4__* config ; 
 struct sway_container* container_find_mark (char*) ; 
 scalar_t__ container_is_floating_or_child (struct sway_container*) ; 
 scalar_t__ container_is_scratchpad_hidden (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  container_move_to_container (struct sway_container*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  container_move_to_workspace (struct sway_container*,struct sway_workspace*) ; 
 int /*<<< orphan*/  container_reap_empty (struct sway_container*) ; 
 char* expected_syntax ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  isdigit (char) ; 
 char* join_args (char**,int) ; 
 struct sway_output* node_get_output (struct sway_node*) ; 
 int /*<<< orphan*/  node_get_parent (struct sway_node*) ; 
 scalar_t__ node_has_ancestor (struct sway_node*,struct sway_node*) ; 
 struct sway_workspace* output_get_active_workspace (struct sway_output*) ; 
 struct sway_output* output_in_direction (char*,struct sway_output*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* root ; 
 int /*<<< orphan*/  root_scratchpad_show (struct sway_container*) ; 
 struct sway_node* seat_get_focus (struct sway_seat*) ; 
 struct sway_node* seat_get_focus_inactive (struct sway_seat*,struct sway_node*) ; 
 struct sway_container* seat_get_focus_inactive_tiling (struct sway_seat*,struct sway_workspace*) ; 
 int /*<<< orphan*/  seat_set_focus (struct sway_seat*,struct sway_node*) ; 
 int /*<<< orphan*/  seat_set_raw_focus (struct sway_seat*,struct sway_node*) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 
 char* strdup (scalar_t__) ; 
 int /*<<< orphan*/  sway_assert (struct sway_workspace*,char*) ; 
 struct sway_workspace* workspace_by_name (char*) ; 
 struct sway_workspace* workspace_by_number (char*) ; 
 int /*<<< orphan*/  workspace_consider_destroy (struct sway_workspace*) ; 
 struct sway_workspace* workspace_create (int /*<<< orphan*/ *,char*) ; 
 struct sway_output* workspace_get_initial_output (char*) ; 
 struct sway_container* workspace_wrap_children (struct sway_workspace*) ; 

__attribute__((used)) static struct cmd_results *cmd_move_container(bool no_auto_back_and_forth,
		int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "move container/window",
				EXPECTED_AT_LEAST, 2))) {
		return error;
	}

	struct sway_node *node = config->handler_context.node;
	struct sway_workspace *workspace = config->handler_context.workspace;
	struct sway_container *container = config->handler_context.container;
	if (node->type == N_WORKSPACE) {
		if (workspace->tiling->length == 0) {
			return cmd_results_new(CMD_FAILURE,
					"Can't move an empty workspace");
		}
		container = workspace_wrap_children(workspace);
	}

	if (container->fullscreen_mode == FULLSCREEN_GLOBAL) {
		return cmd_results_new(CMD_FAILURE,
				"Can't move fullscreen global container");
	}

	struct sway_seat *seat = config->handler_context.seat;
	struct sway_container *old_parent = container->parent;
	struct sway_workspace *old_ws = container->workspace;
	struct sway_output *old_output = old_ws ? old_ws->output : NULL;
	struct sway_node *destination = NULL;

	// determine destination
	if (strcasecmp(argv[0], "workspace") == 0) {
		// move container to workspace x
		struct sway_workspace *ws = NULL;
		char *ws_name = NULL;
		if (strcasecmp(argv[1], "next") == 0 ||
				strcasecmp(argv[1], "prev") == 0 ||
				strcasecmp(argv[1], "next_on_output") == 0 ||
				strcasecmp(argv[1], "prev_on_output") == 0 ||
				strcasecmp(argv[1], "current") == 0) {
			ws = workspace_by_name(argv[1]);
		} else if (strcasecmp(argv[1], "back_and_forth") == 0) {
			if (!(ws = workspace_by_name(argv[1]))) {
				if (seat->prev_workspace_name) {
					ws_name = strdup(seat->prev_workspace_name);
				} else {
					return cmd_results_new(CMD_FAILURE,
							"No workspace was previously active.");
				}
			}
		} else {
			if (strcasecmp(argv[1], "number") == 0) {
				// move [window|container] [to] "workspace number x"
				if (argc < 3) {
					return cmd_results_new(CMD_INVALID, expected_syntax);
				}
				if (!isdigit(argv[2][0])) {
					return cmd_results_new(CMD_INVALID,
							"Invalid workspace number '%s'", argv[2]);
				}
				ws_name = join_args(argv + 2, argc - 2);
				ws = workspace_by_number(ws_name);
			} else {
				ws_name = join_args(argv + 1, argc - 1);
				ws = workspace_by_name(ws_name);
			}

			if (!no_auto_back_and_forth && config->auto_back_and_forth &&
					seat->prev_workspace_name) {
				// auto back and forth move
				if (old_ws && old_ws->name &&
						strcmp(old_ws->name, ws_name) == 0) {
					// if target workspace is the current one
					free(ws_name);
					ws_name = strdup(seat->prev_workspace_name);
					ws = workspace_by_name(ws_name);
				}
			}
		}
		if (!ws) {
			// We have to create the workspace, but if the container is
			// sticky and the workspace is going to be created on the same
			// output, we'll bail out first.
			if (container->is_sticky && container_is_floating_or_child(container)) {
				struct sway_output *new_output =
					workspace_get_initial_output(ws_name);
				if (old_output == new_output) {
					free(ws_name);
					return cmd_results_new(CMD_FAILURE,
							"Can't move sticky container to another workspace "
							"on the same output");
				}
			}
			ws = workspace_create(NULL, ws_name);
		}
		free(ws_name);
		struct sway_container *dst = seat_get_focus_inactive_tiling(seat, ws);
		destination = dst ? &dst->node : &ws->node;
	} else if (strcasecmp(argv[0], "output") == 0) {
		struct sway_output *new_output = output_in_direction(argv[1],
				old_output, container->x, container->y);
		if (!new_output) {
			return cmd_results_new(CMD_FAILURE,
				"Can't find output with name/direction '%s'", argv[1]);
		}
		destination = seat_get_focus_inactive(seat, &new_output->node);
	} else if (strcasecmp(argv[0], "mark") == 0) {
		struct sway_container *dest_con = container_find_mark(argv[1]);
		if (dest_con == NULL) {
			return cmd_results_new(CMD_FAILURE,
					"Mark '%s' not found", argv[1]);
		}
		destination = &dest_con->node;
	} else {
		return cmd_results_new(CMD_INVALID, expected_syntax);
	}

	if (destination->type == N_CONTAINER &&
			container_is_scratchpad_hidden(destination->sway_container)) {
		return cmd_move_to_scratchpad();
	}

	if (container->is_sticky && container_is_floating_or_child(container) &&
			old_output && node_has_ancestor(destination, &old_output->node)) {
		return cmd_results_new(CMD_FAILURE, "Can't move sticky "
				"container to another workspace on the same output");
	}

	struct sway_output *new_output = node_get_output(destination);
	struct sway_workspace *new_output_last_ws = old_output == new_output ?
		NULL : output_get_active_workspace(new_output);

	// save focus, in case it needs to be restored
	struct sway_node *focus = seat_get_focus(seat);

	// move container
	if (container->scratchpad) {
		root_scratchpad_show(container);
	}
	switch (destination->type) {
	case N_WORKSPACE:
		container_move_to_workspace(container, destination->sway_workspace);
		break;
	case N_OUTPUT: {
			struct sway_output *output = destination->sway_output;
			struct sway_workspace *ws = output_get_active_workspace(output);
			if (!sway_assert(ws, "Expected output to have a workspace")) {
				return cmd_results_new(CMD_FAILURE,
						"Expected output to have a workspace");
			}
			container_move_to_workspace(container, ws);
		}
		break;
	case N_CONTAINER:
		container_move_to_container(container, destination->sway_container);
		break;
	case N_ROOT:
		break;
	}

	// restore focus on destination output back to its last active workspace
	struct sway_workspace *new_workspace =
		output_get_active_workspace(new_output);
	if (!sway_assert(new_workspace, "Expected output to have a workspace")) {
		return cmd_results_new(CMD_FAILURE,
				"Expected output to have a workspace");
	}
	if (new_output_last_ws && new_output_last_ws != new_workspace) {
		struct sway_node *new_output_last_focus =
			seat_get_focus_inactive(seat, &new_output_last_ws->node);
		seat_set_raw_focus(seat, new_output_last_focus);
	}

	// restore focus
	if (focus == &container->node) {
		focus = NULL;
		if (old_parent) {
			focus = seat_get_focus_inactive(seat, &old_parent->node);
		}
		if (!focus && old_ws) {
			focus = seat_get_focus_inactive(seat, &old_ws->node);
		}
	}
	seat_set_focus(seat, focus);

	// clean-up, destroying parents if the container was the last child
	if (old_parent) {
		container_reap_empty(old_parent);
	} else if (old_ws) {
		workspace_consider_destroy(old_ws);
	}

	// arrange windows
	if (root->fullscreen_global) {
		arrange_root();
	} else {
		if (old_ws && !old_ws->node.destroying) {
			arrange_workspace(old_ws);
		}
		arrange_node(node_get_parent(destination));
	}

	return cmd_results_new(CMD_SUCCESS, NULL);
}