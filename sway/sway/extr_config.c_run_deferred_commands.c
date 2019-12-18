#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct cmd_results {scalar_t__ status; int /*<<< orphan*/  error; } ;
struct TYPE_6__ {int length; struct cmd_results** items; } ;
typedef  TYPE_1__ list_t ;
struct TYPE_8__ {TYPE_3__* cmd_queue; } ;
struct TYPE_7__ {char** items; scalar_t__ length; } ;

/* Variables and functions */
 scalar_t__ CMD_SUCCESS ; 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  SWAY_ERROR ; 
 TYPE_5__* config ; 
 TYPE_1__* execute_command (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_cmd_results (struct cmd_results*) ; 
 int /*<<< orphan*/  list_del (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_free (TYPE_1__*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,...) ; 

void run_deferred_commands(void) {
	if (!config->cmd_queue->length) {
		return;
	}
	sway_log(SWAY_DEBUG, "Running deferred commands");
	while (config->cmd_queue->length) {
		char *line = config->cmd_queue->items[0];
		list_t *res_list = execute_command(line, NULL, NULL);
		for (int i = 0; i < res_list->length; ++i) {
			struct cmd_results *res = res_list->items[i];
			if (res->status != CMD_SUCCESS) {
				sway_log(SWAY_ERROR, "Error on line '%s': %s",
						line, res->error);
			}
			free_cmd_results(res);
		}
		list_del(config->cmd_queue, 0);
		list_free(res_list);
		free(line);
	}
}