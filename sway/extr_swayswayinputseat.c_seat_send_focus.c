#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wlr_pointer_constraint_v1 {int dummy; } ;
struct wlr_keyboard {int /*<<< orphan*/  modifiers; int /*<<< orphan*/  num_keycodes; int /*<<< orphan*/ * keycodes; } ;
struct sway_view {int /*<<< orphan*/  surface; } ;
struct sway_seat {int /*<<< orphan*/  cursor; int /*<<< orphan*/  wlr_seat; } ;
struct sway_node {scalar_t__ type; TYPE_1__* sway_container; } ;
struct TYPE_4__ {int /*<<< orphan*/  pointer_constraints; } ;
struct TYPE_3__ {struct sway_view* view; } ;

/* Variables and functions */
 scalar_t__ N_CONTAINER ; 
 scalar_t__ seat_is_input_allowed (struct sway_seat*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seat_send_activate (struct sway_node*,struct sway_seat*) ; 
 TYPE_2__ server ; 
 int /*<<< orphan*/  sway_cursor_constrain (int /*<<< orphan*/ ,struct wlr_pointer_constraint_v1*) ; 
 struct wlr_pointer_constraint_v1* wlr_pointer_constraints_v1_constraint_for_surface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wlr_keyboard* wlr_seat_get_keyboard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_seat_keyboard_notify_enter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void seat_send_focus(struct sway_node *node, struct sway_seat *seat) {
	seat_send_activate(node, seat);

	struct sway_view *view = node->type == N_CONTAINER ?
		node->sway_container->view : NULL;

	if (view && seat_is_input_allowed(seat, view->surface)) {
#if HAVE_XWAYLAND
		if (view->type == SWAY_VIEW_XWAYLAND) {
			struct wlr_xwayland *xwayland = server.xwayland.wlr_xwayland;
			wlr_xwayland_set_seat(xwayland, seat->wlr_seat);
		}
#endif
		struct wlr_keyboard *keyboard = wlr_seat_get_keyboard(seat->wlr_seat);
		if (keyboard) {
			wlr_seat_keyboard_notify_enter(seat->wlr_seat,
					view->surface, keyboard->keycodes,
					keyboard->num_keycodes, &keyboard->modifiers);
		} else {
			wlr_seat_keyboard_notify_enter(
					seat->wlr_seat, view->surface, NULL, 0, NULL);
		}

		struct wlr_pointer_constraint_v1 *constraint =
			wlr_pointer_constraints_v1_constraint_for_surface(
				server.pointer_constraints, view->surface, seat->wlr_seat);
		sway_cursor_constrain(seat->cursor, constraint);
	}
}