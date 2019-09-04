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
struct TYPE_2__ {int /*<<< orphan*/  default_orientation; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_EQUAL_TO ; 
 int /*<<< orphan*/  L_HORIZ ; 
 int /*<<< orphan*/  L_VERT ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* config ; 
 scalar_t__ strcasecmp (char*,char*) ; 

struct cmd_results *cmd_default_orientation(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "default_orientation", EXPECTED_EQUAL_TO, 1))) {
		return error;
	}
	if (strcasecmp(argv[0], "horizontal") == 0) {
		config->default_orientation = L_HORIZ;
	} else if (strcasecmp(argv[0], "vertical") == 0) {
		config->default_orientation = L_VERT;
	} else if (strcasecmp(argv[0], "auto") == 0) {
		// Do nothing
	} else {
		return cmd_results_new(CMD_INVALID,
				"Expected 'orientation <horizontal|vertical|auto>'");
	}
	return cmd_results_new(CMD_SUCCESS, NULL);
}