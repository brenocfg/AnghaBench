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
struct bar_config {int tray_padding; int /*<<< orphan*/  id; } ;
struct TYPE_2__ {struct bar_config* current_bar; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_AT_LEAST ; 
 int /*<<< orphan*/  EXPECTED_AT_MOST ; 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__* config ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 int strtol (char*,char**,int) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

struct cmd_results *bar_cmd_tray_padding(int argc, char **argv) {
#if HAVE_TRAY
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "tray_padding", EXPECTED_AT_LEAST, 1))) {
		return error;
	}
	if ((error = checkarg(argc, "tray_padding", EXPECTED_AT_MOST, 2))) {
		return error;
	}

	struct bar_config *bar = config->current_bar;

	char *end;
	int padding = strtol(argv[0], &end, 10);
	if (padding < 0 || (*end != '\0' && strcasecmp(end, "px") != 0)) {
		return cmd_results_new(CMD_INVALID,
				"[Bar %s] Invalid tray padding value: %s", bar->id, argv[0]);
	}

	if (argc == 2 && strcasecmp(argv[1], "px") != 0) {
		return cmd_results_new(CMD_INVALID,
				"Expected 'tray_padding <px> [px]'");
	}

	sway_log(SWAY_DEBUG, "[Bar %s] Setting tray padding to %d", bar->id, padding);
	config->current_bar->tray_padding = padding;
	return cmd_results_new(CMD_SUCCESS, NULL);
#else
	return cmd_results_new(CMD_INVALID,
			"Sway has been compiled without tray support");
#endif
}