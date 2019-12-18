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
struct sway_workspace {int width; int x; int height; int y; struct sway_output* output; } ;
struct sway_output {int dummy; } ;
struct cmd_results {int dummy; } ;
struct TYPE_3__ {struct sway_workspace* workspace; } ;
struct TYPE_4__ {TYPE_1__ handler_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_FAILURE ; 
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_AT_LEAST ; 
 int /*<<< orphan*/  arrange_output (struct sway_output*) ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* config ; 
 struct sway_output* output_in_direction (char*,struct sway_output*,int,int) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  workspace_move_to_output (struct sway_workspace*,struct sway_output*) ; 

__attribute__((used)) static struct cmd_results *cmd_move_workspace(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "move workspace", EXPECTED_AT_LEAST, 1))) {
		return error;
	}

	if (strcasecmp(argv[0], "output") == 0) {
		--argc; ++argv;
	}

	if (!argc) {
		return cmd_results_new(CMD_INVALID,
				"Expected 'move workspace to [output] <output>'");
	}

	struct sway_workspace *workspace = config->handler_context.workspace;
	if (!workspace) {
		return cmd_results_new(CMD_FAILURE, "No workspace to move");
	}

	struct sway_output *old_output = workspace->output;
	int center_x = workspace->width / 2 + workspace->x,
		center_y = workspace->height / 2 + workspace->y;
	struct sway_output *new_output = output_in_direction(argv[0],
			old_output, center_x, center_y);
	if (!new_output) {
		return cmd_results_new(CMD_FAILURE,
			"Can't find output with name/direction '%s'", argv[0]);
	}
	workspace_move_to_output(workspace, new_output);

	arrange_output(old_output);
	arrange_output(new_output);

	return cmd_results_new(CMD_SUCCESS, NULL);
}