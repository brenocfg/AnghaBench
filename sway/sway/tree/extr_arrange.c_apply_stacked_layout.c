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
struct wlr_box {scalar_t__ height; int /*<<< orphan*/  width; scalar_t__ y; int /*<<< orphan*/  x; } ;
struct sway_container {scalar_t__ height; int /*<<< orphan*/  width; scalar_t__ y; int /*<<< orphan*/  x; scalar_t__ view; } ;
struct TYPE_3__ {int length; struct sway_container** items; } ;
typedef  TYPE_1__ list_t ;

/* Variables and functions */
 int container_titlebar_height () ; 

__attribute__((used)) static void apply_stacked_layout(list_t *children, struct wlr_box *parent) {
	if (!children->length) {
		return;
	}
	for (int i = 0; i < children->length; ++i) {
		struct sway_container *child = children->items[i];
		int parent_offset = child->view ?  0 :
			container_titlebar_height() * children->length;
		child->x = parent->x;
		child->y = parent->y + parent_offset;
		child->width = parent->width;
		child->height = parent->height - parent_offset;
	}
}