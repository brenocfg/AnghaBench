#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xkb_layout_index_t ;
struct xkb_state {int dummy; } ;
struct xkb_keymap {int dummy; } ;
struct wlr_keyboard {struct xkb_state* xkb_state; struct xkb_keymap* keymap; } ;
struct sway_input_device {char const* identifier; TYPE_1__* wlr_device; } ;
struct libinput_device {int dummy; } ;
typedef  int /*<<< orphan*/  json_object ;
struct TYPE_3__ {char const* name; scalar_t__ vendor; scalar_t__ product; scalar_t__ type; struct wlr_keyboard* keyboard; } ;

/* Variables and functions */
 scalar_t__ WLR_INPUT_DEVICE_KEYBOARD ; 
 int /*<<< orphan*/  XKB_STATE_LAYOUT_EFFECTIVE ; 
 int /*<<< orphan*/ * describe_libinput_device (struct libinput_device*) ; 
 char const* input_device_get_type (struct sway_input_device*) ; 
 int /*<<< orphan*/  json_object_array_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_object_new_array () ; 
 int /*<<< orphan*/ * json_object_new_int (scalar_t__) ; 
 int /*<<< orphan*/ * json_object_new_object () ; 
 int /*<<< orphan*/ * json_object_new_string (char const*) ; 
 int /*<<< orphan*/  json_object_object_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sway_assert (struct sway_input_device*,char*) ; 
 scalar_t__ wlr_input_device_is_libinput (TYPE_1__*) ; 
 struct libinput_device* wlr_libinput_get_device_handle (TYPE_1__*) ; 
 char* xkb_keymap_layout_get_name (struct xkb_keymap*,scalar_t__) ; 
 scalar_t__ xkb_keymap_num_layouts (struct xkb_keymap*) ; 
 int xkb_state_layout_index_is_active (struct xkb_state*,scalar_t__,int /*<<< orphan*/ ) ; 

json_object *ipc_json_describe_input(struct sway_input_device *device) {
	if (!(sway_assert(device, "Device must not be null"))) {
		return NULL;
	}

	json_object *object = json_object_new_object();

	json_object_object_add(object, "identifier",
		json_object_new_string(device->identifier));
	json_object_object_add(object, "name",
		json_object_new_string(device->wlr_device->name));
	json_object_object_add(object, "vendor",
		json_object_new_int(device->wlr_device->vendor));
	json_object_object_add(object, "product",
		json_object_new_int(device->wlr_device->product));
	json_object_object_add(object, "type",
		json_object_new_string(
			input_device_get_type(device)));

	if (device->wlr_device->type == WLR_INPUT_DEVICE_KEYBOARD) {
		struct wlr_keyboard *keyboard = device->wlr_device->keyboard;
		struct xkb_keymap *keymap = keyboard->keymap;
		struct xkb_state *state = keyboard->xkb_state;

		json_object *layouts_arr = json_object_new_array();
		json_object_object_add(object, "xkb_layout_names", layouts_arr);

		xkb_layout_index_t num_layouts = xkb_keymap_num_layouts(keymap);
		xkb_layout_index_t layout_idx;
		for (layout_idx = 0; layout_idx < num_layouts; layout_idx++) {
			const char *layout = xkb_keymap_layout_get_name(keymap, layout_idx);
			json_object_array_add(layouts_arr,
				layout ? json_object_new_string(layout) : NULL);

			bool is_active = xkb_state_layout_index_is_active(state,
				layout_idx, XKB_STATE_LAYOUT_EFFECTIVE);
			if (is_active) {
				json_object_object_add(object, "xkb_active_layout_index",
					json_object_new_int(layout_idx));
				json_object_object_add(object, "xkb_active_layout_name",
					layout ? json_object_new_string(layout) : NULL);
			}
		}
	}

	if (wlr_input_device_is_libinput(device->wlr_device)) {
		struct libinput_device *libinput_dev;
		libinput_dev = wlr_libinput_get_device_handle(device->wlr_device);
		json_object_object_add(object, "libinput",
				describe_libinput_device(libinput_dev));
	}

	return object;
}