#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wlr_tablet_v2_tablet {int dummy; } ;
struct wlr_surface {int dummy; } ;
struct wlr_event_tablet_tool_tip {scalar_t__ state; int /*<<< orphan*/  time_msec; int /*<<< orphan*/  device; TYPE_1__* tool; } ;
struct wl_listener {int dummy; } ;
struct sway_tablet_tool {int /*<<< orphan*/  tablet_v2_tool; TYPE_2__* tablet; } ;
struct sway_seat {int /*<<< orphan*/  wlr_seat; } ;
struct sway_cursor {struct sway_seat* seat; TYPE_3__* cursor; } ;
struct TYPE_8__ {int /*<<< orphan*/  idle; } ;
struct TYPE_7__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_6__ {struct wlr_tablet_v2_tablet* tablet_v2; } ;
struct TYPE_5__ {struct sway_tablet_tool* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  WLR_BUTTON_PRESSED ; 
 int /*<<< orphan*/  WLR_BUTTON_RELEASED ; 
 scalar_t__ WLR_TABLET_TOOL_TIP_DOWN ; 
 struct sway_cursor* cursor ; 
 int /*<<< orphan*/  dispatch_cursor_button (struct sway_cursor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  node_at_coords (struct sway_seat*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wlr_surface**,double*,double*) ; 
 TYPE_4__ server ; 
 int /*<<< orphan*/  tool_tip ; 
 int /*<<< orphan*/  transaction_commit_dirty () ; 
 struct sway_cursor* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_idle_notify_activity (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_seat_pointer_notify_frame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_surface_accepts_tablet_v2 (struct wlr_tablet_v2_tablet*,struct wlr_surface*) ; 
 int /*<<< orphan*/  wlr_tablet_tool_v2_start_implicit_grab (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_tablet_v2_tablet_tool_notify_down (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_tablet_v2_tablet_tool_notify_up (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_tool_tip(struct wl_listener *listener, void *data) {
	struct sway_cursor *cursor = wl_container_of(listener, cursor, tool_tip);
	wlr_idle_notify_activity(server.idle, cursor->seat->wlr_seat);
	struct wlr_event_tablet_tool_tip *event = data;
	struct sway_tablet_tool *sway_tool = event->tool->data;
	struct wlr_tablet_v2_tablet *tablet_v2 = sway_tool->tablet->tablet_v2;
	struct sway_seat *seat = cursor->seat;

	double sx, sy;
	struct wlr_surface *surface = NULL;
	node_at_coords(seat, cursor->cursor->x, cursor->cursor->y,
		&surface, &sx, &sy);

	if (!surface || !wlr_surface_accepts_tablet_v2(tablet_v2, surface)) {
		dispatch_cursor_button(cursor, event->device, event->time_msec,
				BTN_LEFT, event->state == WLR_TABLET_TOOL_TIP_DOWN ?
					WLR_BUTTON_PRESSED : WLR_BUTTON_RELEASED);
		wlr_seat_pointer_notify_frame(cursor->seat->wlr_seat);
		transaction_commit_dirty();
		return;
	}

	if (event->state == WLR_TABLET_TOOL_TIP_DOWN) {
		wlr_tablet_v2_tablet_tool_notify_down(sway_tool->tablet_v2_tool);
		wlr_tablet_tool_v2_start_implicit_grab(sway_tool->tablet_v2_tool);
	} else {
		wlr_tablet_v2_tablet_tool_notify_up(sway_tool->tablet_v2_tool);
	}
}