#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wlr_tablet_tool {int type; struct sway_tablet_tool* data; } ;
struct wlr_surface {int dummy; } ;
struct sway_tablet_tool {int /*<<< orphan*/  tablet_v2_tool; } ;
struct sway_tablet {int /*<<< orphan*/  tablet_v2; TYPE_1__* seat_device; } ;
struct sway_seat {int dummy; } ;
struct sway_input_device {int /*<<< orphan*/  wlr_device; } ;
struct sway_cursor {TYPE_2__* cursor; struct sway_seat* seat; } ;
struct input_config {int /*<<< orphan*/ * mapped_from_region; } ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_5__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_4__ {struct sway_input_device* input_device; } ;

/* Variables and functions */
 double NAN ; 
#define  WLR_TABLET_TOOL_TYPE_MOUSE 128 
 int /*<<< orphan*/  apply_mapping_from_region (int /*<<< orphan*/ ,int /*<<< orphan*/ *,double*,double*) ; 
 int /*<<< orphan*/  cursor_motion (struct sway_cursor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,double,double,double) ; 
 struct input_config* input_device_get_config (struct sway_input_device*) ; 
 int /*<<< orphan*/  node_at_coords (struct sway_seat*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wlr_surface**,double*,double*) ; 
 int /*<<< orphan*/  wlr_cursor_move (TYPE_2__*,int /*<<< orphan*/ ,double,double) ; 
 int /*<<< orphan*/  wlr_cursor_warp_absolute (TYPE_2__*,int /*<<< orphan*/ ,double,double) ; 
 int /*<<< orphan*/  wlr_surface_accepts_tablet_v2 (int /*<<< orphan*/ ,struct wlr_surface*) ; 
 int /*<<< orphan*/  wlr_tablet_v2_tablet_tool_notify_motion (int /*<<< orphan*/ ,double,double) ; 
 int /*<<< orphan*/  wlr_tablet_v2_tablet_tool_notify_proximity_in (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wlr_surface*) ; 
 int /*<<< orphan*/  wlr_tablet_v2_tablet_tool_notify_proximity_out (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_tablet_tool_position(struct sway_cursor *cursor,
		struct sway_tablet *tablet,
		struct wlr_tablet_tool *tool,
		bool change_x, bool change_y,
		double x, double y, double dx, double dy,
		int32_t time_msec) {
	if (!change_x && !change_y) {
		return;
	}

	struct sway_input_device *input_device = tablet->seat_device->input_device;
	struct input_config *ic = input_device_get_config(input_device);
	if (ic != NULL && ic->mapped_from_region != NULL) {
		apply_mapping_from_region(input_device->wlr_device,
			ic->mapped_from_region, &x, &y);
	}

	switch (tool->type) {
	case WLR_TABLET_TOOL_TYPE_MOUSE:
		wlr_cursor_move(cursor->cursor, input_device->wlr_device, dx, dy);
		break;
	default:
		wlr_cursor_warp_absolute(cursor->cursor, input_device->wlr_device,
			change_x ? x : NAN, change_y ? y : NAN);
	}

	double sx, sy;
	struct wlr_surface *surface = NULL;
	struct sway_seat *seat = cursor->seat;
	node_at_coords(seat, cursor->cursor->x, cursor->cursor->y,
		&surface, &sx, &sy);
	struct sway_tablet_tool *sway_tool = tool->data;

	if (!surface || !wlr_surface_accepts_tablet_v2(tablet->tablet_v2, surface)) {
		wlr_tablet_v2_tablet_tool_notify_proximity_out(sway_tool->tablet_v2_tool);
		cursor_motion(cursor, time_msec, input_device->wlr_device, dx, dy, dx, dy);
		return;
	}

	wlr_tablet_v2_tablet_tool_notify_proximity_in(sway_tool->tablet_v2_tool,
		tablet->tablet_v2, surface);

	wlr_tablet_v2_tablet_tool_notify_motion(sway_tool->tablet_v2_tool, sx, sy);
}