#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {double x; double y; } ;
struct TYPE_5__ {int committed; TYPE_1__ cursor_hint; } ;
struct wlr_pointer_constraint_v1 {int /*<<< orphan*/  surface; TYPE_2__ current; } ;
struct TYPE_6__ {double x; double y; } ;
struct sway_view {TYPE_3__ geometry; struct sway_container* container; } ;
struct sway_cursor {int /*<<< orphan*/  cursor; struct wlr_pointer_constraint_v1* active_constraint; } ;
struct sway_container {double content_x; double content_y; } ;

/* Variables and functions */
 int WLR_POINTER_CONSTRAINT_V1_STATE_CURSOR_HINT ; 
 struct sway_view* view_from_wlr_surface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_cursor_warp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,double,double) ; 

__attribute__((used)) static void warp_to_constraint_cursor_hint(struct sway_cursor *cursor) {
	struct wlr_pointer_constraint_v1 *constraint = cursor->active_constraint;

	if (constraint->current.committed &
			WLR_POINTER_CONSTRAINT_V1_STATE_CURSOR_HINT) {
		double sx = constraint->current.cursor_hint.x;
		double sy = constraint->current.cursor_hint.y;

		struct sway_view *view = view_from_wlr_surface(constraint->surface);
		struct sway_container *con = view->container;

		double lx = sx + con->content_x - view->geometry.x;
		double ly = sy + con->content_y - view->geometry.y;

		wlr_cursor_warp(cursor->cursor, NULL, lx, ly);
	}
}