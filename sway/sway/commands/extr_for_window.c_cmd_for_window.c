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
struct criteria {int /*<<< orphan*/  cmdlist; int /*<<< orphan*/  raw; int /*<<< orphan*/  type; } ;
struct cmd_results {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  criteria; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  CT_COMMAND ; 
 int /*<<< orphan*/  EXPECTED_AT_LEAST ; 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* config ; 
 scalar_t__ criteria_already_exists (struct criteria*) ; 
 int /*<<< orphan*/  criteria_destroy (struct criteria*) ; 
 struct criteria* criteria_parse (char*,char**) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  join_args (char**,int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ ,struct criteria*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct cmd_results *cmd_for_window(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "for_window", EXPECTED_AT_LEAST, 2))) {
		return error;
	}

	char *err_str = NULL;
	struct criteria *criteria = criteria_parse(argv[0], &err_str);
	if (!criteria) {
		error = cmd_results_new(CMD_INVALID, err_str);
		free(err_str);
		return error;
	}

	criteria->type = CT_COMMAND;
	criteria->cmdlist = join_args(argv + 1, argc - 1);

	// Check if it already exists
	if (criteria_already_exists(criteria)) {
		sway_log(SWAY_DEBUG, "for_window already exists: '%s' -> '%s'",
				criteria->raw, criteria->cmdlist);
		criteria_destroy(criteria);
		return cmd_results_new(CMD_SUCCESS, NULL);
	}

	list_add(config->criteria, criteria);
	sway_log(SWAY_DEBUG, "for_window: '%s' -> '%s' added", criteria->raw, criteria->cmdlist);

	return cmd_results_new(CMD_SUCCESS, NULL);
}