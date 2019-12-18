#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cmd_results {int dummy; } ;
struct cmd_handler {struct cmd_results* (* handle ) (int,char**) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_BLOCK ; 
 int /*<<< orphan*/  CMD_BLOCK_END ; 
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  SWAY_INFO ; 
 char* calloc (int,scalar_t__) ; 
 struct cmd_results* cmd_bindcode (int,char**) ; 
 struct cmd_results* cmd_bindswitch (int,char**) ; 
 struct cmd_results* cmd_bindsym (int,char**) ; 
 struct cmd_results* cmd_exec (int,char**) ; 
 struct cmd_results* cmd_exec_always (int,char**) ; 
 struct cmd_results* cmd_for_window (int,char**) ; 
 struct cmd_results* cmd_mode (int,char**) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char const*,...) ; 
 struct cmd_results* cmd_set (int,char**) ; 
 char* do_var_replacement (char*) ; 
 struct cmd_handler* find_core_handler (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_argv (int,char**) ; 
 char* join_args (char**,int) ; 
 char** split_args (char*,int*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strip_quotes (char*) ; 
 scalar_t__ strlen (char*) ; 
 struct cmd_results* stub1 (int,char**) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  unescape_string (char*) ; 

struct cmd_results *config_command(char *exec, char **new_block) {
	struct cmd_results *results = NULL;
	int argc;
	char **argv = split_args(exec, &argc);

	// Check for empty lines
	if (!argc) {
		results = cmd_results_new(CMD_SUCCESS, NULL);
		goto cleanup;
	}

	// Check for the start of a block
	if (argc > 1 && strcmp(argv[argc - 1], "{") == 0) {
		*new_block = join_args(argv, argc - 1);
		results = cmd_results_new(CMD_BLOCK, NULL);
		goto cleanup;
	}

	// Check for the end of a block
	if (strcmp(argv[argc - 1], "}") == 0) {
		results = cmd_results_new(CMD_BLOCK_END, NULL);
		goto cleanup;
	}

	// Make sure the command is not stored in a variable
	if (*argv[0] == '$') {
		argv[0] = do_var_replacement(argv[0]);
		char *temp = join_args(argv, argc);
		free_argv(argc, argv);
		argv = split_args(temp, &argc);
		free(temp);
		if (!argc) {
			results = cmd_results_new(CMD_SUCCESS, NULL);
			goto cleanup;
		}
	}

	// Determine the command handler
	sway_log(SWAY_INFO, "Config command: %s", exec);
	struct cmd_handler *handler = find_core_handler(argv[0]);
	if (!handler || !handler->handle) {
		const char *error = handler
			? "Command '%s' is shimmed, but unimplemented"
			: "Unknown/invalid command '%s'";
		results = cmd_results_new(CMD_INVALID, error, argv[0]);
		goto cleanup;
	}

	// Do variable replacement
	if (handler->handle == cmd_set && argc > 1 && *argv[1] == '$') {
		// Escape the variable name so it does not get replaced by one shorter
		char *temp = calloc(1, strlen(argv[1]) + 2);
		temp[0] = '$';
		strcpy(&temp[1], argv[1]);
		free(argv[1]);
		argv[1] = temp;
	}
	char *command = do_var_replacement(join_args(argv, argc));
	sway_log(SWAY_INFO, "After replacement: %s", command);
	free_argv(argc, argv);
	argv = split_args(command, &argc);
	free(command);

	// Strip quotes and unescape the string
	for (int i = handler->handle == cmd_set ? 2 : 1; i < argc; ++i) {
		if (handler->handle != cmd_exec && handler->handle != cmd_exec_always
				&& handler->handle != cmd_mode
				&& handler->handle != cmd_bindsym
				&& handler->handle != cmd_bindcode
				&& handler->handle != cmd_bindswitch
				&& handler->handle != cmd_set
				&& handler->handle != cmd_for_window
				&& (*argv[i] == '\"' || *argv[i] == '\'')) {
			strip_quotes(argv[i]);
		}
		unescape_string(argv[i]);
	}

	// Run command
	results = handler->handle(argc - 1, argv + 1);

cleanup:
	free_argv(argc, argv);
	return results;
}