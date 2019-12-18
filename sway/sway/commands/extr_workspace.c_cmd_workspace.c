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
struct workspace_config {int /*<<< orphan*/  outputs; } ;
struct sway_workspace {int dummy; } ;
struct sway_seat {char* prev_workspace_name; } ;
struct cmd_results {int dummy; } ;
struct TYPE_6__ {struct sway_seat* seat; } ;
struct TYPE_8__ {TYPE_2__ handler_context; int /*<<< orphan*/  active; scalar_t__ reading; } ;
struct TYPE_7__ {scalar_t__ fullscreen_global; TYPE_1__* outputs; } ;
struct TYPE_5__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_DEFER ; 
 int /*<<< orphan*/  CMD_FAILURE ; 
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_AT_LEAST ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*,...) ; 
 struct cmd_results* cmd_workspace_gaps (int,char**,int) ; 
 TYPE_4__* config ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  isdigit (char) ; 
 char* join_args (char**,int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* root ; 
 int /*<<< orphan*/  seat_consider_warp_to_focus (struct sway_seat*) ; 
 struct sway_workspace* seat_get_focused_workspace (struct sway_seat*) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 struct sway_workspace* workspace_by_name (char*) ; 
 struct sway_workspace* workspace_by_number (char*) ; 
 struct workspace_config* workspace_config_find_or_create (char*) ; 
 struct sway_workspace* workspace_create (int /*<<< orphan*/ *,char*) ; 
 struct sway_workspace* workspace_output_next (struct sway_workspace*,int) ; 
 struct sway_workspace* workspace_output_prev (struct sway_workspace*,int) ; 
 int /*<<< orphan*/  workspace_switch (struct sway_workspace*,int) ; 

struct cmd_results *cmd_workspace(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "workspace", EXPECTED_AT_LEAST, 1))) {
		return error;
	}

	int output_location = -1;
	int gaps_location = -1;

	for (int i = 0; i < argc; ++i) {
		if (strcasecmp(argv[i], "output") == 0) {
			output_location = i;
			break;
		}
	}
	for (int i = 0; i < argc; ++i) {
		if (strcasecmp(argv[i], "gaps") == 0) {
			gaps_location = i;
			break;
		}
	}
	if (output_location >= 0) {
		if ((error = checkarg(argc, "workspace", EXPECTED_AT_LEAST,
						output_location + 2))) {
			return error;
		}
		char *ws_name = join_args(argv, output_location);
		struct workspace_config *wsc = workspace_config_find_or_create(ws_name);
		free(ws_name);
		if (!wsc) {
			return cmd_results_new(CMD_FAILURE,
					"Unable to allocate workspace output");
		}
		for (int i = output_location + 1; i < argc; ++i) {
			list_add(wsc->outputs, strdup(argv[i]));
		}
	} else if (gaps_location >= 0) {
		if ((error = cmd_workspace_gaps(argc, argv, gaps_location))) {
			return error;
		}
	} else {
		if (config->reading || !config->active) {
			return cmd_results_new(CMD_DEFER, NULL);
		} else if (!root->outputs->length) {
			return cmd_results_new(CMD_INVALID,
					"Can't run this command while there's no outputs connected.");
		}

		if (root->fullscreen_global) {
			return cmd_results_new(CMD_FAILURE, "workspace",
				"Can't switch workspaces while fullscreen global");
		}

		bool no_auto_back_and_forth = false;
		while (strcasecmp(argv[0], "--no-auto-back-and-forth") == 0) {
			no_auto_back_and_forth = true;
			if ((error = checkarg(--argc, "workspace", EXPECTED_AT_LEAST, 1))) {
				return error;
			}
			++argv;
		}

		bool create = argc > 1 && strcasecmp(argv[1], "--create") == 0;
		struct sway_seat *seat = config->handler_context.seat;
		struct sway_workspace *current = seat_get_focused_workspace(seat);
		if (!current) {
			return cmd_results_new(CMD_FAILURE, "No workspace to switch from");
		}

		struct sway_workspace *ws = NULL;
		if (strcasecmp(argv[0], "number") == 0) {
			if (argc < 2) {
				return cmd_results_new(CMD_INVALID,
						"Expected workspace number");
			}
			if (!isdigit(argv[1][0])) {
				return cmd_results_new(CMD_INVALID,
						"Invalid workspace number '%s'", argv[1]);
			}
			if (!(ws = workspace_by_number(argv[1]))) {
				char *name = join_args(argv + 1, argc - 1);
				ws = workspace_create(NULL, name);
				free(name);
			}
		} else if (strcasecmp(argv[0], "next") == 0 ||
				strcasecmp(argv[0], "prev") == 0 ||
				strcasecmp(argv[0], "current") == 0) {
			ws = workspace_by_name(argv[0]);
		} else if (strcasecmp(argv[0], "next_on_output") == 0) {
			ws = workspace_output_next(current, create);
		} else if (strcasecmp(argv[0], "prev_on_output") == 0) {
			ws = workspace_output_prev(current, create);
		} else if (strcasecmp(argv[0], "back_and_forth") == 0) {
			if (!seat->prev_workspace_name) {
				return cmd_results_new(CMD_INVALID,
						"There is no previous workspace");
			}
			if (!(ws = workspace_by_name(argv[0]))) {
				ws = workspace_create(NULL, seat->prev_workspace_name);
			}
		} else {
			char *name = join_args(argv, argc);
			if (!(ws = workspace_by_name(name))) {
				ws = workspace_create(NULL, name);
			}
			free(name);
		}
		if (!ws) {
			return cmd_results_new(CMD_FAILURE, "No workspace to switch to");
		}
		workspace_switch(ws, no_auto_back_and_forth);
		seat_consider_warp_to_focus(seat);
	}
	return cmd_results_new(CMD_SUCCESS, NULL);
}