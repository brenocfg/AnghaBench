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

struct cmd_results *bar_cmd_icon_theme(int argc, char **argv) {
#if HAVE_TRAY
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "icon_theme", EXPECTED_EQUAL_TO, 1))) {
		return error;
	}

	if (!config->current_bar) {
		return cmd_results_new(CMD_FAILURE, "No bar defined.");
	}

	sway_log(SWAY_DEBUG, "[Bar %s] Setting icon theme to %s",
			config->current_bar->id, argv[0]);
	free(config->current_bar->icon_theme);
	config->current_bar->icon_theme = strdup(argv[0]);
	return cmd_results_new(CMD_SUCCESS, NULL);
#else
	return cmd_results_new(CMD_INVALID,
			"Sway has been compiled without tray support");
#endif
}