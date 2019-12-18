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
struct wlr_keyboard {int /*<<< orphan*/  modifiers; } ;
struct sway_shortcut_state {int /*<<< orphan*/  npressed; int /*<<< orphan*/ * pressed_keycodes; } ;
struct sway_seat {int /*<<< orphan*/  wlr_seat; } ;
struct sway_keyboard {struct sway_shortcut_state state_pressed_sent; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 struct sway_keyboard* sway_keyboard_for_wlr_keyboard (struct sway_seat*,struct wlr_keyboard*) ; 
 struct wlr_keyboard* wlr_seat_get_keyboard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_seat_keyboard_notify_enter (int /*<<< orphan*/ ,struct wlr_surface*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void seat_keyboard_notify_enter(struct sway_seat *seat,
		struct wlr_surface *surface) {
	struct wlr_keyboard *keyboard = wlr_seat_get_keyboard(seat->wlr_seat);
	if (!keyboard) {
		wlr_seat_keyboard_notify_enter(seat->wlr_seat, surface, NULL, 0, NULL);
		return;
	}

	struct sway_keyboard *sway_keyboard =
		sway_keyboard_for_wlr_keyboard(seat, keyboard);
	assert(sway_keyboard && "Cannot find sway_keyboard for seat keyboard");

	struct sway_shortcut_state *state = &sway_keyboard->state_pressed_sent;
	wlr_seat_keyboard_notify_enter(seat->wlr_seat, surface,
			state->pressed_keycodes, state->npressed, &keyboard->modifiers);
}