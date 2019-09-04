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
struct sway_node {size_t id; } ;
struct sway_output {struct sway_node node; } ;
struct focus_inactive_data {int /*<<< orphan*/ * node; int /*<<< orphan*/ * object; } ;
typedef  int /*<<< orphan*/  json_object ;
struct TYPE_2__ {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  json_object_array_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_object_array_get_idx (int /*<<< orphan*/ *,int) ; 
 int json_object_array_length (int /*<<< orphan*/ *) ; 
 scalar_t__ json_object_get_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_object_new_int (size_t) ; 
 struct sway_output* node_get_output (struct sway_node*) ; 
 int /*<<< orphan*/ * node_get_parent (struct sway_node*) ; 
 TYPE_1__* root ; 

__attribute__((used)) static void focus_inactive_children_iterator(struct sway_node *node,
		void *_data) {
	struct focus_inactive_data *data = _data;
	json_object *focus = data->object;
	if (data->node == &root->node) {
		struct sway_output *output = node_get_output(node);
		if (output == NULL) {
			return;
		}
		size_t id = output->node.id;
		int len = json_object_array_length(focus);
		for (int i = 0; i < len; ++i) {
			if ((size_t) json_object_get_int(json_object_array_get_idx(focus, i)) == id) {
				return;
			}
		}
		node = &output->node;
	} else if (node_get_parent(node) != data->node) {
		return;
	}
	json_object_array_add(focus, json_object_new_int(node->id));
}