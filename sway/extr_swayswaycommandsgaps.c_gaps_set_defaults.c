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
struct cmd_results {int dummy; } ;
struct TYPE_3__ {int top; int right; int bottom; int left; } ;
struct TYPE_4__ {int gaps_inner; TYPE_1__ gaps_outer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_EQUAL_TO ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* config ; 
 int /*<<< orphan*/  expected_defaults ; 
 int /*<<< orphan*/  prevent_invalid_outer_gaps () ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int strtol (char*,char**,int) ; 

__attribute__((used)) static struct cmd_results *gaps_set_defaults(int argc, char **argv) {
	struct cmd_results *error = checkarg(argc, "gaps", EXPECTED_EQUAL_TO, 2);
	if (error) {
		return error;
	}

	char *end;
	int amount = strtol(argv[1], &end, 10);
	if (strlen(end) && strcasecmp(end, "px") != 0) {
		return cmd_results_new(CMD_INVALID, "Expected %s", expected_defaults);
	}

	bool valid = false;
	if (!strcasecmp(argv[0], "inner")) {
		valid = true;
		config->gaps_inner = (amount >= 0) ? amount : 0;
	} else {
		if (!strcasecmp(argv[0], "outer") || !strcasecmp(argv[0], "vertical")
				|| !strcasecmp(argv[0], "top")) {
			valid = true;
			config->gaps_outer.top = amount;
		}
		if (!strcasecmp(argv[0], "outer") || !strcasecmp(argv[0], "horizontal")
				|| !strcasecmp(argv[0], "right")) {
			valid = true;
			config->gaps_outer.right = amount;
		}
		if (!strcasecmp(argv[0], "outer") || !strcasecmp(argv[0], "vertical")
				|| !strcasecmp(argv[0], "bottom")) {
			valid = true;
			config->gaps_outer.bottom = amount;
		}
		if (!strcasecmp(argv[0], "outer") || !strcasecmp(argv[0], "horizontal")
				|| !strcasecmp(argv[0], "left")) {
			valid = true;
			config->gaps_outer.left = amount;
		}
	}
	if (!valid) {
		return cmd_results_new(CMD_INVALID, "Expected %s", expected_defaults);
	}

	prevent_invalid_outer_gaps();
	return cmd_results_new(CMD_SUCCESS, NULL);
}