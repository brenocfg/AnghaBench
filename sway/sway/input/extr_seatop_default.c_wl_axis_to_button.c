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
struct wlr_event_pointer_axis {int orientation; int /*<<< orphan*/  delta; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  SWAY_SCROLL_DOWN ; 
 int /*<<< orphan*/  SWAY_SCROLL_LEFT ; 
 int /*<<< orphan*/  SWAY_SCROLL_RIGHT ; 
 int /*<<< orphan*/  SWAY_SCROLL_UP ; 
#define  WLR_AXIS_ORIENTATION_HORIZONTAL 129 
#define  WLR_AXIS_ORIENTATION_VERTICAL 128 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static uint32_t wl_axis_to_button(struct wlr_event_pointer_axis *event) {
	switch (event->orientation) {
	case WLR_AXIS_ORIENTATION_VERTICAL:
		return event->delta < 0 ? SWAY_SCROLL_UP : SWAY_SCROLL_DOWN;
	case WLR_AXIS_ORIENTATION_HORIZONTAL:
		return event->delta < 0 ? SWAY_SCROLL_LEFT : SWAY_SCROLL_RIGHT;
	default:
		sway_log(SWAY_DEBUG, "Unknown axis orientation");
		return 0;
	}
}