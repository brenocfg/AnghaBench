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
struct input_config {int /*<<< orphan*/  send_events; int /*<<< orphan*/  identifier; } ;
struct cmd_results {int dummy; } ;
struct TYPE_3__ {struct input_config* input_config; } ;
struct TYPE_4__ {scalar_t__ reading; TYPE_1__ handler_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_FAILURE ; 
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_AT_LEAST ; 
 int /*<<< orphan*/  INT_MIN ; 
 int /*<<< orphan*/  LIBINPUT_CONFIG_SEND_EVENTS_DISABLED ; 
 int /*<<< orphan*/  LIBINPUT_CONFIG_SEND_EVENTS_DISABLED_ON_EXTERNAL_MOUSE ; 
 int /*<<< orphan*/  LIBINPUT_CONFIG_SEND_EVENTS_ENABLED ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* config ; 
 int mode_for_name (char*) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  toggle_send_events (struct input_config*,int,char**) ; 
 int /*<<< orphan*/  toggle_wildcard_send_events (int,char**) ; 

struct cmd_results *input_cmd_events(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "events", EXPECTED_AT_LEAST, 1))) {
		return error;
	}
	struct input_config *ic = config->handler_context.input_config;
	if (!ic) {
		return cmd_results_new(CMD_FAILURE, "No input device defined.");
	}

	if (strcasecmp(argv[0], "enabled") == 0) {
		ic->send_events = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;
	} else if (strcasecmp(argv[0], "disabled") == 0) {
		ic->send_events = LIBINPUT_CONFIG_SEND_EVENTS_DISABLED;
	} else if (strcasecmp(argv[0], "disabled_on_external_mouse") == 0) {
		ic->send_events =
			LIBINPUT_CONFIG_SEND_EVENTS_DISABLED_ON_EXTERNAL_MOUSE;
	} else if (config->reading) {
		return cmd_results_new(CMD_INVALID,
			"Expected 'events <enabled|disabled|disabled_on_external_mouse>'");
	} else if (strcasecmp(argv[0], "toggle") == 0) {
		for (int i = 1; i < argc; ++i) {
			if (mode_for_name(argv[i]) == -1) {
				return cmd_results_new(CMD_INVALID,
						"Invalid toggle mode %s", argv[i]);
			}
		}
		if (strcmp(ic->identifier, "*") == 0) {
			// Update the device input configs and then reset the wildcard
			// config send events mode so that is does not override the device
			// ones. The device ones will be applied when attempting to apply
			// the wildcard config
			toggle_wildcard_send_events(argc - 1, argv + 1);
			ic->send_events = INT_MIN;
		} else {
			toggle_send_events(ic, argc - 1, argv + 1);
		}
	} else {
		return cmd_results_new(CMD_INVALID,
			"Expected 'events <enabled|disabled|disabled_on_external_mouse|"
			"toggle>'");
	}

	return cmd_results_new(CMD_SUCCESS, NULL);
}