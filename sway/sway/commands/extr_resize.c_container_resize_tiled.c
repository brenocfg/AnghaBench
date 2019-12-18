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
typedef  scalar_t__ uint32_t ;
struct sway_container {int width; double width_fraction; int height; double height_fraction; int /*<<< orphan*/  workspace; scalar_t__ parent; } ;
struct TYPE_3__ {int length; struct sway_container** items; } ;
typedef  TYPE_1__ list_t ;

/* Variables and functions */
 scalar_t__ AXIS_HORIZONTAL ; 
 scalar_t__ AXIS_VERTICAL ; 
 int MIN_SANE_H ; 
 int MIN_SANE_W ; 
 scalar_t__ WLR_EDGE_LEFT ; 
 scalar_t__ WLR_EDGE_TOP ; 
 int /*<<< orphan*/  arrange_container (scalar_t__) ; 
 int /*<<< orphan*/  arrange_workspace (int /*<<< orphan*/ ) ; 
 int ceil (double) ; 
 struct sway_container* container_find_resize_parent (struct sway_container*,scalar_t__) ; 
 TYPE_1__* container_get_siblings (struct sway_container*) ; 
 int container_sibling_index (struct sway_container*) ; 
 scalar_t__ is_horizontal (scalar_t__) ; 
 int /*<<< orphan*/  sway_assert (int,char*) ; 

void container_resize_tiled(struct sway_container *con,
		uint32_t axis, int amount) {
	if (!con) {
		return;
	}

	con = container_find_resize_parent(con, axis);
	if (!con) {
		// Can't resize in this direction
		return;
	}

	// For HORIZONTAL or VERTICAL, we are growing in two directions so select
	// both adjacent siblings. For RIGHT or DOWN, just select the next sibling.
	// For LEFT or UP, convert it to a RIGHT or DOWN resize and reassign con to
	// the previous sibling.
	struct sway_container *prev = NULL;
	struct sway_container *next = NULL;
	list_t *siblings = container_get_siblings(con);
	int index = container_sibling_index(con);

	if (axis == AXIS_HORIZONTAL || axis == AXIS_VERTICAL) {
		if (index == 0) {
			next = siblings->items[1];
		} else if (index == siblings->length - 1) {
			// Convert edge to top/left
			next = con;
			con = siblings->items[index - 1];
			amount = -amount;
		} else {
			prev = siblings->items[index - 1];
			next = siblings->items[index + 1];
		}
	} else if (axis == WLR_EDGE_TOP || axis == WLR_EDGE_LEFT) {
		if (!sway_assert(index > 0, "Didn't expect first child")) {
			return;
		}
		next = con;
		con = siblings->items[index - 1];
		amount = -amount;
	} else {
		if (!sway_assert(index < siblings->length - 1,
					"Didn't expect last child")) {
			return;
		}
		next = siblings->items[index + 1];
	}

	// Apply new dimensions
	int sibling_amount = prev ? ceil((double)amount / 2.0) : amount;

	if (is_horizontal(axis)) {
		if (con->width + amount < MIN_SANE_W) {
			return;
		}
		if (next->width - sibling_amount < MIN_SANE_W) {
			return;
		}
		if (prev && prev->width - sibling_amount < MIN_SANE_W) {
			return;
		}

		double amount_fraction =
			((double)amount / con->width) * con->width_fraction;
		double sibling_amount_fraction =
			prev ? amount_fraction / 2.0 : amount_fraction;

		con->width_fraction += amount_fraction;
		next->width_fraction -= sibling_amount_fraction;
		if (prev) {
			prev->width_fraction -= sibling_amount_fraction;
		}
	} else {
		if (con->height + amount < MIN_SANE_H) {
			return;
		}
		if (next->height - sibling_amount < MIN_SANE_H) {
			return;
		}
		if (prev && prev->height - sibling_amount < MIN_SANE_H) {
			return;
		}

		double amount_fraction =
			((double)amount / con->height) * con->height_fraction;
		double sibling_amount_fraction =
			prev ? amount_fraction / 2.0 : amount_fraction;

		con->height_fraction += amount_fraction;
		next->height_fraction -= sibling_amount_fraction;
		if (prev) {
			prev->height_fraction -= sibling_amount_fraction;
		}
	}

	if (con->parent) {
		arrange_container(con->parent);
	} else {
		arrange_workspace(con->workspace);
	}
}