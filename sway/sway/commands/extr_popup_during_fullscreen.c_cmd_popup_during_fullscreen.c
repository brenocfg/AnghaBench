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
struct TYPE_2__ {int /*<<< orphan*/  popup_during_fullscreen; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_EQUAL_TO ; 
 int /*<<< orphan*/  POPUP_IGNORE ; 
 int /*<<< orphan*/  POPUP_LEAVE ; 
 int /*<<< orphan*/  POPUP_SMART ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* config ; 
 scalar_t__ strcasecmp (char*,char*) ; 

struct cmd_results *cmd_popup_during_fullscreen(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "popup_during_fullscreen",
					EXPECTED_EQUAL_TO, 1))) {
		return error;
	}

	if (strcasecmp(argv[0], "smart") == 0) {
		config->popup_during_fullscreen = POPUP_SMART;
	} else if (strcasecmp(argv[0], "ignore") == 0) {
		config->popup_during_fullscreen = POPUP_IGNORE;
	} else if (strcasecmp(argv[0], "leave_fullscreen") == 0) {
		config->popup_during_fullscreen = POPUP_LEAVE;
	} else {
		return cmd_results_new(CMD_INVALID, "Expected "
				"'popup_during_fullscreen smart|ignore|leave_fullscreen'");
	}

	return cmd_results_new(CMD_SUCCESS, NULL);
}