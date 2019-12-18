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
struct TYPE_2__ {int /*<<< orphan*/  border_thickness; int /*<<< orphan*/  border; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_NONE ; 
 int /*<<< orphan*/  B_NORMAL ; 
 int /*<<< orphan*/  B_PIXEL ; 
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_AT_LEAST ; 
 int /*<<< orphan*/  atoi (char*) ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* config ; 
 scalar_t__ strcmp (char*,char*) ; 

struct cmd_results *cmd_default_border(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "default_border", EXPECTED_AT_LEAST, 1))) {
		return error;
	}

	if (strcmp(argv[0], "none") == 0) {
		config->border = B_NONE;
	} else if (strcmp(argv[0], "normal") == 0) {
		config->border = B_NORMAL;
	} else if (strcmp(argv[0], "pixel") == 0) {
		config->border = B_PIXEL;
	} else {
		return cmd_results_new(CMD_INVALID,
				"Expected 'default_border <none|normal|pixel>' or 'default_border <normal|pixel> <px>'");
	}
	if (argc == 2) {
		config->border_thickness = atoi(argv[1]);
	}

	return cmd_results_new(CMD_SUCCESS, NULL);
}