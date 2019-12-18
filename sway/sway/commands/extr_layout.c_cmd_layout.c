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
struct sway_workspace {int layout; int prev_split_layout; int /*<<< orphan*/  output; } ;
struct sway_container {int layout; int prev_split_layout; TYPE_3__* workspace; struct sway_container* parent; } ;
struct cmd_results {int dummy; } ;
typedef  enum sway_container_layout { ____Placeholder_sway_container_layout } sway_container_layout ;
struct TYPE_7__ {struct sway_workspace* workspace; struct sway_container* container; } ;
struct TYPE_10__ {TYPE_2__ handler_context; } ;
struct TYPE_9__ {scalar_t__ fullscreen_global; TYPE_1__* outputs; } ;
struct TYPE_8__ {int /*<<< orphan*/  output; } ;
struct TYPE_6__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_FAILURE ; 
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_AT_LEAST ; 
 int L_NONE ; 
 int L_STACKED ; 
 int L_TABBED ; 
 int /*<<< orphan*/  arrange_root () ; 
 int /*<<< orphan*/  arrange_workspace (struct sway_workspace*) ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*) ; 
 TYPE_5__* config ; 
 scalar_t__ container_is_floating (struct sway_container*) ; 
 int /*<<< orphan*/  container_update_representation (struct sway_container*) ; 
 char* expected_syntax ; 
 int get_layout (int,char**,int,int,int /*<<< orphan*/ ) ; 
 TYPE_4__* root ; 
 int /*<<< orphan*/  workspace_update_representation (struct sway_workspace*) ; 

struct cmd_results *cmd_layout(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "layout", EXPECTED_AT_LEAST, 1))) {
		return error;
	}
	if (!root->outputs->length) {
		return cmd_results_new(CMD_INVALID,
				"Can't run this command while there's no outputs connected.");
	}
	struct sway_container *container = config->handler_context.container;
	struct sway_workspace *workspace = config->handler_context.workspace;

	if (container && container_is_floating(container)) {
		return cmd_results_new(CMD_FAILURE,
				"Unable to change layout of floating windows");
	}

	// Operate on parent container, like i3.
	if (container) {
		container = container->parent;
	}

	// We could be working with a container OR a workspace. These are different
	// structures, so we set up pointers to they layouts so we can refer them in
	// an abstract way.
	enum sway_container_layout new_layout = L_NONE;
	enum sway_container_layout old_layout = L_NONE;
	if (container) {
		old_layout = container->layout;
		new_layout = get_layout(argc, argv,
				container->layout, container->prev_split_layout,
				container->workspace->output);
	} else {
		old_layout = workspace->layout;
		new_layout = get_layout(argc, argv,
				workspace->layout, workspace->prev_split_layout,
				workspace->output);
	}
	if (new_layout == L_NONE) {
		return cmd_results_new(CMD_INVALID, expected_syntax);
	}
	if (new_layout != old_layout) {
		if (container) {
			if (old_layout != L_TABBED && old_layout != L_STACKED) {
				container->prev_split_layout = old_layout;
			}
			container->layout = new_layout;
			container_update_representation(container);
		} else {
			if (old_layout != L_TABBED && old_layout != L_STACKED) {
				workspace->prev_split_layout = old_layout;
			}
			workspace->layout = new_layout;
			workspace_update_representation(workspace);
		}
		if (root->fullscreen_global) {
			arrange_root();
		} else {
			arrange_workspace(workspace);
		}
	}

	return cmd_results_new(CMD_SUCCESS, NULL);
}