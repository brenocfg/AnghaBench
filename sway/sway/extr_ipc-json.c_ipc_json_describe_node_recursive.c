#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct sway_node {int type; TYPE_7__* sway_container; TYPE_5__* sway_workspace; TYPE_3__* sway_output; } ;
struct sway_workspace {struct sway_node node; } ;
struct sway_output {struct sway_node node; } ;
struct sway_container {struct sway_node node; } ;
typedef  int /*<<< orphan*/  json_object ;
struct TYPE_16__ {TYPE_1__* outputs; } ;
struct TYPE_15__ {TYPE_6__* children; } ;
struct TYPE_14__ {int length; struct sway_container** items; } ;
struct TYPE_13__ {TYPE_4__* tiling; } ;
struct TYPE_12__ {int length; struct sway_container** items; } ;
struct TYPE_11__ {TYPE_2__* workspaces; } ;
struct TYPE_10__ {int length; struct sway_workspace** items; } ;
struct TYPE_9__ {int length; struct sway_output** items; } ;

/* Variables and functions */
#define  N_CONTAINER 131 
#define  N_OUTPUT 130 
#define  N_ROOT 129 
#define  N_WORKSPACE 128 
 int /*<<< orphan*/ * ipc_json_describe_node (struct sway_node*) ; 
 int /*<<< orphan*/ * ipc_json_describe_scratchpad_output () ; 
 int /*<<< orphan*/  json_object_array_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_object_new_array () ; 
 int /*<<< orphan*/  json_object_object_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 TYPE_8__* root ; 

json_object *ipc_json_describe_node_recursive(struct sway_node *node) {
	json_object *object = ipc_json_describe_node(node);
	int i;

	json_object *children = json_object_new_array();
	switch (node->type) {
	case N_ROOT:
		json_object_array_add(children,
				ipc_json_describe_scratchpad_output());
		for (i = 0; i < root->outputs->length; ++i) {
			struct sway_output *output = root->outputs->items[i];
			json_object_array_add(children,
					ipc_json_describe_node_recursive(&output->node));
		}
		break;
	case N_OUTPUT:
		for (i = 0; i < node->sway_output->workspaces->length; ++i) {
			struct sway_workspace *ws = node->sway_output->workspaces->items[i];
			json_object_array_add(children,
					ipc_json_describe_node_recursive(&ws->node));
		}
		break;
	case N_WORKSPACE:
		for (i = 0; i < node->sway_workspace->tiling->length; ++i) {
			struct sway_container *con = node->sway_workspace->tiling->items[i];
			json_object_array_add(children,
					ipc_json_describe_node_recursive(&con->node));
		}
		break;
	case N_CONTAINER:
		if (node->sway_container->children) {
			for (i = 0; i < node->sway_container->children->length; ++i) {
				struct sway_container *child =
					node->sway_container->children->items[i];
				json_object_array_add(children,
						ipc_json_describe_node_recursive(&child->node));
			}
		}
		break;
	}
	json_object_object_add(object, "nodes", children);

	return object;
}