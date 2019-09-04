#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wlr_box {size_t y; size_t height; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct sway_seat {int dummy; } ;
struct sway_node {int type; int /*<<< orphan*/  sway_workspace; int /*<<< orphan*/  sway_container; int /*<<< orphan*/  sway_output; scalar_t__ id; } ;
struct focus_inactive_data {int /*<<< orphan*/ * object; struct sway_node* node; } ;
typedef  int /*<<< orphan*/  json_object ;
struct TYPE_2__ {size_t length; } ;

/* Variables and functions */
 scalar_t__ L_STACKED ; 
#define  N_CONTAINER 131 
#define  N_OUTPUT 130 
#define  N_ROOT 129 
#define  N_WORKSPACE 128 
 TYPE_1__* container_get_siblings (int /*<<< orphan*/ ) ; 
 scalar_t__ container_parent_layout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  focus_inactive_children_iterator ; 
 int /*<<< orphan*/  get_deco_rect (int /*<<< orphan*/ ,struct wlr_box*) ; 
 struct sway_seat* input_manager_get_default_seat () ; 
 int /*<<< orphan*/ * ipc_json_create_node (int,char*,int,int /*<<< orphan*/ *,struct wlr_box*) ; 
 int /*<<< orphan*/  ipc_json_describe_container (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipc_json_describe_output (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipc_json_describe_root (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipc_json_describe_workspace (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_object_new_array () ; 
 int /*<<< orphan*/  node_get_box (struct sway_node*,struct wlr_box*) ; 
 char* node_get_name (struct sway_node*) ; 
 int /*<<< orphan*/  root ; 
 int /*<<< orphan*/  seat_for_each_node (struct sway_seat*,int /*<<< orphan*/ ,struct focus_inactive_data*) ; 
 struct sway_node* seat_get_focus (struct sway_seat*) ; 

json_object *ipc_json_describe_node(struct sway_node *node) {
	struct sway_seat *seat = input_manager_get_default_seat();
	bool focused = seat_get_focus(seat) == node;
	char *name = node_get_name(node);

	struct wlr_box box;
	node_get_box(node, &box);
	if (node->type == N_CONTAINER) {
		struct wlr_box deco_rect = {0, 0, 0, 0};
		get_deco_rect(node->sway_container, &deco_rect);
		size_t count = 1;
		if (container_parent_layout(node->sway_container) == L_STACKED) {
			count = container_get_siblings(node->sway_container)->length;
		}
		box.y += deco_rect.height * count;
		box.height -= deco_rect.height * count;
	}

	json_object *focus = json_object_new_array();
	struct focus_inactive_data data = {
		.node = node,
		.object = focus,
	};
	seat_for_each_node(seat, focus_inactive_children_iterator, &data);

	json_object *object = ipc_json_create_node(
				(int)node->id, name, focused, focus, &box);

	switch (node->type) {
	case N_ROOT:
		ipc_json_describe_root(root, object);
		break;
	case N_OUTPUT:
		ipc_json_describe_output(node->sway_output, object);
		break;
	case N_CONTAINER:
		ipc_json_describe_container(node->sway_container, object);
		break;
	case N_WORKSPACE:
		ipc_json_describe_workspace(node->sway_workspace, object);
		break;
	}

	return object;
}