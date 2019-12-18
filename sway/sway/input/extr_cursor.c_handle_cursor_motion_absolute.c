#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wlr_event_pointer_motion_absolute {int /*<<< orphan*/  device; int /*<<< orphan*/  time_msec; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct wl_listener {int dummy; } ;
struct sway_cursor {TYPE_1__* cursor; } ;
struct TYPE_2__ {double x; double y; } ;

/* Variables and functions */
 struct sway_cursor* cursor ; 
 int /*<<< orphan*/  cursor_motion (struct sway_cursor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,double,double,double) ; 
 int /*<<< orphan*/  motion_absolute ; 
 int /*<<< orphan*/  transaction_commit_dirty () ; 
 struct sway_cursor* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_cursor_absolute_to_layout_coords (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double*,double*) ; 

__attribute__((used)) static void handle_cursor_motion_absolute(
		struct wl_listener *listener, void *data) {
	struct sway_cursor *cursor =
		wl_container_of(listener, cursor, motion_absolute);
	struct wlr_event_pointer_motion_absolute *event = data;

	double lx, ly;
	wlr_cursor_absolute_to_layout_coords(cursor->cursor, event->device,
			event->x, event->y, &lx, &ly);

	double dx = lx - cursor->cursor->x;
	double dy = ly - cursor->cursor->y;

	cursor_motion(cursor, event->time_msec, event->device, dx, dy, dx, dy);
	transaction_commit_dirty();
}