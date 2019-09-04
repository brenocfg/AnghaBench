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
struct TYPE_2__ {int /*<<< orphan*/  tiling_drag; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_EQUAL_TO ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* config ; 
 int /*<<< orphan*/  parse_boolean (char*,int /*<<< orphan*/ ) ; 

struct cmd_results *cmd_tiling_drag(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "tiling_drag", EXPECTED_EQUAL_TO, 1))) {
		return error;
	}

	config->tiling_drag = parse_boolean(argv[0], config->tiling_drag);

	return cmd_results_new(CMD_SUCCESS, NULL);
}