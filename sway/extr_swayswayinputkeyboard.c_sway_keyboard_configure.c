#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int xkb_mod_mask_t ;
typedef  int xkb_mod_index_t ;
typedef  int uint32_t ;
struct xkb_rule_names {void* variant; void* rules; void* options; void* model; void* layout; int /*<<< orphan*/  member_0; } ;
struct xkb_keymap {int dummy; } ;
struct xkb_context {int dummy; } ;
struct wlr_seat {int dummy; } ;
struct wlr_input_device {TYPE_4__* keyboard; } ;
struct TYPE_14__ {int /*<<< orphan*/  notify; int /*<<< orphan*/  link; } ;
struct sway_keyboard {TYPE_8__ keyboard_modifiers; TYPE_8__ keyboard_key; TYPE_2__* seat_device; struct xkb_keymap* keymap; } ;
struct input_config {scalar_t__ xkb_numlock; scalar_t__ xkb_capslock; int repeat_rate; int repeat_delay; } ;
struct TYPE_15__ {struct wlr_input_device* wlr_device; } ;
struct TYPE_12__ {int /*<<< orphan*/  modifiers; int /*<<< orphan*/  key; } ;
struct TYPE_13__ {TYPE_3__ events; int /*<<< orphan*/ * led_indexes; int /*<<< orphan*/  xkb_state; } ;
struct TYPE_11__ {TYPE_1__* sway_seat; TYPE_9__* input_device; } ;
struct TYPE_10__ {struct wlr_seat* wlr_seat; } ;

/* Variables and functions */
 int INT_MIN ; 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int WLR_LED_COUNT ; 
 int /*<<< orphan*/  XKB_CONTEXT_NO_FLAGS ; 
 int /*<<< orphan*/  XKB_KEYMAP_COMPILE_NO_FLAGS ; 
 int XKB_MOD_INVALID ; 
 int /*<<< orphan*/  XKB_MOD_NAME_CAPS ; 
 int /*<<< orphan*/  XKB_MOD_NAME_NUM ; 
 void* getenv (char*) ; 
 int /*<<< orphan*/  handle_keyboard_key ; 
 int /*<<< orphan*/  handle_keyboard_modifiers ; 
 int /*<<< orphan*/  input_config_fill_rule_names (struct input_config*,struct xkb_rule_names*) ; 
 struct input_config* input_device_get_config (TYPE_9__*) ; 
 int /*<<< orphan*/  sway_assert (struct xkb_context*,char*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl_list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_signal_add (int /*<<< orphan*/ *,TYPE_8__*) ; 
 int /*<<< orphan*/  wlr_keyboard_led_update (TYPE_4__*,int) ; 
 int /*<<< orphan*/  wlr_keyboard_notify_modifiers (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_keyboard_set_keymap (TYPE_4__*,struct xkb_keymap*) ; 
 int /*<<< orphan*/  wlr_keyboard_set_repeat_info (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  wlr_seat_set_keyboard (struct wlr_seat*,struct wlr_input_device*) ; 
 struct xkb_context* xkb_context_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xkb_context_unref (struct xkb_context*) ; 
 struct xkb_keymap* xkb_keymap_new_from_names (struct xkb_context*,struct xkb_rule_names*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xkb_keymap_unref (struct xkb_keymap*) ; 
 int xkb_map_mod_get_index (struct xkb_keymap*,int /*<<< orphan*/ ) ; 
 scalar_t__ xkb_state_led_index_is_active (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sway_keyboard_configure(struct sway_keyboard *keyboard) {
	struct input_config *input_config =
		input_device_get_config(keyboard->seat_device->input_device);
	struct wlr_input_device *wlr_device =
		keyboard->seat_device->input_device->wlr_device;

	struct xkb_rule_names rules = {0};
	if (input_config) {
		input_config_fill_rule_names(input_config, &rules);
	}

	if (!rules.layout) {
		rules.layout = getenv("XKB_DEFAULT_LAYOUT");
	}
	if (!rules.model) {
		rules.model = getenv("XKB_DEFAULT_MODEL");
	}
	if (!rules.options) {
		rules.options = getenv("XKB_DEFAULT_OPTIONS");
	}
	if (!rules.rules) {
		rules.rules = getenv("XKB_DEFAULT_RULES");
	}
	if (!rules.variant) {
		rules.variant = getenv("XKB_DEFAULT_VARIANT");
	}

	struct xkb_context *context = xkb_context_new(XKB_CONTEXT_NO_FLAGS);
	if (!sway_assert(context, "cannot create XKB context")) {
		return;
	}

	struct xkb_keymap *keymap =
		xkb_keymap_new_from_names(context, &rules, XKB_KEYMAP_COMPILE_NO_FLAGS);

	if (!keymap) {
		sway_log(SWAY_DEBUG, "cannot configure keyboard: keymap does not exist");
		xkb_context_unref(context);
		return;
	}

	xkb_keymap_unref(keyboard->keymap);
	keyboard->keymap = keymap;
	wlr_keyboard_set_keymap(wlr_device->keyboard, keyboard->keymap);

	xkb_mod_mask_t locked_mods = 0;
	if (input_config && input_config->xkb_numlock > 0) {
		xkb_mod_index_t mod_index = xkb_map_mod_get_index(keymap, XKB_MOD_NAME_NUM);
		if (mod_index != XKB_MOD_INVALID) {
		       locked_mods |= (uint32_t)1 << mod_index;
		}
	}
	if (input_config && input_config->xkb_capslock > 0) {
		xkb_mod_index_t mod_index = xkb_map_mod_get_index(keymap, XKB_MOD_NAME_CAPS);
		if (mod_index != XKB_MOD_INVALID) {
		       locked_mods |= (uint32_t)1 << mod_index;
		}
	}
	if (locked_mods) {
		wlr_keyboard_notify_modifiers(wlr_device->keyboard, 0, 0, locked_mods, 0);
		uint32_t leds = 0;
		for (uint32_t i = 0; i < WLR_LED_COUNT; ++i) {
			if (xkb_state_led_index_is_active(wlr_device->keyboard->xkb_state,
					wlr_device->keyboard->led_indexes[i])) {
				leds |= (1 << i);
			}
		}
		wlr_keyboard_led_update(wlr_device->keyboard, leds);
	}

	int repeat_rate = 25;
	if (input_config && input_config->repeat_rate != INT_MIN) {
		repeat_rate = input_config->repeat_rate;
	}
	int repeat_delay = 600;
	if (input_config && input_config->repeat_delay != INT_MIN) {
		repeat_delay = input_config->repeat_delay;
	}
	wlr_keyboard_set_repeat_info(wlr_device->keyboard, repeat_rate,
			repeat_delay);

	xkb_context_unref(context);
	struct wlr_seat *seat = keyboard->seat_device->sway_seat->wlr_seat;
	wlr_seat_set_keyboard(seat, wlr_device);

	wl_list_remove(&keyboard->keyboard_key.link);
	wl_signal_add(&wlr_device->keyboard->events.key, &keyboard->keyboard_key);
	keyboard->keyboard_key.notify = handle_keyboard_key;

	wl_list_remove(&keyboard->keyboard_modifiers.link);
	wl_signal_add(&wlr_device->keyboard->events.modifiers,
		&keyboard->keyboard_modifiers);
	keyboard->keyboard_modifiers.notify = handle_keyboard_modifiers;
}