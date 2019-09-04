#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xkb_keysym_t ;
typedef  int /*<<< orphan*/  xkb_keycode_t ;
struct xkb_keymap {int dummy; } ;
struct keycode_matches {scalar_t__ keysym; int /*<<< orphan*/  count; int /*<<< orphan*/  keycode; } ;
struct TYPE_2__ {int /*<<< orphan*/  keysym_translation_state; } ;

/* Variables and functions */
 scalar_t__ XKB_KEY_NoSymbol ; 
 TYPE_1__* config ; 
 scalar_t__ xkb_state_key_get_one_sym (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void find_keycode(struct xkb_keymap *keymap,
		xkb_keycode_t keycode, void *data) {
	xkb_keysym_t keysym = xkb_state_key_get_one_sym(
			config->keysym_translation_state, keycode);

	if (keysym == XKB_KEY_NoSymbol) {
		return;
	}

	struct keycode_matches *matches = data;
	if (matches->keysym == keysym) {
		matches->keycode = keycode;
		matches->count++;
	}
}