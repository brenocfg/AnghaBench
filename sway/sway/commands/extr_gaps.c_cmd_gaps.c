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
struct TYPE_2__ {scalar_t__ reloading; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  EXPECTED_AT_LEAST ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 TYPE_1__* config ; 
 int /*<<< orphan*/  expected_defaults ; 
 int /*<<< orphan*/  expected_runtime ; 
 struct cmd_results* gaps_set_defaults (int,char**) ; 
 struct cmd_results* gaps_set_runtime (int,char**) ; 

struct cmd_results *cmd_gaps(int argc, char **argv) {
	struct cmd_results *error = checkarg(argc, "gaps", EXPECTED_AT_LEAST, 2);
	if (error) {
		return error;
	}

	bool config_loading = !config->active || config->reloading;

	if (argc == 2) {
		return gaps_set_defaults(argc, argv);
	}
	if (argc == 4 && !config_loading) {
		return gaps_set_runtime(argc, argv);
	}
	if (config_loading) {
		return cmd_results_new(CMD_INVALID, "Expected %s", expected_defaults);
	}
	return cmd_results_new(CMD_INVALID, "Expected %s or %s",
			expected_runtime, expected_defaults);
}