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
struct sway_container_state {int focused; int /*<<< orphan*/ * focused_inactive_child; int /*<<< orphan*/  children; int /*<<< orphan*/  content_height; int /*<<< orphan*/  content_width; int /*<<< orphan*/  content_y; int /*<<< orphan*/  content_x; int /*<<< orphan*/  border_bottom; int /*<<< orphan*/  border_right; int /*<<< orphan*/  border_left; int /*<<< orphan*/  border_top; int /*<<< orphan*/  border_thickness; int /*<<< orphan*/  border; int /*<<< orphan*/  workspace; int /*<<< orphan*/  parent; int /*<<< orphan*/  fullscreen_mode; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  layout; } ;
struct sway_transaction_instruction {struct sway_container_state container_state; } ;
struct sway_seat {int dummy; } ;
struct sway_node {int /*<<< orphan*/ * sway_container; } ;
struct sway_container {int /*<<< orphan*/  node; int /*<<< orphan*/  view; int /*<<< orphan*/  children; int /*<<< orphan*/  content_height; int /*<<< orphan*/  content_width; int /*<<< orphan*/  content_y; int /*<<< orphan*/  content_x; int /*<<< orphan*/  border_bottom; int /*<<< orphan*/  border_right; int /*<<< orphan*/  border_left; int /*<<< orphan*/  border_top; int /*<<< orphan*/  border_thickness; int /*<<< orphan*/  border; int /*<<< orphan*/  workspace; int /*<<< orphan*/  parent; int /*<<< orphan*/  fullscreen_mode; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  layout; } ;

/* Variables and functions */
 int /*<<< orphan*/  create_list () ; 
 struct sway_seat* input_manager_current_seat () ; 
 int /*<<< orphan*/  list_cat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sway_node* seat_get_active_tiling_child (struct sway_seat*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * seat_get_focus (struct sway_seat*) ; 

__attribute__((used)) static void copy_container_state(struct sway_container *container,
		struct sway_transaction_instruction *instruction) {
	struct sway_container_state *state = &instruction->container_state;

	state->layout = container->layout;
	state->x = container->x;
	state->y = container->y;
	state->width = container->width;
	state->height = container->height;
	state->fullscreen_mode = container->fullscreen_mode;
	state->parent = container->parent;
	state->workspace = container->workspace;
	state->border = container->border;
	state->border_thickness = container->border_thickness;
	state->border_top = container->border_top;
	state->border_left = container->border_left;
	state->border_right = container->border_right;
	state->border_bottom = container->border_bottom;
	state->content_x = container->content_x;
	state->content_y = container->content_y;
	state->content_width = container->content_width;
	state->content_height = container->content_height;

	if (!container->view) {
		state->children = create_list();
		list_cat(state->children, container->children);
	}

	struct sway_seat *seat = input_manager_current_seat();
	state->focused = seat_get_focus(seat) == &container->node;

	if (!container->view) {
		struct sway_node *focus =
			seat_get_active_tiling_child(seat, &container->node);
		state->focused_inactive_child = focus ? focus->sway_container : NULL;
	}
}