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
struct TYPE_2__ {int /*<<< orphan*/  link; } ;
struct sway_switch {TYPE_1__ switch_toggle; int /*<<< orphan*/  state; struct sway_seat_device* seat_device; } ;
struct sway_seat_device {struct sway_switch* switch_device; } ;
struct sway_seat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  WLR_SWITCH_STATE_OFF ; 
 struct sway_switch* calloc (int,int) ; 
 int /*<<< orphan*/  sway_assert (struct sway_switch*,char*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl_list_init (int /*<<< orphan*/ *) ; 

struct sway_switch *sway_switch_create(struct sway_seat *seat,
		struct sway_seat_device *device) {
	struct sway_switch *switch_device =
		calloc(1, sizeof(struct sway_switch));
	if (!sway_assert(switch_device, "could not allocate switch")) {
		return NULL;
	}
	device->switch_device = switch_device;
	switch_device->seat_device = device;
	switch_device->state = WLR_SWITCH_STATE_OFF;
	wl_list_init(&switch_device->switch_toggle.link);
	sway_log(SWAY_DEBUG, "Allocated switch for device");

	return switch_device;
}