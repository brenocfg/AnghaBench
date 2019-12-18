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
struct bar_config {char const* id; } ;
struct TYPE_4__ {TYPE_1__* bars; struct bar_config* current_bar; scalar_t__ reading; } ;
struct TYPE_3__ {int length; struct bar_config** items; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_AT_LEAST ; 
 int /*<<< orphan*/  EXPECTED_AT_MOST ; 
 struct cmd_results* bar_set_mode (struct bar_config*,char const*) ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* config ; 
 scalar_t__ strcmp (char const*,char*) ; 

struct cmd_results *bar_cmd_mode(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "mode", EXPECTED_AT_LEAST, 1))) {
		return error;
	}
	if ((error = checkarg(argc, "mode", EXPECTED_AT_MOST, 2))) {
		return error;
	}
	if (config->reading && argc > 1) {
		return cmd_results_new(CMD_INVALID,
				"Unexpected value %s in config mode", argv[1]);
	}

	if (config->current_bar && argc == 2 &&
			strcmp(config->current_bar->id, argv[1]) != 0) {
		return cmd_results_new(CMD_INVALID, "Conflicting bar ids: %s and %s",
				config->current_bar->id, argv[1]);
	}

	const char *mode = argv[0];
	if (config->reading) {
		error = bar_set_mode(config->current_bar, mode);
	} else {
		const char *id = argc == 2 ? argv[1] : NULL;
		for (int i = 0; i < config->bars->length; ++i) {
			struct bar_config *bar = config->bars->items[i];
			if (id) {
				if (strcmp(id, bar->id) == 0) {
					error = bar_set_mode(bar, mode);
					break;
				}
			} else if ((error = bar_set_mode(bar, mode))) {
				break;
			}
		}
	}
	return error ? error : cmd_results_new(CMD_SUCCESS, NULL);
}