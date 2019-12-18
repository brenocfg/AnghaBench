#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sway_workspace {char* representation; TYPE_3__* floating; int /*<<< orphan*/  layout; int /*<<< orphan*/  urgent; TYPE_2__* output; int /*<<< orphan*/ * name; } ;
struct sway_container {int /*<<< orphan*/  node; } ;
typedef  int /*<<< orphan*/  json_object ;
struct TYPE_6__ {int length; struct sway_container** items; } ;
struct TYPE_5__ {TYPE_1__* wlr_output; } ;
struct TYPE_4__ {char* name; } ;

/* Variables and functions */
 int atoi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipc_json_describe_node_recursive (int /*<<< orphan*/ *) ; 
 char* ipc_json_layout_description (int /*<<< orphan*/ ) ; 
 char* ipc_json_orientation_description (int /*<<< orphan*/ ) ; 
 scalar_t__ isdigit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_object_array_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * json_object_new_array () ; 
 int /*<<< orphan*/ * json_object_new_boolean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * json_object_new_int (int) ; 
 int /*<<< orphan*/ * json_object_new_string (char*) ; 
 int /*<<< orphan*/  json_object_object_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipc_json_describe_workspace(struct sway_workspace *workspace,
		json_object *object) {
	int num = isdigit(workspace->name[0]) ? atoi(workspace->name) : -1;

	json_object_object_add(object, "num", json_object_new_int(num));
	json_object_object_add(object, "output", workspace->output ?
			json_object_new_string(workspace->output->wlr_output->name) : NULL);
	json_object_object_add(object, "type", json_object_new_string("workspace"));
	json_object_object_add(object, "urgent",
			json_object_new_boolean(workspace->urgent));
	json_object_object_add(object, "representation", workspace->representation ?
			json_object_new_string(workspace->representation) : NULL);

	json_object_object_add(object, "layout",
			json_object_new_string(
				ipc_json_layout_description(workspace->layout)));
	json_object_object_add(object, "orientation",
			json_object_new_string(
				ipc_json_orientation_description(workspace->layout)));

	// Floating
	json_object *floating_array = json_object_new_array();
	for (int i = 0; i < workspace->floating->length; ++i) {
		struct sway_container *floater = workspace->floating->items[i];
		json_object_array_add(floating_array,
				ipc_json_describe_node_recursive(&floater->node));
	}
	json_object_object_add(object, "floating_nodes", floating_array);
}