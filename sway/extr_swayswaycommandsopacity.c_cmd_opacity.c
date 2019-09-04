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
struct sway_container {float alpha; } ;
struct cmd_results {int dummy; } ;
struct TYPE_3__ {struct sway_container* container; } ;
struct TYPE_4__ {TYPE_1__ handler_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_FAILURE ; 
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_EQUAL_TO ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* config ; 
 int /*<<< orphan*/  container_damage_whole (struct sway_container*) ; 
 int /*<<< orphan*/  parse_opacity (char*,float*) ; 

struct cmd_results *cmd_opacity(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "opacity", EXPECTED_EQUAL_TO, 1))) {
		return error;
	}

	struct sway_container *con = config->handler_context.container;

	if (con == NULL) {
		return cmd_results_new(CMD_FAILURE, "No current container");
	}

	float opacity = 0.0f;

	if (!parse_opacity(argv[0], &opacity)) {
		return cmd_results_new(CMD_INVALID,
				"Invalid value (expected 0..1): %s", argv[0]);
	}

	con->alpha = opacity;
	container_damage_whole(con);

	return cmd_results_new(CMD_SUCCESS, NULL);
}