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
struct TYPE_2__ {int urgent_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_AT_LEAST ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* config ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strtol (char*,char**,int) ; 

struct cmd_results *cmd_force_display_urgency_hint(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "force_display_urgency_hint",
					EXPECTED_AT_LEAST, 1))) {
		return error;
	}

	char *err;
	int timeout = (int)strtol(argv[0], &err, 10);
	if (*err) {
		if (strcmp(err, "ms") != 0) {
			return cmd_results_new(CMD_INVALID,
					"Expected 'force_display_urgency_hint <timeout> ms'");
		}
	}

	config->urgent_timeout = timeout > 0 ? timeout : 0;

	return cmd_results_new(CMD_SUCCESS, NULL);
}