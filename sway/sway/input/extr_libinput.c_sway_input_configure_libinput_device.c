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
struct sway_input_device {char* identifier; TYPE_1__* wlr_device; } ;
struct libinput_device {int dummy; } ;
struct input_config {int dummy; } ;
struct TYPE_3__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ WLR_INPUT_DEVICE_KEYBOARD ; 
 scalar_t__ WLR_INPUT_DEVICE_POINTER ; 
 scalar_t__ WLR_INPUT_DEVICE_SWITCH ; 
 scalar_t__ WLR_INPUT_DEVICE_TABLET_TOOL ; 
 scalar_t__ WLR_INPUT_DEVICE_TOUCH ; 
 int config_libinput_keyboard (struct libinput_device*,struct input_config*,char const*) ; 
 int config_libinput_pointer (struct libinput_device*,struct input_config*,char const*) ; 
 int config_libinput_switch (struct libinput_device*,struct input_config*,char const*) ; 
 int config_libinput_touch (struct libinput_device*,struct input_config*,char const*) ; 
 struct input_config* input_device_get_config (struct sway_input_device*) ; 
 int /*<<< orphan*/  ipc_event_input (char*,struct sway_input_device*) ; 
 int /*<<< orphan*/  wlr_input_device_is_libinput (TYPE_1__*) ; 
 struct libinput_device* wlr_libinput_get_device_handle (TYPE_1__*) ; 

void sway_input_configure_libinput_device(struct sway_input_device *device) {
	struct input_config *ic = input_device_get_config(device);
	if (!ic || !wlr_input_device_is_libinput(device->wlr_device)) {
		return;
	}
	bool changed = false;
	const char *device_id = device->identifier;
	struct libinput_device *libinput_device =
		wlr_libinput_get_device_handle(device->wlr_device);
	if (device->wlr_device->type == WLR_INPUT_DEVICE_POINTER ||
			device->wlr_device->type == WLR_INPUT_DEVICE_TABLET_TOOL) {
		changed = config_libinput_pointer(libinput_device, ic, device_id);
	} else if (device->wlr_device->type == WLR_INPUT_DEVICE_KEYBOARD) {
		changed = config_libinput_keyboard(libinput_device, ic, device_id);
	} else if (device->wlr_device->type == WLR_INPUT_DEVICE_SWITCH) {
		changed = config_libinput_switch(libinput_device, ic, device_id);
	} else if (device->wlr_device->type == WLR_INPUT_DEVICE_TOUCH) {
		changed = config_libinput_touch(libinput_device, ic, device_id);
	}
	if (changed) {
		ipc_event_input("libinput_config", device);
	}
}