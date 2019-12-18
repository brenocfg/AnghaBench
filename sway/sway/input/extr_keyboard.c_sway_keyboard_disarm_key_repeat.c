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
struct sway_keyboard {int /*<<< orphan*/  key_repeat_source; int /*<<< orphan*/ * repeat_binding; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wl_event_source_timer_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sway_keyboard_disarm_key_repeat(struct sway_keyboard *keyboard) {
	if (!keyboard) {
		return;
	}
	keyboard->repeat_binding = NULL;
	if (wl_event_source_timer_update(keyboard->key_repeat_source, 0) < 0) {
		sway_log(SWAY_DEBUG, "failed to disarm key repeat timer");
	}
}