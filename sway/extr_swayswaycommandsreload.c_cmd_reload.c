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
struct cmd_results {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  current_config_path; } ;
struct TYPE_3__ {int /*<<< orphan*/  wl_event_loop; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_FAILURE ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_EQUAL_TO ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* config ; 
 int /*<<< orphan*/  do_reload ; 
 int /*<<< orphan*/  load_main_config (int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  wl_event_loop_add_idle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct cmd_results *cmd_reload(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "reload", EXPECTED_EQUAL_TO, 0))) {
		return error;
	}

	if (!load_main_config(config->current_config_path, true, true)) {
		return cmd_results_new(CMD_FAILURE, "Error(s) reloading config.");
	}

	// The reload command frees a lot of stuff, so to avoid use-after-frees
	// we schedule the reload to happen using an idle event.
	wl_event_loop_add_idle(server.wl_event_loop, do_reload, NULL);

	return cmd_results_new(CMD_SUCCESS, NULL);
}