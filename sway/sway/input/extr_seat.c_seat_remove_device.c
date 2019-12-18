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
struct sway_seat {TYPE_1__* wlr_seat; } ;
struct sway_input_device {int /*<<< orphan*/  identifier; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  seat_device_destroy (struct sway_seat_device*) ; 
 struct sway_seat_device* seat_get_device (struct sway_seat*,struct sway_input_device*) ; 
 int /*<<< orphan*/  seat_update_capabilities (struct sway_seat*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void seat_remove_device(struct sway_seat *seat,
		struct sway_input_device *input_device) {
	struct sway_seat_device *seat_device = seat_get_device(seat, input_device);

	if (!seat_device) {
		return;
	}

	sway_log(SWAY_DEBUG, "removing device %s from seat %s",
		input_device->identifier, seat->wlr_seat->name);

	seat_device_destroy(seat_device);

	seat_update_capabilities(seat);
}