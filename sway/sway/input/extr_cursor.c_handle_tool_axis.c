#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wlr_event_tablet_tool_axis {int updated_axes; int /*<<< orphan*/  wheel_delta; int /*<<< orphan*/  slider; int /*<<< orphan*/  rotation; int /*<<< orphan*/  tilt_y; int /*<<< orphan*/  tilt_x; int /*<<< orphan*/  distance; int /*<<< orphan*/  pressure; int /*<<< orphan*/  time_msec; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; int /*<<< orphan*/  y; int /*<<< orphan*/  x; TYPE_3__* tool; } ;
struct wl_listener {int dummy; } ;
struct sway_tablet_tool {int /*<<< orphan*/  tablet_v2_tool; int /*<<< orphan*/  tilt_y; int /*<<< orphan*/  tilt_x; int /*<<< orphan*/  tablet; } ;
struct sway_cursor {TYPE_1__* seat; } ;
struct TYPE_6__ {struct sway_tablet_tool* data; } ;
struct TYPE_5__ {int /*<<< orphan*/  idle; } ;
struct TYPE_4__ {int /*<<< orphan*/  wlr_seat; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int WLR_TABLET_TOOL_AXIS_DISTANCE ; 
 int WLR_TABLET_TOOL_AXIS_PRESSURE ; 
 int WLR_TABLET_TOOL_AXIS_ROTATION ; 
 int WLR_TABLET_TOOL_AXIS_SLIDER ; 
 int WLR_TABLET_TOOL_AXIS_TILT_X ; 
 int WLR_TABLET_TOOL_AXIS_TILT_Y ; 
 int WLR_TABLET_TOOL_AXIS_WHEEL ; 
 int WLR_TABLET_TOOL_AXIS_X ; 
 int WLR_TABLET_TOOL_AXIS_Y ; 
 struct sway_cursor* cursor ; 
 int /*<<< orphan*/  handle_tablet_tool_position (struct sway_cursor*,int /*<<< orphan*/ ,TYPE_3__*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ server ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tool_axis ; 
 struct sway_cursor* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_idle_notify_activity (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_tablet_v2_tablet_tool_notify_distance (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_tablet_v2_tablet_tool_notify_pressure (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_tablet_v2_tablet_tool_notify_rotation (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_tablet_v2_tablet_tool_notify_slider (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_tablet_v2_tablet_tool_notify_tilt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_tablet_v2_tablet_tool_notify_wheel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_tool_axis(struct wl_listener *listener, void *data) {
	struct sway_cursor *cursor = wl_container_of(listener, cursor, tool_axis);
	wlr_idle_notify_activity(server.idle, cursor->seat->wlr_seat);
	struct wlr_event_tablet_tool_axis *event = data;
	struct sway_tablet_tool *sway_tool = event->tool->data;

	if (!sway_tool) {
		sway_log(SWAY_DEBUG, "tool axis before proximity");
		return;
	}

	handle_tablet_tool_position(cursor, sway_tool->tablet, event->tool,
		event->updated_axes & WLR_TABLET_TOOL_AXIS_X,
		event->updated_axes & WLR_TABLET_TOOL_AXIS_Y,
		event->x, event->y, event->dx, event->dy, event->time_msec);

	if (event->updated_axes & WLR_TABLET_TOOL_AXIS_PRESSURE) {
		wlr_tablet_v2_tablet_tool_notify_pressure(
			sway_tool->tablet_v2_tool, event->pressure);
	}

	if (event->updated_axes & WLR_TABLET_TOOL_AXIS_DISTANCE) {
		wlr_tablet_v2_tablet_tool_notify_distance(
			sway_tool->tablet_v2_tool, event->distance);
	}

	if (event->updated_axes & WLR_TABLET_TOOL_AXIS_TILT_X) {
		sway_tool->tilt_x = event->tilt_x;
	}

	if (event->updated_axes & WLR_TABLET_TOOL_AXIS_TILT_Y) {
		sway_tool->tilt_y = event->tilt_y;
	}

	if (event->updated_axes & (WLR_TABLET_TOOL_AXIS_TILT_X | WLR_TABLET_TOOL_AXIS_TILT_Y)) {
		wlr_tablet_v2_tablet_tool_notify_tilt(
			sway_tool->tablet_v2_tool,
			sway_tool->tilt_x, sway_tool->tilt_y);
	}

	if (event->updated_axes & WLR_TABLET_TOOL_AXIS_ROTATION) {
		wlr_tablet_v2_tablet_tool_notify_rotation(
			sway_tool->tablet_v2_tool, event->rotation);
	}

	if (event->updated_axes & WLR_TABLET_TOOL_AXIS_SLIDER) {
		wlr_tablet_v2_tablet_tool_notify_slider(
			sway_tool->tablet_v2_tool, event->slider);
	}

	if (event->updated_axes & WLR_TABLET_TOOL_AXIS_WHEEL) {
		wlr_tablet_v2_tablet_tool_notify_wheel(
			sway_tool->tablet_v2_tool, event->wheel_delta, 0);
	}
}