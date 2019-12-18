#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  link; } ;
struct TYPE_14__ {int /*<<< orphan*/  notify; } ;
struct TYPE_10__ {int /*<<< orphan*/  tablet_tool_button; int /*<<< orphan*/  tablet_tool_proximity; int /*<<< orphan*/  tablet_tool_tip; int /*<<< orphan*/  tablet_tool_axis; int /*<<< orphan*/  touch_motion; int /*<<< orphan*/  touch_up; int /*<<< orphan*/  touch_down; int /*<<< orphan*/  frame; int /*<<< orphan*/  axis; int /*<<< orphan*/  button; int /*<<< orphan*/  motion_absolute; int /*<<< orphan*/  motion; } ;
struct TYPE_9__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct wlr_cursor {struct wlr_cursor* cursor; int /*<<< orphan*/  tablet_pads; int /*<<< orphan*/  tablets; TYPE_5__ constraint_commit; TYPE_6__ request_set_cursor; TYPE_6__ tool_button; TYPE_2__ events; TYPE_6__ tool_proximity; TYPE_6__ tool_tip; TYPE_6__ tool_axis; TYPE_6__ touch_motion; TYPE_6__ touch_up; TYPE_6__ touch_down; TYPE_6__ frame; TYPE_6__ axis; TYPE_6__ button; TYPE_6__ motion_absolute; TYPE_6__ motion; int /*<<< orphan*/  hide_source; struct sway_seat* seat; int /*<<< orphan*/  y; TYPE_1__ previous; int /*<<< orphan*/  x; } ;
struct sway_seat {TYPE_4__* wlr_seat; } ;
struct sway_cursor {struct sway_cursor* cursor; int /*<<< orphan*/  tablet_pads; int /*<<< orphan*/  tablets; TYPE_5__ constraint_commit; TYPE_6__ request_set_cursor; TYPE_6__ tool_button; TYPE_2__ events; TYPE_6__ tool_proximity; TYPE_6__ tool_tip; TYPE_6__ tool_axis; TYPE_6__ touch_motion; TYPE_6__ touch_up; TYPE_6__ touch_down; TYPE_6__ frame; TYPE_6__ axis; TYPE_6__ button; TYPE_6__ motion_absolute; TYPE_6__ motion; int /*<<< orphan*/  hide_source; struct sway_seat* seat; int /*<<< orphan*/  y; TYPE_1__ previous; int /*<<< orphan*/  x; } ;
struct TYPE_16__ {int /*<<< orphan*/  output_layout; } ;
struct TYPE_15__ {int /*<<< orphan*/  wl_event_loop; } ;
struct TYPE_11__ {int /*<<< orphan*/  request_set_cursor; } ;
struct TYPE_12__ {TYPE_3__ events; } ;

/* Variables and functions */
 struct wlr_cursor* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct wlr_cursor*) ; 
 int /*<<< orphan*/  handle_cursor_axis ; 
 int /*<<< orphan*/  handle_cursor_button ; 
 int /*<<< orphan*/  handle_cursor_frame ; 
 int /*<<< orphan*/  handle_cursor_motion_absolute ; 
 int /*<<< orphan*/  handle_cursor_motion_relative ; 
 int /*<<< orphan*/  handle_request_set_cursor ; 
 int /*<<< orphan*/  handle_tool_axis ; 
 int /*<<< orphan*/  handle_tool_button ; 
 int /*<<< orphan*/  handle_tool_proximity ; 
 int /*<<< orphan*/  handle_tool_tip ; 
 int /*<<< orphan*/  handle_touch_down ; 
 int /*<<< orphan*/  handle_touch_motion ; 
 int /*<<< orphan*/  handle_touch_up ; 
 int /*<<< orphan*/  hide_notify ; 
 TYPE_8__* root ; 
 TYPE_7__ server ; 
 int /*<<< orphan*/  sway_assert (struct wlr_cursor*,char*) ; 
 int /*<<< orphan*/  wl_event_loop_add_timer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wlr_cursor*) ; 
 int /*<<< orphan*/  wl_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_signal_add (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  wlr_cursor_attach_output_layout (struct wlr_cursor*,int /*<<< orphan*/ ) ; 
 struct wlr_cursor* wlr_cursor_create () ; 

struct sway_cursor *sway_cursor_create(struct sway_seat *seat) {
	struct sway_cursor *cursor = calloc(1, sizeof(struct sway_cursor));
	if (!sway_assert(cursor, "could not allocate sway cursor")) {
		return NULL;
	}

	struct wlr_cursor *wlr_cursor = wlr_cursor_create();
	if (!sway_assert(wlr_cursor, "could not allocate wlr cursor")) {
		free(cursor);
		return NULL;
	}

	cursor->previous.x = wlr_cursor->x;
	cursor->previous.y = wlr_cursor->y;

	cursor->seat = seat;
	wlr_cursor_attach_output_layout(wlr_cursor, root->output_layout);

	cursor->hide_source = wl_event_loop_add_timer(server.wl_event_loop,
			hide_notify, cursor);

	// input events
	wl_signal_add(&wlr_cursor->events.motion, &cursor->motion);
	cursor->motion.notify = handle_cursor_motion_relative;

	wl_signal_add(&wlr_cursor->events.motion_absolute,
		&cursor->motion_absolute);
	cursor->motion_absolute.notify = handle_cursor_motion_absolute;

	wl_signal_add(&wlr_cursor->events.button, &cursor->button);
	cursor->button.notify = handle_cursor_button;

	wl_signal_add(&wlr_cursor->events.axis, &cursor->axis);
	cursor->axis.notify = handle_cursor_axis;

	wl_signal_add(&wlr_cursor->events.frame, &cursor->frame);
	cursor->frame.notify = handle_cursor_frame;

	wl_signal_add(&wlr_cursor->events.touch_down, &cursor->touch_down);
	cursor->touch_down.notify = handle_touch_down;

	wl_signal_add(&wlr_cursor->events.touch_up, &cursor->touch_up);
	cursor->touch_up.notify = handle_touch_up;

	wl_signal_add(&wlr_cursor->events.touch_motion,
		&cursor->touch_motion);
	cursor->touch_motion.notify = handle_touch_motion;

	wl_signal_add(&wlr_cursor->events.tablet_tool_axis,
		&cursor->tool_axis);
	cursor->tool_axis.notify = handle_tool_axis;

	wl_signal_add(&wlr_cursor->events.tablet_tool_tip, &cursor->tool_tip);
	cursor->tool_tip.notify = handle_tool_tip;

	wl_signal_add(&wlr_cursor->events.tablet_tool_proximity, &cursor->tool_proximity);
	cursor->tool_proximity.notify = handle_tool_proximity;

	wl_signal_add(&wlr_cursor->events.tablet_tool_button, &cursor->tool_button);
	cursor->tool_button.notify = handle_tool_button;

	wl_signal_add(&seat->wlr_seat->events.request_set_cursor,
			&cursor->request_set_cursor);
	cursor->request_set_cursor.notify = handle_request_set_cursor;

	wl_list_init(&cursor->constraint_commit.link);
	wl_list_init(&cursor->tablets);
	wl_list_init(&cursor->tablet_pads);

	cursor->cursor = wlr_cursor;

	return cursor;
}