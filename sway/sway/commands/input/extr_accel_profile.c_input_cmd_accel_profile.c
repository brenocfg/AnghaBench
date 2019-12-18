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
struct input_config {int /*<<< orphan*/  accel_profile; } ;
struct cmd_results {int dummy; } ;
struct TYPE_3__ {struct input_config* input_config; } ;
struct TYPE_4__ {TYPE_1__ handler_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_FAILURE ; 
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_AT_LEAST ; 
 int /*<<< orphan*/  LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE ; 
 int /*<<< orphan*/  LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* config ; 
 scalar_t__ strcasecmp (char*,char*) ; 

struct cmd_results *input_cmd_accel_profile(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "accel_profile", EXPECTED_AT_LEAST, 1))) {
		return error;
	}
	struct input_config *ic = config->handler_context.input_config;
	if (!ic) {
		return cmd_results_new(CMD_FAILURE, "No input device defined.");
	}

	if (strcasecmp(argv[0], "adaptive") == 0) {
		ic->accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE;
	} else if (strcasecmp(argv[0], "flat") == 0) {
		ic->accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT;
	} else {
		return cmd_results_new(CMD_INVALID,
				"Expected 'accel_profile <adaptive|flat>'");
	}

	return cmd_results_new(CMD_SUCCESS, NULL);
}