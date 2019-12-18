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
typedef  int /*<<< orphan*/  uint32_t ;
struct wlr_input_device {int dummy; } ;
struct sway_seat {TYPE_1__* seatop_impl; } ;
typedef  enum wlr_button_state { ____Placeholder_wlr_button_state } wlr_button_state ;
struct TYPE_2__ {int /*<<< orphan*/  (* button ) (struct sway_seat*,int /*<<< orphan*/ ,struct wlr_input_device*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct sway_seat*,int /*<<< orphan*/ ,struct wlr_input_device*,int /*<<< orphan*/ ,int) ; 

void seatop_button(struct sway_seat *seat, uint32_t time_msec,
		struct wlr_input_device *device, uint32_t button,
		enum wlr_button_state state) {
	if (seat->seatop_impl->button) {
		seat->seatop_impl->button(seat, time_msec, device, button, state);
	}
}