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
struct wlr_event_pointer_axis {int dummy; } ;
struct sway_seat {TYPE_1__* seatop_impl; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* axis ) (struct sway_seat*,struct wlr_event_pointer_axis*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct sway_seat*,struct wlr_event_pointer_axis*) ; 

void seatop_axis(struct sway_seat *seat, struct wlr_event_pointer_axis *event) {
	if (seat->seatop_impl->axis) {
		seat->seatop_impl->axis(seat, event);
	}
}