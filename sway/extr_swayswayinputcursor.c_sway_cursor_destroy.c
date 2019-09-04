#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  link; } ;
struct TYPE_14__ {int /*<<< orphan*/  link; } ;
struct TYPE_13__ {int /*<<< orphan*/  link; } ;
struct TYPE_24__ {int /*<<< orphan*/  link; } ;
struct TYPE_23__ {int /*<<< orphan*/  link; } ;
struct TYPE_22__ {int /*<<< orphan*/  link; } ;
struct TYPE_21__ {int /*<<< orphan*/  link; } ;
struct TYPE_20__ {int /*<<< orphan*/  link; } ;
struct TYPE_19__ {int /*<<< orphan*/  link; } ;
struct TYPE_18__ {int /*<<< orphan*/  link; } ;
struct TYPE_17__ {int /*<<< orphan*/  link; } ;
struct TYPE_16__ {int /*<<< orphan*/  link; } ;
struct sway_cursor {int /*<<< orphan*/  cursor; int /*<<< orphan*/  xcursor_manager; TYPE_12__ request_set_cursor; TYPE_11__ tool_button; TYPE_10__ tool_tip; TYPE_9__ tool_axis; TYPE_8__ touch_motion; TYPE_7__ touch_up; TYPE_6__ touch_down; TYPE_5__ frame; TYPE_4__ axis; TYPE_3__ button; TYPE_2__ motion_absolute; TYPE_1__ motion; int /*<<< orphan*/  hide_source; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct sway_cursor*) ; 
 int /*<<< orphan*/  wl_event_source_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wlr_cursor_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_xcursor_manager_destroy (int /*<<< orphan*/ ) ; 

void sway_cursor_destroy(struct sway_cursor *cursor) {
	if (!cursor) {
		return;
	}

	wl_event_source_remove(cursor->hide_source);

	wl_list_remove(&cursor->motion.link);
	wl_list_remove(&cursor->motion_absolute.link);
	wl_list_remove(&cursor->button.link);
	wl_list_remove(&cursor->axis.link);
	wl_list_remove(&cursor->frame.link);
	wl_list_remove(&cursor->touch_down.link);
	wl_list_remove(&cursor->touch_up.link);
	wl_list_remove(&cursor->touch_motion.link);
	wl_list_remove(&cursor->tool_axis.link);
	wl_list_remove(&cursor->tool_tip.link);
	wl_list_remove(&cursor->tool_button.link);
	wl_list_remove(&cursor->request_set_cursor.link);

	wlr_xcursor_manager_destroy(cursor->xcursor_manager);
	wlr_cursor_destroy(cursor->cursor);
	free(cursor);
}