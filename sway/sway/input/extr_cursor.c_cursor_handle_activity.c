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
struct sway_cursor {scalar_t__ hidden; TYPE_1__* seat; int /*<<< orphan*/  hide_source; } ;
struct TYPE_4__ {int /*<<< orphan*/  idle; } ;
struct TYPE_3__ {int /*<<< orphan*/  wlr_seat; } ;

/* Variables and functions */
 int /*<<< orphan*/  cursor_get_timeout (struct sway_cursor*) ; 
 int /*<<< orphan*/  cursor_unhide (struct sway_cursor*) ; 
 TYPE_2__ server ; 
 int /*<<< orphan*/  wl_event_source_timer_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_idle_notify_activity (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cursor_handle_activity(struct sway_cursor *cursor) {
	wl_event_source_timer_update(
			cursor->hide_source, cursor_get_timeout(cursor));

	wlr_idle_notify_activity(server.idle, cursor->seat->wlr_seat);
	if (cursor->hidden) {
		cursor_unhide(cursor);
	}
}