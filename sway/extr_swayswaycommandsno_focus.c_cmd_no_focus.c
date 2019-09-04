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
struct criteria {int /*<<< orphan*/  type; } ;
struct cmd_results {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  criteria; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  CT_NO_FOCUS ; 
 int /*<<< orphan*/  EXPECTED_AT_LEAST ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* config ; 
 struct criteria* criteria_parse (char*,char**) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ ,struct criteria*) ; 

struct cmd_results *cmd_no_focus(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "no_focus", EXPECTED_AT_LEAST, 1))) {
		return error;
	}

	char *err_str = NULL;
	struct criteria *criteria = criteria_parse(argv[0], &err_str);
	if (!criteria) {
		error = cmd_results_new(CMD_INVALID, err_str);
		free(err_str);
		return error;
	}

	criteria->type = CT_NO_FOCUS;
	list_add(config->criteria, criteria);

	return cmd_results_new(CMD_SUCCESS, NULL);
}