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
struct wlr_surface {int dummy; } ;
struct wlr_box {double y; double height; int width; double x; } ;
struct sway_seat {int dummy; } ;
struct sway_node {int dummy; } ;
struct sway_container {int dummy; } ;
struct TYPE_3__ {int length; struct sway_container** items; } ;
typedef  TYPE_1__ list_t ;

/* Variables and functions */
 int container_titlebar_height () ; 
 struct sway_seat* input_manager_current_seat () ; 
 int /*<<< orphan*/  node_get_box (struct sway_node*,struct wlr_box*) ; 
 TYPE_1__* node_get_children (struct sway_node*) ; 
 struct sway_node* seat_get_active_tiling_child (struct sway_seat*,struct sway_node*) ; 
 struct sway_container* tiling_container_at (struct sway_node*,double,double,struct wlr_surface**,double*,double*) ; 

__attribute__((used)) static struct sway_container *container_at_tabbed(struct sway_node *parent,
		double lx, double ly,
		struct wlr_surface **surface, double *sx, double *sy) {
	struct wlr_box box;
	node_get_box(parent, &box);
	if (ly < box.y || ly > box.y + box.height) {
		return NULL;
	}
	struct sway_seat *seat = input_manager_current_seat();
	list_t *children = node_get_children(parent);
	if (!children->length) {
		return NULL;
	}

	// Tab titles
	int title_height = container_titlebar_height();
	if (ly < box.y + title_height) {
		int tab_width = box.width / children->length;
		int child_index = (lx - box.x) / tab_width;
		if (child_index >= children->length) {
			child_index = children->length - 1;
		}
		struct sway_container *child = children->items[child_index];
		return child;
	}

	// Surfaces
	struct sway_node *current = seat_get_active_tiling_child(seat, parent);
	return current ? tiling_container_at(current, lx, ly, surface, sx, sy) : NULL;
}