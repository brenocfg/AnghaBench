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
struct wlr_event_tablet_tool_button {int state; int /*<<< orphan*/  time_msec; int /*<<< orphan*/  device; } ;
struct wl_listener {int dummy; } ;
struct sway_cursor {int tool_buttons; TYPE_1__* seat; } ;
struct TYPE_4__ {int /*<<< orphan*/  idle; } ;
struct TYPE_3__ {int /*<<< orphan*/  wlr_seat; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_RIGHT ; 
#define  WLR_BUTTON_PRESSED 129 
#define  WLR_BUTTON_RELEASED 128 
 struct sway_cursor* cursor ; 
 int /*<<< orphan*/  dispatch_cursor_button (struct sway_cursor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_2__ server ; 
 int /*<<< orphan*/  tool_button ; 
 int /*<<< orphan*/  transaction_commit_dirty () ; 
 struct sway_cursor* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_idle_notify_activity (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_seat_pointer_notify_frame (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_tool_button(struct wl_listener *listener, void *data) {
	struct sway_cursor *cursor = wl_container_of(listener, cursor, tool_button);
	wlr_idle_notify_activity(server.idle, cursor->seat->wlr_seat);
	struct wlr_event_tablet_tool_button *event = data;
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
}