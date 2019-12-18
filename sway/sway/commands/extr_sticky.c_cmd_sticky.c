#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sway_workspace {int /*<<< orphan*/  output; } ;
struct sway_container {struct sway_workspace* workspace; scalar_t__ is_sticky; } ;
struct cmd_results {int dummy; } ;
struct TYPE_3__ {struct sway_container* container; } ;
struct TYPE_4__ {TYPE_1__ handler_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_FAILURE ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_EQUAL_TO ; 
 int /*<<< orphan*/  arrange_workspace (struct sway_workspace*) ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* config ; 
 int /*<<< orphan*/  container_detach (struct sway_container*) ; 
 int /*<<< orphan*/  container_handle_fullscreen_reparent (struct sway_container*) ; 
 scalar_t__ container_is_floating_or_child (struct sway_container*) ; 
 int /*<<< orphan*/  container_is_scratchpad_hidden (struct sway_container*) ; 
 struct sway_workspace* output_get_active_workspace (int /*<<< orphan*/ ) ; 
 scalar_t__ parse_boolean (char*,scalar_t__) ; 
 int /*<<< orphan*/  sway_assert (struct sway_workspace*,char*) ; 
 int /*<<< orphan*/  workspace_add_floating (struct sway_workspace*,struct sway_container*) ; 
 int /*<<< orphan*/  workspace_consider_destroy (struct sway_workspace*) ; 

struct cmd_results *cmd_sticky(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "sticky", EXPECTED_EQUAL_TO, 1))) {
		return error;
	}
	struct sway_container *container = config->handler_context.container;

	if (container == NULL) {
		return cmd_results_new(CMD_FAILURE, "No current container");
	};

	container->is_sticky = parse_boolean(argv[0], container->is_sticky);

	if (container->is_sticky && container_is_floating_or_child(container) &&
			!container_is_scratchpad_hidden(container)) {
		// move container to active workspace
		struct sway_workspace *active_workspace =
			output_get_active_workspace(container->workspace->output);
		if (!sway_assert(active_workspace,
					"Expected output to have a workspace")) {
			return cmd_results_new(CMD_FAILURE,
					"Expected output to have a workspace");
		}
		if (container->workspace != active_workspace) {
			struct sway_workspace *old_workspace = container->workspace;
			container_detach(container);
			workspace_add_floating(active_workspace, container);
			container_handle_fullscreen_reparent(container);
			arrange_workspace(active_workspace);
			workspace_consider_destroy(old_workspace);
		}
	}

	return cmd_results_new(CMD_SUCCESS, NULL);
}