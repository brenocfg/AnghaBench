#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cmd_results {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  swaynag_config_errors; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_EQUAL_TO ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* config ; 
 int /*<<< orphan*/  load_include_configs (char*,TYPE_1__*,int /*<<< orphan*/ *) ; 

struct cmd_results *cmd_include(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "include", EXPECTED_EQUAL_TO, 1))) {
		return error;
	}

	// We don't care if the included config(s) fails to load.
	load_include_configs(argv[0], config, &config->swaynag_config_errors);

	return cmd_results_new(CMD_SUCCESS, NULL);
}