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
struct sway_input_device {TYPE_1__* wlr_device; } ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
#define  WLR_INPUT_DEVICE_KEYBOARD 133 
#define  WLR_INPUT_DEVICE_POINTER 132 
#define  WLR_INPUT_DEVICE_SWITCH 131 
#define  WLR_INPUT_DEVICE_TABLET_PAD 130 
#define  WLR_INPUT_DEVICE_TABLET_TOOL 129 
#define  WLR_INPUT_DEVICE_TOUCH 128 
 int /*<<< orphan*/  device_is_touchpad (struct sway_input_device*) ; 

const char *input_device_get_type(struct sway_input_device *device) {
	switch (device->wlr_device->type) {
	case WLR_INPUT_DEVICE_POINTER:
		if (device_is_touchpad(device)) {
			return "touchpad";
		} else {
			return "pointer";
		}
	case WLR_INPUT_DEVICE_KEYBOARD:
		return "keyboard";
	case WLR_INPUT_DEVICE_TOUCH:
		return "touch";
	case WLR_INPUT_DEVICE_TABLET_TOOL:
		return "tablet_tool";
	case WLR_INPUT_DEVICE_TABLET_PAD:
		return "tablet_pad";
	case WLR_INPUT_DEVICE_SWITCH:
		return "switch";
	}
	return "unknown";
}