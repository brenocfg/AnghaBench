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
struct wlr_event_pointer_axis {int dummy; } ;
struct sway_cursor {int /*<<< orphan*/  seat; } ;

/* Variables and functions */
 int /*<<< orphan*/  seatop_axis (int /*<<< orphan*/ ,struct wlr_event_pointer_axis*) ; 

void dispatch_cursor_axis(struct sway_cursor *cursor,
		struct wlr_event_pointer_axis *event) {
	seatop_axis(cursor->seat, event);
}