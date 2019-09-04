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
struct TYPE_2__ {int /*<<< orphan*/  mouse_warping; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_FAILURE ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_EQUAL_TO ; 
 int /*<<< orphan*/  WARP_CONTAINER ; 
 int /*<<< orphan*/  WARP_NO ; 
 int /*<<< orphan*/  WARP_OUTPUT ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* config ; 
 scalar_t__ strcasecmp (char*,char*) ; 

struct cmd_results *cmd_mouse_warping(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "mouse_warping", EXPECTED_EQUAL_TO, 1))) {
		return error;
	} else if (strcasecmp(argv[0], "container") == 0) {
		config->mouse_warping = WARP_CONTAINER;
	} else if (strcasecmp(argv[0], "output") == 0) {
		config->mouse_warping = WARP_OUTPUT;
	} else if (strcasecmp(argv[0], "none") == 0) {
		config->mouse_warping = WARP_NO;
	} else {
		return cmd_results_new(CMD_FAILURE,
				"Expected 'mouse_warping output|container|none'");
	}
	return cmd_results_new(CMD_SUCCESS, NULL);
}