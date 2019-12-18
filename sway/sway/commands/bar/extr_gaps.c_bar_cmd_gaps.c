#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cmd_results {int dummy; } ;
struct TYPE_6__ {TYPE_2__* current_bar; int /*<<< orphan*/  reading; } ;
struct TYPE_4__ {int top; int right; int bottom; int left; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; TYPE_1__ gaps; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_AT_LEAST ; 
 int /*<<< orphan*/  EXPECTED_AT_MOST ; 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* config ; 
 int /*<<< orphan*/  ipc_event_barconfig_update (TYPE_2__*) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int strtol (char*,char**,int) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int,int,int,int,int /*<<< orphan*/ ) ; 

struct cmd_results *bar_cmd_gaps(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "gaps", EXPECTED_AT_LEAST, 1))) {
		return error;
	}
	if ((error = checkarg(argc, "gaps", EXPECTED_AT_MOST, 4))) {
		return error;
	}

	int top = 0, right = 0, bottom = 0, left = 0;

	for (int i = 0; i < argc; i++) {
		char *end;
		int amount = strtol(argv[i], &end, 10);
		if (strlen(end) && strcasecmp(end, "px") != 0) {
			return cmd_results_new(CMD_INVALID,
					"Expected 'bar [<bar-id>] gaps <all> | <horizonal> "
					"<vertical> | <top> <right> <bottom> <left>'");
		}

		if (i == 0) {
			top = amount;
		}
		if (i == 0 || i == 1) {
			right = amount;
		}
		if (i == 0 || i == 2) {
			bottom = amount;
		}
		if (i == 0 || i == 1 || i == 3) {
			left = amount;
		}
	}

	config->current_bar->gaps.top = top;
	config->current_bar->gaps.right = right;
	config->current_bar->gaps.bottom = bottom;
	config->current_bar->gaps.left = left;

	sway_log(SWAY_DEBUG, "Setting bar gaps to %d %d %d %d on bar: %s",
			config->current_bar->gaps.top, config->current_bar->gaps.right,
			config->current_bar->gaps.bottom, config->current_bar->gaps.left,
			config->current_bar->id);

	if (!config->reading) {
		ipc_event_barconfig_update(config->current_bar);
	}

	return cmd_results_new(CMD_SUCCESS, NULL);
}