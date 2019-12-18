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
struct sway_seat_device {int dummy; } ;
struct sway_seat {int dummy; } ;
struct sway_input_device {TYPE_1__* wlr_device; } ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
#define  WLR_INPUT_DEVICE_KEYBOARD 133 
#define  WLR_INPUT_DEVICE_POINTER 132 
#define  WLR_INPUT_DEVICE_SWITCH 131 
#define  WLR_INPUT_DEVICE_TABLET_PAD 130 
#define  WLR_INPUT_DEVICE_TABLET_TOOL 129 
#define  WLR_INPUT_DEVICE_TOUCH 128 
 int /*<<< orphan*/  seat_configure_keyboard (struct sway_seat*,struct sway_seat_device*) ; 
 int /*<<< orphan*/  seat_configure_pointer (struct sway_seat*,struct sway_seat_device*) ; 
 int /*<<< orphan*/  seat_configure_switch (struct sway_seat*,struct sway_seat_device*) ; 
 int /*<<< orphan*/  seat_configure_tablet_pad (struct sway_seat*,struct sway_seat_device*) ; 
 int /*<<< orphan*/  seat_configure_tablet_tool (struct sway_seat*,struct sway_seat_device*) ; 
 int /*<<< orphan*/  seat_configure_touch (struct sway_seat*,struct sway_seat_device*) ; 
 struct sway_seat_device* seat_get_device (struct sway_seat*,struct sway_input_device*) ; 

void seat_configure_device(struct sway_seat *seat,
		struct sway_input_device *input_device) {
	struct sway_seat_device *seat_device = seat_get_device(seat, input_device);
	if (!seat_device) {
		return;
	}

	switch (input_device->wlr_device->type) {
		case WLR_INPUT_DEVICE_POINTER:
			seat_configure_pointer(seat, seat_device);
			break;
		case WLR_INPUT_DEVICE_KEYBOARD:
			seat_configure_keyboard(seat, seat_device);
			break;
		case WLR_INPUT_DEVICE_SWITCH:
			seat_configure_switch(seat, seat_device);
			break;
		case WLR_INPUT_DEVICE_TOUCH:
			seat_configure_touch(seat, seat_device);
			break;
		case WLR_INPUT_DEVICE_TABLET_TOOL:
			seat_configure_tablet_tool(seat, seat_device);
			break;
		case WLR_INPUT_DEVICE_TABLET_PAD:
			seat_configure_tablet_pad(seat, seat_device);
			break;
	}
}