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
struct sway_shortcut_state {size_t npressed; scalar_t__* pressed_keycodes; scalar_t__ current_key; scalar_t__* pressed_keys; } ;

/* Variables and functions */

__attribute__((used)) static void state_erase_key(struct sway_shortcut_state *state,
		uint32_t keycode) {
	size_t j = 0;
	for (size_t i = 0; i < state->npressed; ++i) {
		if (i > j) {
			state->pressed_keys[j] = state->pressed_keys[i];
			state->pressed_keycodes[j] = state->pressed_keycodes[i];
		}
		if (state->pressed_keycodes[i] != keycode) {
			++j;
		}
	}
	while(state->npressed > j) {
		--state->npressed;
		state->pressed_keys[state->npressed] = 0;
		state->pressed_keycodes[state->npressed] = 0;
	}
	state->current_key = 0;
}