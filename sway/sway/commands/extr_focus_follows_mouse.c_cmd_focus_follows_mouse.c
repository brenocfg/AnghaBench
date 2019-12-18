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
struct TYPE_2__ {int /*<<< orphan*/  focus_follows_mouse; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_FAILURE ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_EQUAL_TO ; 
 int /*<<< orphan*/  FOLLOWS_ALWAYS ; 
 int /*<<< orphan*/  FOLLOWS_NO ; 
 int /*<<< orphan*/  FOLLOWS_YES ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* config ; 
 scalar_t__ strcmp (char*,char*) ; 

struct cmd_results *cmd_focus_follows_mouse(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "focus_follows_mouse", EXPECTED_EQUAL_TO, 1))) {
		return error;
	} else if(strcmp(argv[0], "no") == 0) {
		config->focus_follows_mouse = FOLLOWS_NO;
	} else if(strcmp(argv[0], "yes") == 0) {
		config->focus_follows_mouse = FOLLOWS_YES;
	} else if(strcmp(argv[0], "always") == 0) {
		config->focus_follows_mouse = FOLLOWS_ALWAYS;
	} else {
		return cmd_results_new(CMD_FAILURE,
				"Expected 'focus_follows_mouse no|yes|always'");
	}
	return cmd_results_new(CMD_SUCCESS, NULL);
}