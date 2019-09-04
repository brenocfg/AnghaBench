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
struct TYPE_4__ {int /*<<< orphan*/  link; } ;
struct TYPE_3__ {int /*<<< orphan*/  link; } ;
struct sway_keyboard {int /*<<< orphan*/  key_repeat_source; TYPE_2__ keyboard_modifiers; TYPE_1__ keyboard_key; scalar_t__ keymap; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct sway_keyboard*) ; 
 int /*<<< orphan*/  sway_keyboard_disarm_key_repeat (struct sway_keyboard*) ; 
 int /*<<< orphan*/  wl_event_source_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xkb_keymap_unref (scalar_t__) ; 

void sway_keyboard_destroy(struct sway_keyboard *keyboard) {
	if (!keyboard) {
		return;
	}
	if (keyboard->keymap) {
		xkb_keymap_unref(keyboard->keymap);
	}
	wl_list_remove(&keyboard->keyboard_key.link);
	wl_list_remove(&keyboard->keyboard_modifiers.link);
	sway_keyboard_disarm_key_repeat(keyboard);
	wl_event_source_remove(keyboard->key_repeat_source);
	free(keyboard);
}