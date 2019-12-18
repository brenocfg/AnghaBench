#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char xcb_window_t ;
struct sway_node {int dummy; } ;
struct sway_container {int /*<<< orphan*/  node; } ;
struct cmd_results {int dummy; } ;
struct TYPE_6__ {struct sway_container* container; } ;
struct TYPE_8__ {TYPE_2__ handler_context; } ;
struct TYPE_7__ {scalar_t__ fullscreen_global; TYPE_1__* outputs; } ;
struct TYPE_5__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_FAILURE ; 
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_AT_LEAST ; 
 int /*<<< orphan*/  arrange_node (struct sway_node*) ; 
 int /*<<< orphan*/  arrange_root () ; 
 size_t atoi (char*) ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_4__* config ; 
 scalar_t__ container_has_ancestor (struct sway_container*,struct sway_container*) ; 
 int /*<<< orphan*/  container_swap (struct sway_container*,struct sway_container*) ; 
 char* expected_syntax ; 
 int /*<<< orphan*/  free (char*) ; 
 char* join_args (char**,int) ; 
 struct sway_node* node_get_parent (int /*<<< orphan*/ *) ; 
 TYPE_3__* root ; 
 struct sway_container* root_find_container (int /*<<< orphan*/ ,...) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 char strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_con_id ; 
 int /*<<< orphan*/  test_id ; 
 int /*<<< orphan*/  test_mark ; 

struct cmd_results *cmd_swap(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "swap", EXPECTED_AT_LEAST, 4))) {
		return error;
	}
	if (!root->outputs->length) {
		return cmd_results_new(CMD_INVALID,
				"Can't run this command while there's no outputs connected.");
	}

	if (strcasecmp(argv[0], "container") || strcasecmp(argv[1], "with")) {
		return cmd_results_new(CMD_INVALID, expected_syntax);
	}

	struct sway_container *current = config->handler_context.container;
	struct sway_container *other = NULL;

	char *value = join_args(argv + 3, argc - 3);
	if (strcasecmp(argv[2], "id") == 0) {
#if HAVE_XWAYLAND
		xcb_window_t id = strtol(value, NULL, 0);
		other = root_find_container(test_id, &id);
#endif
	} else if (strcasecmp(argv[2], "con_id") == 0) {
		size_t con_id = atoi(value);
		other = root_find_container(test_con_id, &con_id);
	} else if (strcasecmp(argv[2], "mark") == 0) {
		other = root_find_container(test_mark, value);
	} else {
		free(value);
		return cmd_results_new(CMD_INVALID, expected_syntax);
	}

	if (!other) {
		error = cmd_results_new(CMD_FAILURE,
				"Failed to find %s '%s'", argv[2], value);
	} else if (!current) {
		error = cmd_results_new(CMD_FAILURE,
				"Can only swap with containers and views");
	} else if (container_has_ancestor(current, other)
			|| container_has_ancestor(other, current)) {
		error = cmd_results_new(CMD_FAILURE,
				"Cannot swap ancestor and descendant");
	}

	free(value);

	if (error) {
		return error;
	}

	container_swap(current, other);

	if (root->fullscreen_global) {
		arrange_root();
	} else {
		struct sway_node *current_parent = node_get_parent(&current->node);
		struct sway_node *other_parent = node_get_parent(&other->node);
		if (current_parent) {
			arrange_node(current_parent);
		}
		if (other_parent && current_parent != other_parent) {
			arrange_node(other_parent);
		}
	}

	return cmd_results_new(CMD_SUCCESS, NULL);
}