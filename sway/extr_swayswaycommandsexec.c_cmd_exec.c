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
 int /*<<< orphan*/  CMD_DEFER ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 struct cmd_results* cmd_exec_always (int,char**) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* config ; 
 int /*<<< orphan*/  free (char*) ; 
 char* join_args (char**,int) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,char*) ; 

struct cmd_results *cmd_exec(int argc, char **argv) {
	if (!config->active) return cmd_results_new(CMD_DEFER, NULL);
	if (config->reloading) {
		char *args = join_args(argv, argc);
		sway_log(SWAY_DEBUG, "Ignoring 'exec %s' due to reload", args);
		free(args);
		return cmd_results_new(CMD_SUCCESS, NULL);
	}
	return cmd_exec_always(argc, argv);
}