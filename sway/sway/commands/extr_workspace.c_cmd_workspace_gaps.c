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
struct TYPE_2__ {int top; int right; int bottom; int left; } ;
struct workspace_config {int gaps_inner; TYPE_1__ gaps_outer; } ;
struct cmd_results {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_FAILURE ; 
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  EXPECTED_EQUAL_TO ; 
 int INT_MIN ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* join_args (char**,int) ; 
 int /*<<< orphan*/  prevent_invalid_outer_gaps (struct workspace_config*) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int strtol (char*,char**,int) ; 
 struct workspace_config* workspace_config_find_or_create (char*) ; 

__attribute__((used)) static struct cmd_results *cmd_workspace_gaps(int argc, char **argv,
		int gaps_location) {
	const char expected[] = "Expected 'workspace <name> gaps "
		"inner|outer|horizontal|vertical|top|right|bottom|left <px>'";
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "workspace", EXPECTED_EQUAL_TO,
					gaps_location + 3))) {
		return error;
	}
	char *ws_name = join_args(argv, argc - 3);
	struct workspace_config *wsc = workspace_config_find_or_create(ws_name);
	free(ws_name);
	if (!wsc) {
		return cmd_results_new(CMD_FAILURE,
				"Unable to allocate workspace output");
	}

	char *end;
	int amount = strtol(argv[gaps_location + 2], &end, 10);
	if (strlen(end)) {
		return cmd_results_new(CMD_FAILURE, expected);
	}

	bool valid = false;
	char *type = argv[gaps_location + 1];
	if (!strcasecmp(type, "inner")) {
		valid = true;
		wsc->gaps_inner = (amount >= 0) ? amount : 0;
	} else {
		if (!strcasecmp(type, "outer") || !strcasecmp(type, "vertical")
				|| !strcasecmp(type, "top")) {
			valid = true;
			wsc->gaps_outer.top = amount;
		}
		if (!strcasecmp(type, "outer") || !strcasecmp(type, "horizontal")
				|| !strcasecmp(type, "right")) {
			valid = true;
			wsc->gaps_outer.right = amount;
		}
		if (!strcasecmp(type, "outer") || !strcasecmp(type, "vertical")
				|| !strcasecmp(type, "bottom")) {
			valid = true;
			wsc->gaps_outer.bottom = amount;
		}
		if (!strcasecmp(type, "outer") || !strcasecmp(type, "horizontal")
				|| !strcasecmp(type, "left")) {
			valid = true;
			wsc->gaps_outer.left = amount;
		}
	}
	if (!valid) {
		return cmd_results_new(CMD_INVALID, expected);
	}

	// Prevent invalid gaps configurations.
	if (wsc->gaps_inner != INT_MIN && wsc->gaps_inner < 0) {
		wsc->gaps_inner = 0;
	}
	prevent_invalid_outer_gaps(wsc);

	return error;
}