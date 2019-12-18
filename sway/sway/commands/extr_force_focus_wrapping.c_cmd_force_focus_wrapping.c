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
struct TYPE_2__ {scalar_t__ focus_wrapping; scalar_t__ reading; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_EQUAL_TO ; 
 int /*<<< orphan*/  SWAY_INFO ; 
 scalar_t__ WRAP_FORCE ; 
 scalar_t__ WRAP_YES ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* config ; 
 int /*<<< orphan*/  config_add_swaynag_warning (char*) ; 
 scalar_t__ parse_boolean (char*,int) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 

struct cmd_results *cmd_force_focus_wrapping(int argc, char **argv) {
	sway_log(SWAY_INFO, "Warning: force_focus_wrapping is deprecated. "
		"Use focus_wrapping instead.");
	if (config->reading) {
		config_add_swaynag_warning("force_focus_wrapping is deprecated. "
			"Use focus_wrapping instead.");
	}

	struct cmd_results *error =
		checkarg(argc, "force_focus_wrapping", EXPECTED_EQUAL_TO, 1);
	if (error) {
		return error;
	}

	if (parse_boolean(argv[0], config->focus_wrapping == WRAP_FORCE)) {
		config->focus_wrapping = WRAP_FORCE;
	} else {
		config->focus_wrapping = WRAP_YES;
	}

	return cmd_results_new(CMD_SUCCESS, NULL);
}