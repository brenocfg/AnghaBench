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
typedef  int /*<<< orphan*/  uint32_t ;
struct sway_seat {int /*<<< orphan*/  wlr_seat; int /*<<< orphan*/  last_button_serial; } ;
typedef  enum wlr_button_state { ____Placeholder_wlr_button_state } wlr_button_state ;

/* Variables and functions */
 int /*<<< orphan*/  wlr_seat_pointer_notify_button (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void seat_pointer_notify_button(struct sway_seat *seat, uint32_t time_msec,
		uint32_t button, enum wlr_button_state state) {
	seat->last_button_serial = wlr_seat_pointer_notify_button(seat->wlr_seat,
			time_msec, button, state);
}