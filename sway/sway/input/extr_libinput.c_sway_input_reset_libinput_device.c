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
struct sway_input_device {int /*<<< orphan*/  identifier; TYPE_1__* wlr_device; } ;
struct libinput_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ WLR_INPUT_DEVICE_KEYBOARD ; 
 scalar_t__ WLR_INPUT_DEVICE_POINTER ; 
 scalar_t__ WLR_INPUT_DEVICE_SWITCH ; 
 scalar_t__ WLR_INPUT_DEVICE_TABLET_TOOL ; 
 scalar_t__ WLR_INPUT_DEVICE_TOUCH ; 
 int /*<<< orphan*/  ipc_event_input (char*,struct sway_input_device*) ; 
 int reset_libinput_keyboard (struct libinput_device*,int /*<<< orphan*/ ) ; 
 int reset_libinput_pointer (struct libinput_device*,int /*<<< orphan*/ ) ; 
 int reset_libinput_switch (struct libinput_device*,int /*<<< orphan*/ ) ; 
 int reset_libinput_touch (struct libinput_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_input_device_is_libinput (TYPE_1__*) ; 
 struct libinput_device* wlr_libinput_get_device_handle (TYPE_1__*) ; 

void sway_input_reset_libinput_device(struct sway_input_device *device) {
	if (!wlr_input_device_is_libinput(device->wlr_device)) {
		return;
	}
	bool changed = false;
	struct libinput_device *libinput_device =
		wlr_libinput_get_device_handle(device->wlr_device);
	if (device->wlr_device->type == WLR_INPUT_DEVICE_POINTER ||
			device->wlr_device->type == WLR_INPUT_DEVICE_TABLET_TOOL) {
		changed = reset_libinput_pointer(libinput_device, device->identifier);
	} else if (device->wlr_device->type == WLR_INPUT_DEVICE_KEYBOARD) {
		changed = reset_libinput_keyboard(libinput_device, device->identifier);
	} else if (device->wlr_device->type == WLR_INPUT_DEVICE_SWITCH) {
		changed = reset_libinput_switch(libinput_device, device->identifier);
	} else if (device->wlr_device->type == WLR_INPUT_DEVICE_TOUCH) {
		changed = reset_libinput_touch(libinput_device, device->identifier);
	}
	if (changed) {
		ipc_event_input("libinput_config", device);
	}
}