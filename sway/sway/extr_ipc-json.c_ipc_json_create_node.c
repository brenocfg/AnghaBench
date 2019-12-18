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
struct wlr_box {int dummy; } ;
typedef  int /*<<< orphan*/  json_object ;

/* Variables and functions */
 int /*<<< orphan*/  B_NONE ; 
 int /*<<< orphan*/  L_HORIZ ; 
 char* ipc_json_border_description (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ipc_json_create_empty_rect () ; 
 int /*<<< orphan*/ * ipc_json_create_rect (struct wlr_box*) ; 
 char* ipc_json_layout_description (int /*<<< orphan*/ ) ; 
 char* ipc_json_orientation_description (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * json_object_new_array () ; 
 int /*<<< orphan*/ * json_object_new_boolean (int) ; 
 int /*<<< orphan*/ * json_object_new_int (int) ; 
 int /*<<< orphan*/ * json_object_new_object () ; 
 int /*<<< orphan*/ * json_object_new_string (char*) ; 
 int /*<<< orphan*/  json_object_object_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static json_object *ipc_json_create_node(int id, char *name,
		bool focused, json_object *focus, struct wlr_box *box) {
	json_object *object = json_object_new_object();

	json_object_object_add(object, "id", json_object_new_int(id));
	json_object_object_add(object, "name",
			name ? json_object_new_string(name) : NULL);
	json_object_object_add(object, "rect", ipc_json_create_rect(box));
	json_object_object_add(object, "focused", json_object_new_boolean(focused));
	json_object_object_add(object, "focus", focus);

	// set default values to be compatible with i3
	json_object_object_add(object, "border",
			json_object_new_string(
				ipc_json_border_description(B_NONE)));
	json_object_object_add(object, "current_border_width",
			json_object_new_int(0));
	json_object_object_add(object, "layout",
			json_object_new_string(
				ipc_json_layout_description(L_HORIZ)));
	json_object_object_add(object, "orientation",
			json_object_new_string(
				ipc_json_orientation_description(L_HORIZ)));
	json_object_object_add(object, "percent", NULL);
	json_object_object_add(object, "window_rect", ipc_json_create_empty_rect());
	json_object_object_add(object, "deco_rect", ipc_json_create_empty_rect());
	json_object_object_add(object, "geometry", ipc_json_create_empty_rect());
	json_object_object_add(object, "window", NULL);
	json_object_object_add(object, "urgent", json_object_new_boolean(false));
	json_object_object_add(object, "floating_nodes", json_object_new_array());
	json_object_object_add(object, "sticky", json_object_new_boolean(false));

	return object;
}