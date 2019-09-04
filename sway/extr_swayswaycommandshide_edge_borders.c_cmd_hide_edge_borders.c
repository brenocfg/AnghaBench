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
struct TYPE_2__ {int hide_lone_tab; int /*<<< orphan*/  hide_edge_borders; int /*<<< orphan*/  saved_edge_borders; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_AT_LEAST ; 
 int /*<<< orphan*/  E_BOTH ; 
 int /*<<< orphan*/  E_HORIZONTAL ; 
 int /*<<< orphan*/  E_NONE ; 
 int /*<<< orphan*/  E_SMART ; 
 int /*<<< orphan*/  E_SMART_NO_GAPS ; 
 int /*<<< orphan*/  E_VERTICAL ; 
 int /*<<< orphan*/  arrange_root () ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* config ; 
 scalar_t__ strcmp (char*,char*) ; 

struct cmd_results *cmd_hide_edge_borders(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "hide_edge_borders", EXPECTED_AT_LEAST, 1))) {
		return error;
	}

	if (strcmp(*argv, "--i3") == 0) {
		config->hide_lone_tab = true;
		++argv;
		--argc;
	} else {
		config->hide_lone_tab = false;
	}

	if (strcmp(argv[0], "none") == 0) {
		config->hide_edge_borders = E_NONE;
	} else if (strcmp(argv[0], "vertical") == 0) {
		config->hide_edge_borders = E_VERTICAL;
	} else if (strcmp(argv[0], "horizontal") == 0) {
		config->hide_edge_borders = E_HORIZONTAL;
	} else if (strcmp(argv[0], "both") == 0) {
		config->hide_edge_borders = E_BOTH;
	} else if (strcmp(argv[0], "smart") == 0) {
		config->hide_edge_borders = E_SMART;
	} else if (strcmp(argv[0], "smart_no_gaps") == 0) {
		config->hide_edge_borders = E_SMART_NO_GAPS;
	} else {
		return cmd_results_new(CMD_INVALID, "Expected 'hide_edge_borders "
				"[--i3] <none|vertical|horizontal|both|smart|smart_no_gaps>'");
	}
	config->saved_edge_borders = config->hide_edge_borders;

	arrange_root();

	return cmd_results_new(CMD_SUCCESS, NULL);
}