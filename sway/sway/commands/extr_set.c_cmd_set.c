#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sway_variable {int /*<<< orphan*/  value; int /*<<< orphan*/  name; } ;
struct cmd_results {int dummy; } ;
struct TYPE_5__ {TYPE_1__* symbols; } ;
struct TYPE_4__ {int length; struct sway_variable** items; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_FAILURE ; 
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_AT_LEAST ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  compare_set_qsort ; 
 TYPE_3__* config ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  join_args (char**,int) ; 
 int /*<<< orphan*/  list_add (TYPE_1__*,struct sway_variable*) ; 
 int /*<<< orphan*/  list_qsort (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct sway_variable* malloc (int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strdup (char*) ; 

struct cmd_results *cmd_set(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "set", EXPECTED_AT_LEAST, 2))) {
		return error;
	}

	if (argv[0][0] != '$') {
		return cmd_results_new(CMD_INVALID, "variable '%s' must start with $", argv[0]);
	}

	struct sway_variable *var = NULL;
	// Find old variable if it exists
	int i;
	for (i = 0; i < config->symbols->length; ++i) {
		var = config->symbols->items[i];
		if (strcmp(var->name, argv[0]) == 0) {
			break;
		}
		var = NULL;
	}
	if (var) {
		free(var->value);
	} else {
		var = malloc(sizeof(struct sway_variable));
		if (!var) {
			return cmd_results_new(CMD_FAILURE, "Unable to allocate variable");
		}
		var->name = strdup(argv[0]);
		list_add(config->symbols, var);
		list_qsort(config->symbols, compare_set_qsort);
	}
	var->value = join_args(argv + 1, argc - 1);
	return cmd_results_new(CMD_SUCCESS, NULL);
}