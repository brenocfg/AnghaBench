#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xkb_layout_index_t ;
typedef  int /*<<< orphan*/  xkb_keysym_t ;
typedef  int /*<<< orphan*/  xkb_keycode_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct wlr_input_device {TYPE_3__* keyboard; } ;
struct sway_keyboard {TYPE_2__* seat_device; } ;
struct TYPE_6__ {int /*<<< orphan*/  keymap; int /*<<< orphan*/  xkb_state; } ;
struct TYPE_5__ {TYPE_1__* input_device; } ;
struct TYPE_4__ {struct wlr_input_device* wlr_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  wlr_keyboard_get_modifiers (TYPE_3__*) ; 
 size_t xkb_keymap_key_get_syms_by_level (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  xkb_state_key_get_layout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t keyboard_keysyms_raw(struct sway_keyboard *keyboard,
		xkb_keycode_t keycode, const xkb_keysym_t **keysyms,
		uint32_t *modifiers) {
	struct wlr_input_device *device =
		keyboard->seat_device->input_device->wlr_device;
	*modifiers = wlr_keyboard_get_modifiers(device->keyboard);

	xkb_layout_index_t layout_index = xkb_state_key_get_layout(
		device->keyboard->xkb_state, keycode);
	return xkb_keymap_key_get_syms_by_level(device->keyboard->keymap,
		keycode, layout_index, 0, keysyms);
}