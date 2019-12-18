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
struct sway_seat_device {int /*<<< orphan*/  tablet_pad; int /*<<< orphan*/  tablet; } ;
struct sway_seat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sway_configure_tablet_pad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sway_tablet_pad_create (struct sway_seat*,struct sway_seat_device*) ; 

__attribute__((used)) static void seat_configure_tablet_pad(struct sway_seat *seat,
		struct sway_seat_device *sway_device) {
	if (!sway_device->tablet) {
		sway_device->tablet_pad = sway_tablet_pad_create(seat, sway_device);
	}
	sway_configure_tablet_pad(sway_device->tablet_pad);
}