#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wlr_tablet_tool {struct sway_tablet_tool* data; } ;
struct wlr_event_tablet_tool_proximity {scalar_t__ state; int /*<<< orphan*/  time_msec; int /*<<< orphan*/  y; int /*<<< orphan*/  x; struct wlr_tablet_tool* tool; int /*<<< orphan*/  device; } ;
struct wl_listener {int dummy; } ;
struct sway_tablet_tool {int /*<<< orphan*/  tablet; int /*<<< orphan*/  tablet_v2_tool; } ;
struct sway_tablet {int dummy; } ;
struct sway_cursor {TYPE_1__* seat; } ;
struct TYPE_4__ {int /*<<< orphan*/  idle; } ;
struct TYPE_3__ {int /*<<< orphan*/  wlr_seat; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_ERROR ; 
 scalar_t__ WLR_TABLET_TOOL_PROXIMITY_OUT ; 
 struct sway_cursor* cursor ; 
 struct sway_tablet* get_tablet_for_device (struct sway_cursor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_tablet_tool_position (struct sway_cursor*,int /*<<< orphan*/ ,struct wlr_tablet_tool*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ server ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sway_tablet_tool_configure (struct sway_tablet*,struct wlr_tablet_tool*) ; 
 int /*<<< orphan*/  tool_proximity ; 
 struct sway_cursor* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_idle_notify_activity (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_tablet_v2_tablet_tool_notify_proximity_out (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_tool_proximity(struct wl_listener *listener, void *data) {
	struct sway_cursor *cursor = wl_container_of(listener, cursor, tool_proximity);
	wlr_idle_notify_activity(server.idle, cursor->seat->wlr_seat);
	struct wlr_event_tablet_tool_proximity *event = data;

	struct wlr_tablet_tool *tool = event->tool;
	if (!tool->data) {
		struct sway_tablet *tablet = get_tablet_for_device(cursor, event->device);
		if (!tablet) {
			sway_log(SWAY_ERROR, "no tablet for tablet tool");
			return;
		}
		sway_tablet_tool_configure(tablet, tool);
	}

	struct sway_tablet_tool *sway_tool = tool->data;
	if (!sway_tool) {
		sway_log(SWAY_ERROR, "tablet tool not initialized");
		return;
	}

	if (event->state == WLR_TABLET_TOOL_PROXIMITY_OUT) {
		wlr_tablet_v2_tablet_tool_notify_proximity_out(sway_tool->tablet_v2_tool);
		return;
	}

	handle_tablet_tool_position(cursor, sway_tool->tablet, event->tool,
		true, true, event->x, event->y, 0, 0, event->time_msec);
}