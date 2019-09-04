#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cmd_results {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_INVALID ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*) ; 

struct cmd_results *bar_cmd_tray_output(int argc, char **argv) {
#if HAVE_TRAY
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "tray_output", EXPECTED_EQUAL_TO, 1))) {
		return error;
	}

	if (!config->current_bar) {
		return cmd_results_new(CMD_FAILURE, "No bar defined.");
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
	} else {
		sway_log(SWAY_DEBUG, "Showing tray on output '%s' for bar: %s", argv[0],
				config->current_bar->id);
	}
	list_add(outputs, strdup(argv[0]));

	return cmd_results_new(CMD_SUCCESS, NULL);
#else
	return cmd_results_new(CMD_INVALID,
			"Sway has been compiled without tray support");
#endif
}