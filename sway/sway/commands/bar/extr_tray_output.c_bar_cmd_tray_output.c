#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct cmd_results {int dummy; } ;
struct TYPE_8__ {int length; char** items; } ;
typedef  TYPE_2__ list_t ;
struct TYPE_9__ {TYPE_1__* current_bar; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; TYPE_2__* tray_outputs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_EQUAL_TO ; 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*) ; 
 TYPE_6__* config ; 
 TYPE_2__* create_list () ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  list_add (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,char*,...) ; 

struct cmd_results *bar_cmd_tray_output(int argc, char **argv) {
#if HAVE_TRAY
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "tray_output", EXPECTED_EQUAL_TO, 1))) {
		return error;
	}

	list_t *outputs = config->current_bar->tray_outputs;
	if (!outputs) {
		config->current_bar->tray_outputs = outputs = create_list();
	}

	if (strcmp(argv[0], "none") == 0) {
		sway_log(SWAY_DEBUG, "Hiding tray on bar: %s", config->current_bar->id);
		for (int i = 0; i < outputs->length; ++i) {
			free(outputs->items[i]);
		}
		outputs->length = 0;
	} else if (strcmp(argv[0], "*") == 0) {
		sway_log(SWAY_DEBUG, "Showing tray on all outputs for bar: %s",
				config->current_bar->id);
		while (outputs->length) {
			free(outputs->items[0]);
			list_del(outputs, 0);
		}
		return cmd_results_new(CMD_SUCCESS, NULL);
	} else {
		sway_log(SWAY_DEBUG, "Showing tray on output '%s' for bar: %s", argv[0],
				config->current_bar->id);
		if (outputs->length == 1 && strcmp(outputs->items[0], "none") == 0) {
			free(outputs->items[0]);
			list_del(outputs, 0);
		}
	}
	list_add(outputs, strdup(argv[0]));

	return cmd_results_new(CMD_SUCCESS, NULL);
#else
	return cmd_results_new(CMD_INVALID,
			"Sway has been compiled without tray support");
#endif
}