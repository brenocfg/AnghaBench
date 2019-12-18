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
struct sway_container {scalar_t__ view; } ;
struct cmd_results {int dummy; } ;
struct TYPE_3__ {struct sway_container* container; } ;
struct TYPE_4__ {TYPE_1__ handler_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_AT_LEAST ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* config ; 
 int /*<<< orphan*/  container_add_mark (struct sway_container*,char*) ; 
 int /*<<< orphan*/  container_clear_marks (struct sway_container*) ; 
 int /*<<< orphan*/  container_find_and_unmark (char*) ; 
 int container_has_mark (struct sway_container*,char*) ; 
 int /*<<< orphan*/  container_update_marks_textures (struct sway_container*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* join_args (char**,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  view_execute_criteria (scalar_t__) ; 

struct cmd_results *cmd_mark(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "mark", EXPECTED_AT_LEAST, 1))) {
		return error;
	}
	struct sway_container *container = config->handler_context.container;
	if (!container) {
		return cmd_results_new(CMD_INVALID, "Only containers can have marks");
	}

	bool add = false, toggle = false;
	while (argc > 0 && strncmp(*argv, "--", 2) == 0) {
		if (strcmp(*argv, "--add") == 0) {
			add = true;
		} else if (strcmp(*argv, "--replace") == 0) {
			add = false;
		} else if (strcmp(*argv, "--toggle") == 0) {
			toggle = true;
		} else {
			return cmd_results_new(CMD_INVALID,
					"Unrecognized argument '%s'", *argv);
		}
		++argv;
		--argc;
	}

	if (!argc) {
		return cmd_results_new(CMD_INVALID,
				"Expected '[--add|--replace] [--toggle] <identifier>'");
	}

	char *mark = join_args(argv, argc);
	bool had_mark = container_has_mark(container, mark);

	if (!add) {
		// Replacing
		container_clear_marks(container);
	}

	container_find_and_unmark(mark);

	if (!toggle || !had_mark) {
		container_add_mark(container, mark);
	}

	free(mark);
	container_update_marks_textures(container);
	if (container->view) {
		view_execute_criteria(container->view);
	}

	return cmd_results_new(CMD_SUCCESS, NULL);
}