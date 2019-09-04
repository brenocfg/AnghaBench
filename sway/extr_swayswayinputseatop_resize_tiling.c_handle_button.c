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
struct sway_seat {TYPE_1__* cursor; } ;
typedef  enum wlr_button_state { ____Placeholder_wlr_button_state } wlr_button_state ;
struct TYPE_2__ {scalar_t__ pressed_button_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  seatop_begin_default (struct sway_seat*) ; 

__attribute__((used)) static void handle_button(struct sway_seat *seat, uint32_t time_msec,
		struct wlr_input_device *device, uint32_t button,
		enum wlr_button_state state) {
	if (seat->cursor->pressed_button_count == 0) {
		seatop_begin_default(seat);
	}
}