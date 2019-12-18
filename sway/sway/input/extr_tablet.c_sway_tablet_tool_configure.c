#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  destroy; } ;
struct wlr_tablet_tool {struct sway_tablet_tool* data; TYPE_3__ events; } ;
struct TYPE_13__ {int /*<<< orphan*/  notify; } ;
struct sway_tablet_tool {TYPE_6__ set_cursor; TYPE_5__* tablet_v2_tool; TYPE_6__ tool_destroy; struct sway_tablet* tablet; TYPE_1__* seat; } ;
struct sway_tablet {TYPE_2__* seat_device; } ;
struct TYPE_14__ {int /*<<< orphan*/  tablet_v2; } ;
struct TYPE_11__ {int /*<<< orphan*/  set_cursor; } ;
struct TYPE_12__ {TYPE_4__ events; } ;
struct TYPE_9__ {TYPE_1__* sway_seat; } ;
struct TYPE_8__ {int /*<<< orphan*/  wlr_seat; } ;

/* Variables and functions */
 struct sway_tablet_tool* calloc (int,int) ; 
 int /*<<< orphan*/  handle_tablet_tool_destroy ; 
 int /*<<< orphan*/  handle_tablet_tool_set_cursor ; 
 TYPE_7__ server ; 
 int /*<<< orphan*/  sway_assert (struct sway_tablet_tool*,char*) ; 
 int /*<<< orphan*/  wl_signal_add (int /*<<< orphan*/ *,TYPE_6__*) ; 
 TYPE_5__* wlr_tablet_tool_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wlr_tablet_tool*) ; 

void sway_tablet_tool_configure(struct sway_tablet *tablet,
		struct wlr_tablet_tool *wlr_tool) {
	struct sway_tablet_tool *tool =
		calloc(1, sizeof(struct sway_tablet_tool));
	if (!sway_assert(tool, "could not allocate sway tablet tool for tablet")) {
		return;
	}

	tool->seat = tablet->seat_device->sway_seat;
	tool->tablet = tablet;
	tool->tablet_v2_tool =
		wlr_tablet_tool_create(server.tablet_v2,
			tablet->seat_device->sway_seat->wlr_seat, wlr_tool);

	tool->tool_destroy.notify = handle_tablet_tool_destroy;
	wl_signal_add(&wlr_tool->events.destroy, &tool->tool_destroy);

	tool->set_cursor.notify = handle_tablet_tool_set_cursor;
	wl_signal_add(&tool->tablet_v2_tool->events.set_cursor,
		&tool->set_cursor);

	wlr_tool->data = tool;
}