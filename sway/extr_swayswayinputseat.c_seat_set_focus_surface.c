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
struct wlr_surface {int dummy; } ;
struct wlr_keyboard {int /*<<< orphan*/  modifiers; int /*<<< orphan*/  num_keycodes; int /*<<< orphan*/ * keycodes; } ;
struct sway_seat {int has_focus; int /*<<< orphan*/  wlr_seat; } ;
struct sway_node {int dummy; } ;

/* Variables and functions */
 struct sway_node* seat_get_focus (struct sway_seat*) ; 
 int /*<<< orphan*/  seat_send_unfocus (struct sway_node*,struct sway_seat*) ; 
 struct wlr_keyboard* wlr_seat_get_keyboard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_seat_keyboard_notify_enter (int /*<<< orphan*/ ,struct wlr_surface*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void seat_set_focus_surface(struct sway_seat *seat,
		struct wlr_surface *surface, bool unfocus) {
	if (seat->has_focus && unfocus) {
		struct sway_node *focus = seat_get_focus(seat);
		seat_send_unfocus(focus, seat);
		seat->has_focus = false;
	}
	struct wlr_keyboard *keyboard = wlr_seat_get_keyboard(seat->wlr_seat);
	if (keyboard) {
		wlr_seat_keyboard_notify_enter(seat->wlr_seat, surface,
			keyboard->keycodes, keyboard->num_keycodes, &keyboard->modifiers);
	} else {
		wlr_seat_keyboard_notify_enter(seat->wlr_seat, surface, NULL, 0, NULL);
	}
}