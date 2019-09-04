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
struct wlr_box {int height; double y; int /*<<< orphan*/  width; int /*<<< orphan*/  x; } ;
struct sway_container {int height; double y; int /*<<< orphan*/  width; int /*<<< orphan*/  x; } ;
struct TYPE_3__ {int length; struct sway_container** items; } ;
typedef  TYPE_1__ list_t ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  container_add_gaps (struct sway_container*) ; 
 int /*<<< orphan*/  container_remove_gaps (struct sway_container*) ; 
 double floor (double) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,struct wlr_box*) ; 

__attribute__((used)) static void apply_vert_layout(list_t *children, struct wlr_box *parent) {
	if (!children->length) {
		return;
	}

	// Calculate total height of children
	double total_height = 0;
	for (int i = 0; i < children->length; ++i) {
		struct sway_container *child = children->items[i];
		if (child->height <= 0) {
			if (children->length > 1) {
				child->height = parent->height / (children->length - 1);
			} else {
				child->height = parent->height;
			}
		}
		container_remove_gaps(child);
		total_height += child->height;
	}
	double scale = parent->height / total_height;

	// Resize
	sway_log(SWAY_DEBUG, "Arranging %p vertically", parent);
	double child_y = parent->y;
	for (int i = 0; i < children->length; ++i) {
		struct sway_container *child = children->items[i];
		child->x = parent->x;
		child->y = child_y;
		child->width = parent->width;
		child->height = floor(child->height * scale);
		child_y += child->height;

		// Make last child use remaining height of parent
		if (i == children->length - 1) {
			child->height = parent->y + parent->height - child->y;
		}
		container_add_gaps(child);
	}
}