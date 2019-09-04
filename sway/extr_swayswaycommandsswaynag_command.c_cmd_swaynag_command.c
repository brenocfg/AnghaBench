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
struct cmd_results {int dummy; } ;
struct TYPE_2__ {char* swaynag_command; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_AT_LEAST ; 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* config ; 
 int /*<<< orphan*/  free (char*) ; 
 char* join_args (char**,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,char*) ; 

struct cmd_results *cmd_swaynag_command(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "swaynag_command", EXPECTED_AT_LEAST, 1))) {
		return error;
	}

	free(config->swaynag_command);
	config->swaynag_command = NULL;

	char *new_command = join_args(argv, argc);
	if (strcmp(new_command, "-") != 0) {
		config->swaynag_command = new_command;
		sway_log(SWAY_DEBUG, "Using custom swaynag command: %s",
				config->swaynag_command);
	} else {
		free(new_command);
	}

	return cmd_results_new(CMD_SUCCESS, NULL);
}