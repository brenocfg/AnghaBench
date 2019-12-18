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
struct wlr_event_tablet_tool_button {int state; scalar_t__ button; int /*<<< orphan*/  time_msec; int /*<<< orphan*/  device; TYPE_1__* tool; } ;
struct wl_listener {int dummy; } ;
struct sway_tablet_tool {int /*<<< orphan*/  tablet_v2_tool; TYPE_2__* tablet; } ;
struct sway_seat {int /*<<< orphan*/  wlr_seat; } ;
struct sway_cursor {int tool_buttons; struct sway_seat* seat; TYPE_3__* cursor; } ;
typedef  enum zwp_tablet_pad_v2_button_state { ____Placeholder_zwp_tablet_pad_v2_button_state } zwp_tablet_pad_v2_button_state ;
struct TYPE_8__ {int /*<<< orphan*/  idle; } ;
struct TYPE_7__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_6__ {struct wlr_tablet_v2_tablet* tablet_v2; } ;
struct TYPE_5__ {struct sway_tablet_tool* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  SWAY_DEBUG ; 
#define  WLR_BUTTON_PRESSED 129 
#define  WLR_BUTTON_RELEASED 128 
 struct sway_cursor* cursor ; 
 int /*<<< orphan*/  dispatch_cursor_button (struct sway_cursor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  node_at_coords (struct sway_seat*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wlr_surface**,double*,double*) ; 
 TYPE_4__ server ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tool_button ; 
 int /*<<< orphan*/  transaction_commit_dirty () ; 
 struct sway_cursor* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_idle_notify_activity (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_seat_pointer_notify_frame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_surface_accepts_tablet_v2 (struct wlr_tablet_v2_tablet*,struct wlr_surface*) ; 
 int /*<<< orphan*/  wlr_tablet_v2_tablet_tool_notify_button (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void handle_tool_button(struct wl_listener *listener, void *data) {
	struct sway_cursor *cursor = wl_container_of(listener, cursor, tool_button);
	wlr_idle_notify_activity(server.idle, cursor->seat->wlr_seat);
	struct wlr_event_tablet_tool_button *event = data;
	struct sway_tablet_tool *sway_tool = event->tool->data;
	struct wlr_tablet_v2_tablet *tablet_v2 = sway_tool->tablet->tablet_v2;
	struct sway_seat *seat = cursor->seat;

	if (!sway_tool) {
		sway_log(SWAY_DEBUG, "tool button before proximity");
		return;
	}

	double sx, sy;
	struct wlr_surface *surface = NULL;

	node_at_coords(seat, cursor->cursor->x, cursor->cursor->y,
		&surface, &sx, &sy);

	if (!surface || !wlr_surface_accepts_tablet_v2(tablet_v2, surface)) {
		// TODO: the user may want to configure which tool buttons are mapped to
		// which simulated pointer buttons
		switch (event->state) {
		case WLR_BUTTON_PRESSED:
			if (cursor->tool_buttons == 0) {
				dispatch_cursor_button(cursor, event->device,
						event->time_msec, BTN_RIGHT, event->state);
			}
			cursor->tool_buttons++;
			break;
		case WLR_BUTTON_RELEASED:
			if (cursor->tool_buttons == 1) {
				dispatch_cursor_button(cursor, event->device,
						event->time_msec, BTN_RIGHT, event->state);
			}
			cursor->tool_buttons--;
			break;
		}
		wlr_seat_pointer_notify_frame(cursor->seat->wlr_seat);
		transaction_commit_dirty();
		return;
	}

	wlr_tablet_v2_tablet_tool_notify_button(sway_tool->tablet_v2_tool,
		(enum zwp_tablet_pad_v2_button_state)event->button,
		(enum zwp_tablet_pad_v2_button_state)event->state);
}