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
struct sway_seat_device {TYPE_3__* input_device; } ;
struct sway_seat {TYPE_2__* cursor; TYPE_1__* wlr_seat; } ;
struct TYPE_6__ {int /*<<< orphan*/  wlr_device; } ;
struct TYPE_5__ {int /*<<< orphan*/  cursor; } ;
struct TYPE_4__ {int capabilities; } ;

/* Variables and functions */
 int WL_SEAT_CAPABILITY_POINTER ; 
 int /*<<< orphan*/  seat_apply_input_config (struct sway_seat*,struct sway_seat_device*) ; 
 int /*<<< orphan*/  seat_configure_xcursor (struct sway_seat*) ; 
 int /*<<< orphan*/  wlr_cursor_attach_input_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void seat_configure_pointer(struct sway_seat *seat,
		struct sway_seat_device *sway_device) {
	if ((seat->wlr_seat->capabilities & WL_SEAT_CAPABILITY_POINTER) == 0) {
		seat_configure_xcursor(seat);
	}
	wlr_cursor_attach_input_device(seat->cursor->cursor,
		sway_device->input_device->wlr_device);
	seat_apply_input_config(seat, sway_device);
}