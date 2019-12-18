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
struct wlr_surface {int dummy; } ;
struct sway_cursor {TYPE_2__* cursor; } ;
struct sway_container {scalar_t__ border; scalar_t__ border_thickness; scalar_t__ x; scalar_t__ y; scalar_t__ width; scalar_t__ height; TYPE_1__* view; } ;
typedef  enum wlr_edges { ____Placeholder_wlr_edges } wlr_edges ;
struct TYPE_4__ {scalar_t__ x; scalar_t__ y; } ;
struct TYPE_3__ {struct wlr_surface* surface; } ;

/* Variables and functions */
 scalar_t__ B_CSD ; 
 scalar_t__ B_NONE ; 
 int WLR_EDGE_BOTTOM ; 
 int WLR_EDGE_LEFT ; 
 int WLR_EDGE_NONE ; 
 int WLR_EDGE_RIGHT ; 
 int WLR_EDGE_TOP ; 

__attribute__((used)) static enum wlr_edges find_edge(struct sway_container *cont,
		struct wlr_surface *surface, struct sway_cursor *cursor) {
	if (!cont->view || (surface && cont->view->surface != surface)) {
		return WLR_EDGE_NONE;
	}
	if (cont->border == B_NONE || !cont->border_thickness ||
			cont->border == B_CSD) {
		return WLR_EDGE_NONE;
	}

	enum wlr_edges edge = 0;
	if (cursor->cursor->x < cont->x + cont->border_thickness) {
		edge |= WLR_EDGE_LEFT;
	}
	if (cursor->cursor->y < cont->y + cont->border_thickness) {
		edge |= WLR_EDGE_TOP;
	}
	if (cursor->cursor->x >= cont->x + cont->width - cont->border_thickness) {
		edge |= WLR_EDGE_RIGHT;
	}
	if (cursor->cursor->y >= cont->y + cont->height - cont->border_thickness) {
		edge |= WLR_EDGE_BOTTOM;
	}

	return edge;
}