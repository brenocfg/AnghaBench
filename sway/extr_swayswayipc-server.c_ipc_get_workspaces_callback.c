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
struct sway_workspace {int /*<<< orphan*/  output; int /*<<< orphan*/  node; } ;
struct sway_seat {int dummy; } ;
typedef  int /*<<< orphan*/  json_object ;

/* Variables and functions */
 struct sway_seat* input_manager_get_default_seat () ; 
 int /*<<< orphan*/ * ipc_json_describe_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_object_array_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_object_new_boolean (int) ; 
 int /*<<< orphan*/  json_object_object_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_object_object_del (int /*<<< orphan*/ *,char*) ; 
 struct sway_workspace* output_get_active_workspace (int /*<<< orphan*/ ) ; 
 struct sway_workspace* seat_get_focused_workspace (struct sway_seat*) ; 

__attribute__((used)) static void ipc_get_workspaces_callback(struct sway_workspace *workspace,
		void *data) {
	json_object *workspace_json = ipc_json_describe_node(&workspace->node);
	// override the default focused indicator because
	// it's set differently for the get_workspaces reply
	struct sway_seat *seat = input_manager_get_default_seat();
	struct sway_workspace *focused_ws = seat_get_focused_workspace(seat);
	bool focused = workspace == focused_ws;
	json_object_object_del(workspace_json, "focused");
	json_object_object_add(workspace_json, "focused",
			json_object_new_boolean(focused));
	json_object_array_add((json_object *)data, workspace_json);

	focused_ws = output_get_active_workspace(workspace->output);
	bool visible = workspace == focused_ws;
	json_object_object_add(workspace_json, "visible",
			json_object_new_boolean(visible));
}