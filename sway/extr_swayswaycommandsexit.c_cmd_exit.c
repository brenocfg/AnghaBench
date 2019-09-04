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
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_EQUAL_TO ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sway_terminate (int /*<<< orphan*/ ) ; 

struct cmd_results *cmd_exit(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "exit", EXPECTED_EQUAL_TO, 0))) {
		return error;
	}
	sway_terminate(0);
	return cmd_results_new(CMD_SUCCESS, NULL);
}