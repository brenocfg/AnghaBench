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
struct sway_seat_node {int /*<<< orphan*/  link; } ;
struct sway_seat {int /*<<< orphan*/  focus_stack; } ;
struct sway_node {int dummy; } ;

/* Variables and functions */
 struct sway_node* node_get_parent (struct sway_node*) ; 
 int /*<<< orphan*/  node_set_dirty (struct sway_node*) ; 
 struct sway_seat_node* seat_node_from_node (struct sway_seat*,struct sway_node*) ; 
 int /*<<< orphan*/  wl_list_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_list_remove (int /*<<< orphan*/ *) ; 

void seat_set_raw_focus(struct sway_seat *seat, struct sway_node *node) {
	struct sway_seat_node *seat_node = seat_node_from_node(seat, node);
	wl_list_remove(&seat_node->link);
	wl_list_insert(&seat->focus_stack, &seat_node->link);
	node_set_dirty(node);

	// If focusing a scratchpad container that is fullscreen global, parent
	// will be NULL
	struct sway_node *parent = node_get_parent(node);
	if (parent) {
		node_set_dirty(parent);
	}
}