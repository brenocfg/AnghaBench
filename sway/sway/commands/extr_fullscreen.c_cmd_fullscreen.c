#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sway_workspace {int /*<<< orphan*/  layout; TYPE_2__* tiling; } ;
struct sway_node {scalar_t__ type; } ;
struct sway_container {scalar_t__ fullscreen_mode; struct sway_container* parent; int /*<<< orphan*/  workspace; } ;
struct cmd_results {int dummy; } ;
typedef  enum sway_fullscreen_mode { ____Placeholder_sway_fullscreen_mode } sway_fullscreen_mode ;
struct TYPE_8__ {int /*<<< orphan*/  seat; struct sway_workspace* workspace; struct sway_container* container; struct sway_node* node; } ;
struct TYPE_10__ {TYPE_3__ handler_context; } ;
struct TYPE_9__ {TYPE_1__* outputs; } ;
struct TYPE_7__ {scalar_t__ length; } ;
struct TYPE_6__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_FAILURE ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_AT_MOST ; 
 int FULLSCREEN_GLOBAL ; 
 scalar_t__ FULLSCREEN_NONE ; 
 int FULLSCREEN_WORKSPACE ; 
 int /*<<< orphan*/  L_HORIZ ; 
 scalar_t__ N_WORKSPACE ; 
 int /*<<< orphan*/  arrange_root () ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*) ; 
 TYPE_5__* config ; 
 int /*<<< orphan*/  container_set_fullscreen (struct sway_container*,int) ; 
 int parse_boolean (char*,int) ; 
 TYPE_4__* root ; 
 int /*<<< orphan*/  seat_set_focus_container (int /*<<< orphan*/ ,struct sway_container*) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 struct sway_container* workspace_wrap_children (struct sway_workspace*) ; 

struct cmd_results *cmd_fullscreen(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "fullscreen", EXPECTED_AT_MOST, 2))) {
		return error;
	}
	if (!root->outputs->length) {
		return cmd_results_new(CMD_FAILURE,
				"Can't run this command while there's no outputs connected.");
	}
	struct sway_node *node = config->handler_context.node;
	struct sway_container *container = config->handler_context.container;
	struct sway_workspace *workspace = config->handler_context.workspace;
	if (node->type == N_WORKSPACE && workspace->tiling->length == 0) {
		return cmd_results_new(CMD_FAILURE,
				"Can't fullscreen an empty workspace");
	}

	// If in the scratchpad, operate on the highest container
	if (container && !container->workspace) {
		while (container->parent) {
			container = container->parent;
		}
	}

	bool is_fullscreen = false;
	for (struct sway_container *curr = container; curr; curr = curr->parent) {
		if (curr->fullscreen_mode != FULLSCREEN_NONE) {
			container = curr;
			is_fullscreen = true;
			break;
		}
	}

	bool global = false;
	bool enable = !is_fullscreen;

	if (argc >= 1) {
		if (strcasecmp(argv[0], "global") == 0) {
			global = true;
		} else {
			enable = parse_boolean(argv[0], is_fullscreen);
		}
	}

	if (argc >= 2) {
		global = strcasecmp(argv[1], "global") == 0;
	}

	if (enable && node->type == N_WORKSPACE) {
		// Wrap the workspace's children in a container so we can fullscreen it
		container = workspace_wrap_children(workspace);
		workspace->layout = L_HORIZ;
		seat_set_focus_container(config->handler_context.seat, container);
	}

	enum sway_fullscreen_mode mode = FULLSCREEN_NONE;
	if (enable) {
		mode = global ? FULLSCREEN_GLOBAL : FULLSCREEN_WORKSPACE;
	}

	container_set_fullscreen(container, mode);
	arrange_root();

	return cmd_results_new(CMD_SUCCESS, NULL);
}