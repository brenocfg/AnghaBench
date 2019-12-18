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
struct bar_binding {int release; int /*<<< orphan*/  command; int /*<<< orphan*/  button; } ;
typedef  int /*<<< orphan*/  list_t ;
struct TYPE_4__ {TYPE_1__* current_bar; } ;
struct TYPE_3__ {int /*<<< orphan*/ * bindings; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_FAILURE ; 
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  EXPECTED_AT_LEAST ; 
 struct cmd_results* binding_add (struct bar_binding*,int /*<<< orphan*/ *) ; 
 struct cmd_results* binding_remove (struct bar_binding*,int /*<<< orphan*/ *) ; 
 struct bar_binding* calloc (int,int) ; 
 struct cmd_results* checkarg (int,char const*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* config ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_bar_binding (struct bar_binding*) ; 
 int /*<<< orphan*/  get_mouse_bindcode (char*,char**) ; 
 int /*<<< orphan*/  get_mouse_bindsym (char*,char**) ; 
 int /*<<< orphan*/  join_args (char**,int) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static struct cmd_results *bar_cmd_bind(int argc, char **argv, bool code,
		bool unbind) {
	int minargs = 2;
	const char *command;
	if (unbind) {
		minargs--;
		command = code ? "bar unbindcode" : "bar unbindsym";
	} else {
		command = code ? "bar bindcode" : "bar bindsym";
	}

	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, command, EXPECTED_AT_LEAST, minargs))) {
		return error;
	}

	struct bar_binding *binding = calloc(1, sizeof(struct bar_binding));
	if (!binding) {
		return cmd_results_new(CMD_FAILURE, "Unable to allocate bar binding");
	}

	binding->release = false;
	if (strcmp("--release", argv[0]) == 0) {
		binding->release = true;
		argv++;
		argc--;
	}

	char *message = NULL;
	if (code) {
		binding->button = get_mouse_bindcode(argv[0], &message);
	} else {
		binding->button = get_mouse_bindsym(argv[0], &message);
	}
	if (message) {
		free_bar_binding(binding);
		error = cmd_results_new(CMD_INVALID, message);
		free(message);
		return error;
	} else if (!binding->button) {
		free_bar_binding(binding);
		return cmd_results_new(CMD_INVALID, "Unknown button %s", argv[0]);
	}
	list_t *bindings = config->current_bar->bindings;
	if (unbind) {
		return binding_remove(binding, bindings);
	}

	binding->command = join_args(argv + 1, argc - 1);
	return binding_add(binding, bindings);
}