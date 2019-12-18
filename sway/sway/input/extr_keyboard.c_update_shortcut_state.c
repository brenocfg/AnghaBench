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
typedef  scalar_t__ uint32_t ;
struct wlr_event_keyboard_key {scalar_t__ state; scalar_t__ keycode; } ;
struct sway_shortcut_state {scalar_t__ last_raw_modifiers; scalar_t__ last_keycode; } ;

/* Variables and functions */
 scalar_t__ WLR_KEY_PRESSED ; 
 int /*<<< orphan*/  state_add_key (struct sway_shortcut_state*,scalar_t__,scalar_t__) ; 
 int state_erase_key (struct sway_shortcut_state*,scalar_t__) ; 

__attribute__((used)) static bool update_shortcut_state(struct sway_shortcut_state *state,
		struct wlr_event_keyboard_key *event, uint32_t new_key,
		uint32_t raw_modifiers) {
	bool last_key_was_a_modifier = raw_modifiers != state->last_raw_modifiers;
	state->last_raw_modifiers = raw_modifiers;

	if (last_key_was_a_modifier && state->last_keycode) {
		// Last pressed key before this one was a modifier
		state_erase_key(state, state->last_keycode);
	}

	if (event->state == WLR_KEY_PRESSED) {
		// Add current key to set; there may be duplicates
		state_add_key(state, event->keycode, new_key);
		state->last_keycode = event->keycode;
	} else {
		return state_erase_key(state, event->keycode);
	}

	return false;
}