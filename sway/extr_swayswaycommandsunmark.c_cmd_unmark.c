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
struct sway_container {int dummy; } ;
struct cmd_results {int dummy; } ;
struct TYPE_3__ {struct sway_container* container; scalar_t__ using_criteria; } ;
struct TYPE_4__ {TYPE_1__ handler_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SUCCESS ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* config ; 
 int /*<<< orphan*/  container_clear_marks (struct sway_container*) ; 
 int /*<<< orphan*/  container_find_and_unmark (char*) ; 
 scalar_t__ container_has_mark (struct sway_container*,char*) ; 
 int /*<<< orphan*/  container_update_marks_textures (struct sway_container*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* join_args (char**,int) ; 
 int /*<<< orphan*/  remove_all_marks_iterator ; 
 int /*<<< orphan*/  root_for_each_container (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct cmd_results *cmd_unmark(int argc, char **argv) {
	// Determine the container
	struct sway_container *con = NULL;
	if (config->handler_context.using_criteria) {
		con = config->handler_context.container;
	}

	// Determine the mark
	char *mark = NULL;
	if (argc > 0) {
		mark = join_args(argv, argc);
	}

	if (con && mark) {
		// Remove the mark from the given container
		if (container_has_mark(con, mark)) {
			container_find_and_unmark(mark);
		}
	} else if (con && !mark) {
		// Clear all marks from the given container
		container_clear_marks(con);
		container_update_marks_textures(con);
	} else if (!con && mark) {
		// Remove mark from whichever container has it
		container_find_and_unmark(mark);
	} else {
		// Remove all marks from all containers
		root_for_each_container(remove_all_marks_iterator, NULL);
	}
	free(mark);

	return cmd_results_new(CMD_SUCCESS, NULL);
}