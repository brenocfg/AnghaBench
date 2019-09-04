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
struct seatop_default_event {size_t pressed_button_count; scalar_t__* pressed_buttons; } ;

/* Variables and functions */
 size_t SWAY_CURSOR_PRESSED_BUTTONS_CAP ; 

__attribute__((used)) static void state_add_button(struct seatop_default_event *e, uint32_t button) {
	if (e->pressed_button_count >= SWAY_CURSOR_PRESSED_BUTTONS_CAP) {
		return;
	}
	size_t i = 0;
	while (i < e->pressed_button_count && e->pressed_buttons[i] < button) {
		++i;
	}
	size_t j = e->pressed_button_count;
	while (j > i) {
		e->pressed_buttons[j] = e->pressed_buttons[j - 1];
		--j;
	}
	e->pressed_buttons[i] = button;
	e->pressed_button_count++;
}