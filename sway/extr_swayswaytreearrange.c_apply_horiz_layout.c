#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wlr_box {int width; double x; int /*<<< orphan*/  height; int /*<<< orphan*/  y; } ;
struct sway_container {int width; double x; int /*<<< orphan*/  height; int /*<<< orphan*/  y; } ;
struct TYPE_3__ {int length; struct sway_container** items; } ;
typedef  TYPE_1__ list_t ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  container_add_gaps (struct sway_container*) ; 
 int /*<<< orphan*/  container_remove_gaps (struct sway_container*) ; 
 double floor (double) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,struct wlr_box*) ; 

__attribute__((used)) static void apply_horiz_layout(list_t *children, struct wlr_box *parent) {
	if (!children->length) {
		return;
	}

	// Calculate total width of children
	double total_width = 0;
	for (int i = 0; i < children->length; ++i) {
		struct sway_container *child = children->items[i];
		if (child->width <= 0) {
			if (children->length > 1) {
				child->width = parent->width / (children->length - 1);
			} else {
				child->width = parent->width;
			}
		}
		container_remove_gaps(child);
		total_width += child->width;
	}
	double scale = parent->width / total_width;

	// Resize windows
	sway_log(SWAY_DEBUG, "Arranging %p horizontally", parent);
	double child_x = parent->x;
	for (int i = 0; i < children->length; ++i) {
		struct sway_container *child = children->items[i];
		child->x = child_x;
		child->y = parent->y;
		child->width = floor(child->width * scale);
		child->height = parent->height;
		child_x += child->width;

		// Make last child use remaining width of parent
		if (i == children->length - 1) {
			child->width = parent->x + parent->width - child->x;
		}
		container_add_gaps(child);
	}
}