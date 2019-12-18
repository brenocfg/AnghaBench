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
 int /*<<< orphan*/  EXPECTED_AT_LEAST ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* config ; 
 int /*<<< orphan*/  container_damage_whole (struct sway_container*) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 float strtof (char*,char**) ; 

struct cmd_results *cmd_opacity(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "opacity", EXPECTED_AT_LEAST, 1))) {
		return error;
	}

	struct sway_container *con = config->handler_context.container;

	if (con == NULL) {
		return cmd_results_new(CMD_FAILURE, "No current container");
	}

	char *err;
	float val = strtof(argc == 1 ? argv[0] : argv[1], &err);
	if (*err) {
		return cmd_results_new(CMD_INVALID, "opacity float invalid");
	}

	if (!strcasecmp(argv[0], "plus")) {
		val = con->alpha + val;
	} else if (!strcasecmp(argv[0], "minus")) {
		val = con->alpha - val;
	} else if (argc > 1 && strcasecmp(argv[0], "set")) {
		return cmd_results_new(CMD_INVALID,
				"Expected: set|plus|minus <0..1>: %s", argv[0]);
	}

	if (val < 0 || val > 1) {
		return cmd_results_new(CMD_FAILURE, "opacity value out of bounds");
	}

	con->alpha = val;
	container_damage_whole(con);
	return cmd_results_new(CMD_SUCCESS, NULL);
}