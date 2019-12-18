#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wlr_pointer_constraint_v1 {scalar_t__ type; int /*<<< orphan*/  surface; int /*<<< orphan*/  region; } ;
struct TYPE_5__ {double x; double y; } ;
struct sway_view {TYPE_1__ geometry; struct sway_container* container; } ;
struct sway_cursor {int /*<<< orphan*/  confine; TYPE_3__* cursor; struct wlr_pointer_constraint_v1* active_constraint; } ;
struct sway_container {double content_x; double content_y; } ;
typedef  int /*<<< orphan*/  pixman_region32_t ;
struct TYPE_6__ {int x1; int x2; int y1; int y2; } ;
typedef  TYPE_2__ pixman_box32_t ;
struct TYPE_7__ {double x; double y; } ;

/* Variables and functions */
 scalar_t__ WLR_POINTER_CONSTRAINT_V1_CONFINED ; 
 int /*<<< orphan*/  floor (double) ; 
 int /*<<< orphan*/  pixman_region32_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pixman_region32_contains_point (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pixman_region32_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* pixman_region32_rectangles (int /*<<< orphan*/ *,int*) ; 
 struct sway_view* view_from_wlr_surface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_cursor_warp_closest (TYPE_3__*,int /*<<< orphan*/ *,double,double) ; 

__attribute__((used)) static void check_constraint_region(struct sway_cursor *cursor) {
	struct wlr_pointer_constraint_v1 *constraint = cursor->active_constraint;
	pixman_region32_t *region = &constraint->region;
	struct sway_view *view = view_from_wlr_surface(constraint->surface);
	if (view) {
		struct sway_container *con = view->container;

		double sx = cursor->cursor->x - con->content_x + view->geometry.x;
		double sy = cursor->cursor->y - con->content_y + view->geometry.y;

		if (!pixman_region32_contains_point(region,
				floor(sx), floor(sy), NULL)) {
			int nboxes;
			pixman_box32_t *boxes = pixman_region32_rectangles(region, &nboxes);
			if (nboxes > 0) {
				double sx = (boxes[0].x1 + boxes[0].x2) / 2.;
				double sy = (boxes[0].y1 + boxes[0].y2) / 2.;

				wlr_cursor_warp_closest(cursor->cursor, NULL,
					sx + con->content_x - view->geometry.x,
					sy + con->content_y - view->geometry.y);
			}
		}
	}

	// A locked pointer will result in an empty region, thus disallowing all movement
	if (constraint->type == WLR_POINTER_CONSTRAINT_V1_CONFINED) {
		pixman_region32_copy(&cursor->confine, region);
	} else {
		pixman_region32_clear(&cursor->confine);
	}
}