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
struct sway_workspace {int /*<<< orphan*/  node; struct sway_output* output; } ;
struct sway_seat {int dummy; } ;
struct sway_output {TYPE_3__* wlr_output; TYPE_2__* workspaces; } ;
struct sway_node {int dummy; } ;
struct TYPE_5__ {struct sway_seat* seat; } ;
struct TYPE_8__ {TYPE_1__ handler_context; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {scalar_t__ length; } ;

/* Variables and functions */
 TYPE_4__* config ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ipc_event_workspace (int /*<<< orphan*/ *,struct sway_workspace*,char*) ; 
 int /*<<< orphan*/  output_add_workspace (struct sway_output*,struct sway_workspace*) ; 
 struct sway_workspace* output_get_active_workspace (struct sway_output*) ; 
 int /*<<< orphan*/  output_sort_workspaces (struct sway_output*) ; 
 struct sway_node* seat_get_focus_inactive (struct sway_seat*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seat_set_focus (struct sway_seat*,struct sway_node*) ; 
 int /*<<< orphan*/  seat_set_raw_focus (struct sway_seat*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sway_assert (struct sway_workspace*,char*) ; 
 int /*<<< orphan*/  workspace_consider_destroy (struct sway_workspace*) ; 
 struct sway_workspace* workspace_create (struct sway_output*,char*) ; 
 int /*<<< orphan*/  workspace_detach (struct sway_workspace*) ; 
 char* workspace_next_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  workspace_output_raise_priority (struct sway_workspace*,struct sway_output*,struct sway_output*) ; 

__attribute__((used)) static void workspace_move_to_output(struct sway_workspace *workspace,
		struct sway_output *output) {
	if (workspace->output == output) {
		return;
	}
	struct sway_output *old_output = workspace->output;
	workspace_detach(workspace);
	struct sway_workspace *new_output_old_ws =
		output_get_active_workspace(output);
	if (!sway_assert(new_output_old_ws, "Expected output to have a workspace")) {
		return;
	}

	output_add_workspace(output, workspace);

	// If moving the last workspace from the old output, create a new workspace
	// on the old output
	struct sway_seat *seat = config->handler_context.seat;
	if (old_output->workspaces->length == 0) {
		char *ws_name = workspace_next_name(old_output->wlr_output->name);
		struct sway_workspace *ws = workspace_create(old_output, ws_name);
		free(ws_name);
		seat_set_raw_focus(seat, &ws->node);
	}

	workspace_consider_destroy(new_output_old_ws);

	output_sort_workspaces(output);
	struct sway_node *focus = seat_get_focus_inactive(seat, &workspace->node);
	seat_set_focus(seat, focus);
	workspace_output_raise_priority(workspace, old_output, output);
	ipc_event_workspace(NULL, workspace, "move");
}