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
struct sway_seat_device {int /*<<< orphan*/  keyboard; } ;
struct sway_seat {int dummy; } ;
struct sway_input_device {TYPE_1__* wlr_device; } ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
#define  WLR_INPUT_DEVICE_KEYBOARD 133 
#define  WLR_INPUT_DEVICE_POINTER 132 
#define  WLR_INPUT_DEVICE_SWITCH 131 
#define  WLR_INPUT_DEVICE_TABLET_PAD 130 
#define  WLR_INPUT_DEVICE_TABLET_TOOL 129 
#define  WLR_INPUT_DEVICE_TOUCH 128 
 struct sway_seat_device* seat_get_device (struct sway_seat*,struct sway_input_device*) ; 
 int /*<<< orphan*/  seat_reset_input_config (struct sway_seat*,struct sway_seat_device*) ; 
 int /*<<< orphan*/  sway_keyboard_configure (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sway_keyboard_disarm_key_repeat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 

void seat_reset_device(struct sway_seat *seat,
		struct sway_input_device *input_device) {
	struct sway_seat_device *seat_device = seat_get_device(seat, input_device);
	if (!seat_device) {
		return;
	}

	switch (input_device->wlr_device->type) {
		case WLR_INPUT_DEVICE_POINTER:
			seat_reset_input_config(seat, seat_device);
			break;
		case WLR_INPUT_DEVICE_KEYBOARD:
			sway_keyboard_disarm_key_repeat(seat_device->keyboard);
			sway_keyboard_configure(seat_device->keyboard);
			break;
		case WLR_INPUT_DEVICE_TOUCH:
			seat_reset_input_config(seat, seat_device);
			break;
		case WLR_INPUT_DEVICE_TABLET_TOOL:
			seat_reset_input_config(seat, seat_device);
			break;
		case WLR_INPUT_DEVICE_TABLET_PAD:
			sway_log(SWAY_DEBUG, "TODO: reset tablet pad");
			break;
		case WLR_INPUT_DEVICE_SWITCH:
			sway_log(SWAY_DEBUG, "TODO: reset switch device");
			break;
	}
}