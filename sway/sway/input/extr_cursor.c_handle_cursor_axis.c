#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct wlr_event_pointer_axis {int dummy; } ;
struct wl_listener {int dummy; } ;
struct sway_cursor {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  axis ; 
 struct sway_cursor* cursor ; 
 int /*<<< orphan*/  cursor_handle_activity (struct sway_cursor*) ; 
 int /*<<< orphan*/  dispatch_cursor_axis (struct sway_cursor*,struct wlr_event_pointer_axis*) ; 
 int /*<<< orphan*/  transaction_commit_dirty () ; 
 struct sway_cursor* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_cursor_axis(struct wl_listener *listener, void *data) {
	struct sway_cursor *cursor = wl_container_of(listener, cursor, axis);
	struct wlr_event_pointer_axis *event = data;
	cursor_handle_activity(cursor);
	dispatch_cursor_axis(cursor, event);
	transaction_commit_dirty();
}