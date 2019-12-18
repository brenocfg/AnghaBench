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
struct sway_binding {char* command; int order; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 char* argsep (char**,char*,int /*<<< orphan*/ *) ; 
 char* do_var_replacement (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ isdigit (char) ; 
 char* malloc (size_t) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strip_quotes (char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ workspace_by_name (char*) ; 
 scalar_t__ workspace_by_number (char*) ; 
 int /*<<< orphan*/  workspace_valid_on_output (char const*,char*) ; 

__attribute__((used)) static void workspace_name_from_binding(const struct sway_binding * binding,
		const char* output_name, int *min_order, char **earliest_name) {
	char *cmdlist = strdup(binding->command);
	char *dup = cmdlist;
	char *name = NULL;

	// workspace n
	char *cmd = argsep(&cmdlist, " ", NULL);
	if (cmdlist) {
		name = argsep(&cmdlist, ",;", NULL);
	}

	// TODO: support "move container to workspace" bindings as well

	if (strcmp("workspace", cmd) == 0 && name) {
		char *_target = strdup(name);
		_target = do_var_replacement(_target);
		strip_quotes(_target);
		sway_log(SWAY_DEBUG, "Got valid workspace command for target: '%s'",
				_target);

		// Make sure that the command references an actual workspace
		// not a command about workspaces
		if (strcmp(_target, "next") == 0 ||
				strcmp(_target, "prev") == 0 ||
				strncmp(_target, "next_on_output",
					strlen("next_on_output")) == 0 ||
				strncmp(_target, "prev_on_output",
					strlen("next_on_output")) == 0 ||
				strcmp(_target, "number") == 0 ||
				strcmp(_target, "back_and_forth") == 0 ||
				strcmp(_target, "current") == 0) {
			free(_target);
			free(dup);
			return;
		}

		// If the command is workspace number <name>, isolate the name
		if (strncmp(_target, "number ", strlen("number ")) == 0) {
			size_t length = strlen(_target) - strlen("number ") + 1;
			char *temp = malloc(length);
			strncpy(temp, _target + strlen("number "), length - 1);
			temp[length - 1] = '\0';
			free(_target);
			_target = temp;
			sway_log(SWAY_DEBUG, "Isolated name from workspace number: '%s'", _target);

			// Make sure the workspace number doesn't already exist
			if (isdigit(_target[0]) && workspace_by_number(_target)) {
				free(_target);
				free(dup);
				return;
			}
		}

		// Make sure that the workspace doesn't already exist
		if (workspace_by_name(_target)) {
			free(_target);
			free(dup);
			return;
		}

		// make sure that the workspace can appear on the given
		// output
		if (!workspace_valid_on_output(output_name, _target)) {
			free(_target);
			free(dup);
			return;
		}

		if (binding->order < *min_order) {
			*min_order = binding->order;
			free(*earliest_name);
			*earliest_name = _target;
			sway_log(SWAY_DEBUG, "Workspace: Found free name %s", _target);
		} else {
			free(_target);
		}
	}
	free(dup);
}