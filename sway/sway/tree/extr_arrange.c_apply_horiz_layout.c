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
struct sway_workspace {double gaps_inner; } ;
struct sway_container {scalar_t__ width_fraction; double x; double width; int /*<<< orphan*/  height; int /*<<< orphan*/  y; struct sway_container* parent; struct sway_workspace* workspace; } ;
struct TYPE_3__ {int length; struct sway_container** items; } ;
typedef  TYPE_1__ list_t ;
typedef  enum sway_container_layout { ____Placeholder_sway_container_layout } sway_container_layout ;

/* Variables and functions */
 int L_STACKED ; 
 int L_TABBED ; 
 int MIN_SANE_W ; 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int container_parent_layout (struct sway_container*) ; 
 double floor (double) ; 
 int /*<<< orphan*/  fmax (int /*<<< orphan*/ ,int) ; 
 double fmin (double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,struct wlr_box*) ; 

__attribute__((used)) static void apply_horiz_layout(list_t *children, struct wlr_box *parent) {
	if (!children->length) {
		return;
	}

	// Count the number of new windows we are resizing, and how much space
	// is currently occupied
	int new_children = 0;
	double current_width_fraction = 0;
	for (int i = 0; i < children->length; ++i) {
		struct sway_container *child = children->items[i];
		current_width_fraction += child->width_fraction;
		if (child->width_fraction <= 0) {
			new_children += 1;
		}
	}

	// Calculate each height fraction
	double total_width_fraction = 0;
	for (int i = 0; i < children->length; ++i) {
		struct sway_container *child = children->items[i];
		if (child->width_fraction <= 0) {
			if (current_width_fraction <= 0) {
				child->width_fraction = 1.0;
			} else if (children->length > new_children) {
				child->width_fraction = current_width_fraction /
					(children->length - new_children);
			} else {
				child->width_fraction = current_width_fraction;
			}
		}
		total_width_fraction += child->width_fraction;
	}
	// Normalize width fractions so the sum is 1.0
	for (int i = 0; i < children->length; ++i) {
		struct sway_container *child = children->items[i];
		child->width_fraction /= total_width_fraction;
	}

	// Calculate gap size
	double inner_gap = 0;
	struct sway_container *child = children->items[0];
	struct sway_workspace *ws = child->workspace;
	if (ws) {
		inner_gap = ws->gaps_inner;
	}
	// Descendants of tabbed/stacked containers don't have gaps
	struct sway_container *temp = child;
	while (temp) {
		enum sway_container_layout layout = container_parent_layout(temp);
		if (layout == L_TABBED || layout == L_STACKED) {
			inner_gap = 0;
		}
		temp = temp->parent;
	}
	double total_gap = fmin(inner_gap * (children->length - 1),
		fmax(0, parent->width - MIN_SANE_W * children->length));
	double child_total_width = parent->width - total_gap;
	inner_gap = total_gap / (children->length - 1);

	// Resize windows
	sway_log(SWAY_DEBUG, "Arranging %p horizontally", parent);
	double child_x = parent->x;
	for (int i = 0; i < children->length; ++i) {
		struct sway_container *child = children->items[i];
		child->x = child_x;
		child->y = parent->y;
		child->width = floor(child->width_fraction * child_total_width);
		child->height = parent->height;
		child_x += child->width + inner_gap;

		// Make last child use remaining width of parent
		if (i == children->length - 1) {
			child->width = parent->x + parent->width - child->x;
		}
	}
}