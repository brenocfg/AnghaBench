#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct wlr_event_tablet_tool_axis {int updated_axes; double x; double y; TYPE_3__* device; int /*<<< orphan*/  time_msec; } ;
struct wl_listener {int dummy; } ;
struct sway_input_device {int dummy; } ;
struct sway_cursor {TYPE_1__* seat; TYPE_2__* cursor; } ;
struct input_config {int /*<<< orphan*/ * mapped_from_region; } ;
struct TYPE_10__ {int /*<<< orphan*/  idle; } ;
struct TYPE_9__ {struct sway_input_device* data; } ;
struct TYPE_8__ {double x; double y; } ;
struct TYPE_7__ {int /*<<< orphan*/  wlr_seat; } ;

/* Variables and functions */
 double NAN ; 
 int WLR_TABLET_TOOL_AXIS_X ; 
 int WLR_TABLET_TOOL_AXIS_Y ; 
 int /*<<< orphan*/  apply_mapping_from_region (TYPE_3__*,int /*<<< orphan*/ *,double*,double*) ; 
 struct sway_cursor* cursor ; 
 int /*<<< orphan*/  cursor_motion (struct sway_cursor*,int /*<<< orphan*/ ,TYPE_3__*,double,double,double,double) ; 
 struct input_config* input_device_get_config (struct sway_input_device*) ; 
 TYPE_4__ server ; 
 int /*<<< orphan*/  tool_axis ; 
 int /*<<< orphan*/  transaction_commit_dirty () ; 
 struct sway_cursor* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_cursor_absolute_to_layout_coords (TYPE_2__*,TYPE_3__*,double,double,double*,double*) ; 
 int /*<<< orphan*/  wlr_idle_notify_activity (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_seat_pointer_notify_frame (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_tool_axis(struct wl_listener *listener, void *data) {
	struct sway_cursor *cursor = wl_container_of(listener, cursor, tool_axis);
	wlr_idle_notify_activity(server.idle, cursor->seat->wlr_seat);
	struct wlr_event_tablet_tool_axis *event = data;
	struct sway_input_device *input_device = event->device->data;

	double x = NAN, y = NAN;
	if ((event->updated_axes & WLR_TABLET_TOOL_AXIS_X)) {
		x = event->x;
	}
	if ((event->updated_axes & WLR_TABLET_TOOL_AXIS_Y)) {
		y = event->y;
	}

	struct input_config *ic = input_device_get_config(input_device);
	if (ic != NULL && ic->mapped_from_region != NULL) {
		apply_mapping_from_region(event->device, ic->mapped_from_region, &x, &y);
	}

	double lx, ly;
	wlr_cursor_absolute_to_layout_coords(cursor->cursor, event->device,
			x, y, &lx, &ly);

	double dx = lx - cursor->cursor->x;
	double dy = ly - cursor->cursor->y;

	cursor_motion(cursor, event->time_msec, event->device, dx, dy, dx, dy);
	wlr_seat_pointer_notify_frame(cursor->seat->wlr_seat);
	transaction_commit_dirty();
}