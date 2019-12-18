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
struct wlr_touch_point {int dummy; } ;
struct wlr_drag_icon {TYPE_2__* drag; } ;
struct wlr_cursor {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct sway_seat {int /*<<< orphan*/  touch_y; int /*<<< orphan*/  touch_x; int /*<<< orphan*/  wlr_seat; TYPE_1__* cursor; } ;
struct sway_drag_icon {int /*<<< orphan*/  y; int /*<<< orphan*/  x; struct sway_seat* seat; struct wlr_drag_icon* wlr_drag_icon; } ;
struct TYPE_4__ {int grab_type; int /*<<< orphan*/  touch_id; } ;
struct TYPE_3__ {struct wlr_cursor* cursor; } ;

/* Variables and functions */
#define  WLR_DRAG_GRAB_KEYBOARD 130 
#define  WLR_DRAG_GRAB_KEYBOARD_POINTER 129 
#define  WLR_DRAG_GRAB_KEYBOARD_TOUCH 128 
 int /*<<< orphan*/  drag_icon_damage_whole (struct sway_drag_icon*) ; 
 struct wlr_touch_point* wlr_seat_touch_get_point (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void drag_icon_update_position(struct sway_drag_icon *icon) {
	drag_icon_damage_whole(icon);

	struct wlr_drag_icon *wlr_icon = icon->wlr_drag_icon;
	struct sway_seat *seat = icon->seat;
	struct wlr_cursor *cursor = seat->cursor->cursor;
	switch (wlr_icon->drag->grab_type) {
	case WLR_DRAG_GRAB_KEYBOARD:
		return;
	case WLR_DRAG_GRAB_KEYBOARD_POINTER:
		icon->x = cursor->x;
		icon->y = cursor->y;
		break;
	case WLR_DRAG_GRAB_KEYBOARD_TOUCH:;
		struct wlr_touch_point *point =
			wlr_seat_touch_get_point(seat->wlr_seat, wlr_icon->drag->touch_id);
		if (point == NULL) {
			return;
		}
		icon->x = seat->touch_x;
		icon->y = seat->touch_y;
	}

	drag_icon_damage_whole(icon);
}