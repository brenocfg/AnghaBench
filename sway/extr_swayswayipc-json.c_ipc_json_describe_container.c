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
struct wlr_box {double width; double height; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct sway_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  border_thickness; int /*<<< orphan*/  border; } ;
struct sway_container {char* title; int is_sticky; scalar_t__ view; TYPE_1__ current; scalar_t__ height; scalar_t__ width; int /*<<< orphan*/  node; int /*<<< orphan*/  fullscreen_mode; int /*<<< orphan*/  layout; } ;
typedef  int /*<<< orphan*/  json_object ;

/* Variables and functions */
 int container_has_urgent_child (struct sway_container*) ; 
 scalar_t__ container_is_floating (struct sway_container*) ; 
 int /*<<< orphan*/  get_deco_rect (struct sway_container*,struct wlr_box*) ; 
 char* ipc_json_border_description (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ipc_json_create_rect (struct wlr_box*) ; 
 int /*<<< orphan*/  ipc_json_describe_view (struct sway_container*,int /*<<< orphan*/ *) ; 
 char* ipc_json_layout_description (int /*<<< orphan*/ ) ; 
 char* ipc_json_orientation_description (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * json_object_new_array () ; 
 int /*<<< orphan*/ * json_object_new_boolean (int) ; 
 int /*<<< orphan*/ * json_object_new_double (double) ; 
 int /*<<< orphan*/ * json_object_new_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * json_object_new_string (char*) ; 
 int /*<<< orphan*/  json_object_object_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  node_get_box (struct sway_node*,struct wlr_box*) ; 
 struct sway_node* node_get_parent (int /*<<< orphan*/ *) ; 
 int view_is_urgent (scalar_t__) ; 

__attribute__((used)) static void ipc_json_describe_container(struct sway_container *c, json_object *object) {
	json_object_object_add(object, "name",
			c->title ? json_object_new_string(c->title) : NULL);
	json_object_object_add(object, "type",
			json_object_new_string(container_is_floating(c) ? "floating_con" : "con"));

	json_object_object_add(object, "layout",
			json_object_new_string(
				ipc_json_layout_description(c->layout)));

	json_object_object_add(object, "orientation",
			json_object_new_string(
				ipc_json_orientation_description(c->layout)));

	bool urgent = c->view ?
		view_is_urgent(c->view) : container_has_urgent_child(c);
	json_object_object_add(object, "urgent", json_object_new_boolean(urgent));
	json_object_object_add(object, "sticky", json_object_new_boolean(c->is_sticky));

	json_object_object_add(object, "fullscreen_mode",
			json_object_new_int(c->fullscreen_mode));

	struct sway_node *parent = node_get_parent(&c->node);
	struct wlr_box parent_box = {0, 0, 0, 0};

	if (parent != NULL) {
		node_get_box(parent, &parent_box);
	}

	if (parent_box.width != 0 && parent_box.height != 0) {
		double percent = ((double)c->width / parent_box.width)
				* ((double)c->height / parent_box.height);
		json_object_object_add(object, "percent", json_object_new_double(percent));
	}

	json_object_object_add(object, "border",
			json_object_new_string(
				ipc_json_border_description(c->current.border)));
	json_object_object_add(object, "current_border_width",
			json_object_new_int(c->current.border_thickness));
	json_object_object_add(object, "floating_nodes", json_object_new_array());

	struct wlr_box deco_box = {0, 0, 0, 0};
	get_deco_rect(c, &deco_box);
	json_object_object_add(object, "deco_rect", ipc_json_create_rect(&deco_box));

	if (c->view) {
		ipc_json_describe_view(c, object);
	}
}