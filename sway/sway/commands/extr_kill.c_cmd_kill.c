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
struct sway_workspace {int dummy; } ;
struct sway_container {int dummy; } ;
struct cmd_results {int dummy; } ;
struct TYPE_6__ {struct sway_workspace* workspace; struct sway_container* container; } ;
struct TYPE_8__ {TYPE_2__ handler_context; } ;
struct TYPE_7__ {TYPE_1__* outputs; } ;
struct TYPE_5__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  close_container_iterator (struct sway_container*,int /*<<< orphan*/ *) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*) ; 
 TYPE_4__* config ; 
 int /*<<< orphan*/  container_for_each_child (struct sway_container*,int /*<<< orphan*/  (*) (struct sway_container*,int /*<<< orphan*/ *),int /*<<< orphan*/ *) ; 
 TYPE_3__* root ; 
 int /*<<< orphan*/  workspace_for_each_container (struct sway_workspace*,int /*<<< orphan*/  (*) (struct sway_container*,int /*<<< orphan*/ *),int /*<<< orphan*/ *) ; 

struct cmd_results *cmd_kill(int argc, char **argv) {
	if (!root->outputs->length) {
		return cmd_results_new(CMD_INVALID,
				"Can't run this command while there's no outputs connected.");
	}
	struct sway_container *con = config->handler_context.container;
	struct sway_workspace *ws = config->handler_context.workspace;

	if (con) {
		close_container_iterator(con, NULL);
		container_for_each_child(con, close_container_iterator, NULL);
	} else {
		workspace_for_each_container(ws, close_container_iterator, NULL);
	}

	return cmd_results_new(CMD_SUCCESS, NULL);
}