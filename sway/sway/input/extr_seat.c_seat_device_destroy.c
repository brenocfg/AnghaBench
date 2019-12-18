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
struct sway_seat_device {int /*<<< orphan*/  link; TYPE_3__* input_device; TYPE_2__* sway_seat; int /*<<< orphan*/  tablet_pad; int /*<<< orphan*/  tablet; int /*<<< orphan*/  keyboard; } ;
struct TYPE_6__ {int /*<<< orphan*/  wlr_device; } ;
struct TYPE_5__ {TYPE_1__* cursor; } ;
struct TYPE_4__ {int /*<<< orphan*/  cursor; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct sway_seat_device*) ; 
 int /*<<< orphan*/  sway_keyboard_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sway_tablet_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sway_tablet_pad_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wlr_cursor_detach_input_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void seat_device_destroy(struct sway_seat_device *seat_device) {
	if (!seat_device) {
		return;
	}

	sway_keyboard_destroy(seat_device->keyboard);
	sway_tablet_destroy(seat_device->tablet);
	sway_tablet_pad_destroy(seat_device->tablet_pad);
	wlr_cursor_detach_input_device(seat_device->sway_seat->cursor->cursor,
		seat_device->input_device->wlr_device);
	wl_list_remove(&seat_device->link);
	free(seat_device);
}