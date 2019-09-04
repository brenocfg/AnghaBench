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
struct sway_view {int allow_request_urgent; } ;
struct sway_container {struct sway_view* view; } ;
struct cmd_results {int dummy; } ;
struct TYPE_3__ {struct sway_container* container; } ;
struct TYPE_4__ {TYPE_1__ handler_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_FAILURE ; 
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_EQUAL_TO ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* config ; 
 int /*<<< orphan*/  parse_boolean (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  view_is_urgent (struct sway_view*) ; 
 int /*<<< orphan*/  view_set_urgent (struct sway_view*,int /*<<< orphan*/ ) ; 

struct cmd_results *cmd_urgent(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "urgent", EXPECTED_EQUAL_TO, 1))) {
		return error;
	}
	struct sway_container *container = config->handler_context.container;
	if (!container) {
		return cmd_results_new(CMD_FAILURE, "No current container");
	}
	if (!container->view) {
		return cmd_results_new(CMD_INVALID, "Only views can be urgent");
	}
	struct sway_view *view = container->view;

	if (strcmp(argv[0], "allow") == 0) {
		view->allow_request_urgent = true;
	} else if (strcmp(argv[0], "deny") == 0) {
		view->allow_request_urgent = false;
	} else {
		view_set_urgent(view, parse_boolean(argv[0], view_is_urgent(view)));
	}

	return cmd_results_new(CMD_SUCCESS, NULL);
}