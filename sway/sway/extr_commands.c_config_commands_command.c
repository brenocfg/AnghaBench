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
struct command_policy {char* command; int context; } ;
struct cmd_results {int dummy; } ;
struct cmd_handler {int dummy; } ;
typedef  enum command_context { ____Placeholder_command_context } command_context ;
typedef  int /*<<< orphan*/  context_names ;
struct TYPE_4__ {TYPE_1__* command_policies; } ;
struct TYPE_3__ {int length; struct command_policy** items; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_BLOCK_END ; 
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  CONTEXT_ALL ; 
 int /*<<< orphan*/  CONTEXT_BINDING ; 
 int /*<<< orphan*/  CONTEXT_CONFIG ; 
 int /*<<< orphan*/  CONTEXT_CRITERIA ; 
 int /*<<< orphan*/  CONTEXT_IPC ; 
 int /*<<< orphan*/  SWAY_INFO ; 
 struct command_policy* alloc_command_policy (char*) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* config ; 
 struct cmd_handler* find_handler (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_argv (int,char**) ; 
 int /*<<< orphan*/  list_add (TYPE_1__*,struct command_policy*) ; 
 char** split_args (char*,int*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  sway_assert (struct command_policy*,char*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,char*,int) ; 

struct cmd_results *config_commands_command(char *exec) {
	struct cmd_results *results = NULL;
	int argc;
	char **argv = split_args(exec, &argc);
	if (!argc) {
		results = cmd_results_new(CMD_SUCCESS, NULL);
		goto cleanup;
	}

	// Find handler for the command this is setting a policy for
	char *cmd = argv[0];

	if (strcmp(cmd, "}") == 0) {
		results = cmd_results_new(CMD_BLOCK_END, NULL);
		goto cleanup;
	}

	struct cmd_handler *handler = find_handler(cmd, NULL, 0);
	if (!handler && strcmp(cmd, "*") != 0) {
		results = cmd_results_new(CMD_INVALID,
			"Unknown/invalid command '%s'", cmd);
		goto cleanup;
	}

	enum command_context context = 0;

	struct {
		char *name;
		enum command_context context;
	} context_names[] = {
		{ "config", CONTEXT_CONFIG },
		{ "binding", CONTEXT_BINDING },
		{ "ipc", CONTEXT_IPC },
		{ "criteria", CONTEXT_CRITERIA },
		{ "all", CONTEXT_ALL },
	};

	for (int i = 1; i < argc; ++i) {
		size_t j;
		for (j = 0; j < sizeof(context_names) / sizeof(context_names[0]); ++j) {
			if (strcmp(context_names[j].name, argv[i]) == 0) {
				break;
			}
		}
		if (j == sizeof(context_names) / sizeof(context_names[0])) {
			results = cmd_results_new(CMD_INVALID,
					"Invalid command context %s", argv[i]);
			goto cleanup;
		}
		context |= context_names[j].context;
	}

	struct command_policy *policy = NULL;
	for (int i = 0; i < config->command_policies->length; ++i) {
		struct command_policy *p = config->command_policies->items[i];
		if (strcmp(p->command, cmd) == 0) {
			policy = p;
			break;
		}
	}
	if (!policy) {
		policy = alloc_command_policy(cmd);
		if (!sway_assert(policy, "Unable to allocate security policy")) {
			results = cmd_results_new(CMD_INVALID,
					"Unable to allocate memory");
			goto cleanup;
		}
		list_add(config->command_policies, policy);
	}
	policy->context = context;

	sway_log(SWAY_INFO, "Set command policy for %s to %d",
			policy->command, policy->context);

	results = cmd_results_new(CMD_SUCCESS, NULL);

cleanup:
	free_argv(argc, argv);
	return results;
}