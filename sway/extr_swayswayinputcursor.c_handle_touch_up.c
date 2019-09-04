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
struct wlr_seat {int dummy; } ;
struct wlr_event_touch_up {int /*<<< orphan*/  touch_id; int /*<<< orphan*/  time_msec; } ;
struct wl_listener {int dummy; } ;
struct sway_cursor {TYPE_1__* seat; } ;
struct TYPE_4__ {int /*<<< orphan*/  idle; } ;
struct TYPE_3__ {struct wlr_seat* wlr_seat; } ;

/* Variables and functions */
 struct sway_cursor* cursor ; 
 TYPE_2__ server ; 
 int /*<<< orphan*/  touch_up ; 
 struct sway_cursor* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_idle_notify_activity (int /*<<< orphan*/ ,struct wlr_seat*) ; 
 int /*<<< orphan*/  wlr_seat_touch_notify_up (struct wlr_seat*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_touch_up(struct wl_listener *listener, void *data) {
	struct sway_cursor *cursor = wl_container_of(listener, cursor, touch_up);
	wlr_idle_notify_activity(server.idle, cursor->seat->wlr_seat);
	struct wlr_event_touch_up *event = data;
	struct wlr_seat *seat = cursor->seat->wlr_seat;
	// TODO: fall back to cursor simulation if client has not bound to touch
	wlr_seat_touch_notify_up(seat, event->time_msec, event->touch_id);
}