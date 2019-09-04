#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sway_container {scalar_t__ border; int border_thickness; int /*<<< orphan*/  node; scalar_t__ content_height; scalar_t__ height; scalar_t__ content_width; scalar_t__ width; scalar_t__ content_y; scalar_t__ y; scalar_t__ content_x; scalar_t__ x; int /*<<< orphan*/  view; } ;

/* Variables and functions */
 scalar_t__ B_CSD ; 
 scalar_t__ B_NONE ; 
 scalar_t__ B_NORMAL ; 
 int /*<<< orphan*/  container_is_floating (struct sway_container*) ; 
 size_t container_titlebar_height () ; 
 int /*<<< orphan*/  node_set_dirty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sway_assert (int /*<<< orphan*/ ,char*) ; 

void container_set_geometry_from_content(struct sway_container *con) {
	if (!sway_assert(con->view, "Expected a view")) {
		return;
	}
	if (!sway_assert(container_is_floating(con), "Expected a floating view")) {
		return;
	}
	size_t border_width = 0;
	size_t top = 0;

	if (con->border != B_CSD) {
		border_width = con->border_thickness * (con->border != B_NONE);
		top = con->border == B_NORMAL ?
			container_titlebar_height() : border_width;
	}

	con->x = con->content_x - border_width;
	con->y = con->content_y - top;
	con->width = con->content_width + border_width * 2;
	con->height = top + con->content_height + border_width;
	node_set_dirty(&con->node);
}