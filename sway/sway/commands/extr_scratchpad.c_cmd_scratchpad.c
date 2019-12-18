#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sway_container {int /*<<< orphan*/  scratchpad; struct sway_container* parent; } ;
struct cmd_results {int dummy; } ;
struct TYPE_8__ {struct sway_container* container; scalar_t__ using_criteria; } ;
struct TYPE_10__ {TYPE_3__ handler_context; } ;
struct TYPE_9__ {TYPE_2__* scratchpad; TYPE_1__* outputs; } ;
struct TYPE_7__ {int /*<<< orphan*/  length; } ;
struct TYPE_6__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_EQUAL_TO ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*) ; 
 TYPE_5__* config ; 
 scalar_t__ container_is_floating_or_child (struct sway_container*) ; 
 TYPE_4__* root ; 
 int /*<<< orphan*/  scratchpad_toggle_auto () ; 
 int /*<<< orphan*/  scratchpad_toggle_container (struct sway_container*) ; 
 scalar_t__ strcmp (char*,char*) ; 

struct cmd_results *cmd_scratchpad(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "scratchpad", EXPECTED_EQUAL_TO, 1))) {
		return error;
	}
	if (strcmp(argv[0], "show") != 0) {
		return cmd_results_new(CMD_INVALID, "Expected 'scratchpad show'");
	}
	if (!root->outputs->length) {
		return cmd_results_new(CMD_INVALID,
				"Can't run this command while there's no outputs connected.");
	}
	if (!root->scratchpad->length) {
		return cmd_results_new(CMD_INVALID, "Scratchpad is empty");
	}

	if (config->handler_context.using_criteria) {
		struct sway_container *con = config->handler_context.container;

		// If the container is in a floating split container,
		// operate on the split container instead of the child.
		if (container_is_floating_or_child(con)) {
			while (con->parent) {
				con = con->parent;
			}
		}

		// If using criteria, this command is executed for every container which
		// matches the criteria. If this container isn't in the scratchpad,
		// we'll just silently return a success.
		if (!con->scratchpad) {
			return cmd_results_new(CMD_SUCCESS, NULL);
		}
		scratchpad_toggle_container(con);
	} else {
		scratchpad_toggle_auto();
	}

	return cmd_results_new(CMD_SUCCESS, NULL);
}