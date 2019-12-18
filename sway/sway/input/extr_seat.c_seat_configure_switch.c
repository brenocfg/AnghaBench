#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sway_seat_device {int /*<<< orphan*/  switch_device; } ;
struct sway_seat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  seat_apply_input_config (struct sway_seat*,struct sway_seat_device*) ; 
 int /*<<< orphan*/  sway_switch_configure (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sway_switch_create (struct sway_seat*,struct sway_seat_device*) ; 

__attribute__((used)) static void seat_configure_switch(struct sway_seat *seat,
        struct sway_seat_device *seat_device) {
	if (!seat_device->switch_device) {
		sway_switch_create(seat, seat_device);
	}
	seat_apply_input_config(seat, seat_device);
	sway_switch_configure(seat_device->switch_device);
}