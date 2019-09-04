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
struct wlr_event_tablet_tool_tip {scalar_t__ state; int /*<<< orphan*/  time_msec; int /*<<< orphan*/  device; } ;
struct wl_listener {int dummy; } ;
struct sway_cursor {TYPE_1__* seat; } ;
struct TYPE_4__ {int /*<<< orphan*/  idle; } ;
struct TYPE_3__ {int /*<<< orphan*/  wlr_seat; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  WLR_BUTTON_PRESSED ; 
 int /*<<< orphan*/  WLR_BUTTON_RELEASED ; 
 scalar_t__ WLR_TABLET_TOOL_TIP_DOWN ; 
 struct sway_cursor* cursor ; 
 int /*<<< orphan*/  dispatch_cursor_button (struct sway_cursor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ server ; 
 int /*<<< orphan*/  tool_tip ; 
 int /*<<< orphan*/  transaction_commit_dirty () ; 
 struct sway_cursor* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_idle_notify_activity (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_seat_pointer_notify_frame (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_tool_tip(struct wl_listener *listener, void *data) {
	struct sway_cursor *cursor = wl_container_of(listener, cursor, tool_tip);
	wlr_idle_notify_activity(server.idle, cursor->seat->wlr_seat);
	struct wlr_event_tablet_tool_tip *event = data;
	dispatch_cursor_button(cursor, event->device, event->time_msec,
			BTN_LEFT, event->state == WLR_TABLET_TOOL_TIP_DOWN ?
				WLR_BUTTON_PRESSED : WLR_BUTTON_RELEASED);
	wlr_seat_pointer_notify_frame(cursor->seat->wlr_seat);
	transaction_commit_dirty();
}