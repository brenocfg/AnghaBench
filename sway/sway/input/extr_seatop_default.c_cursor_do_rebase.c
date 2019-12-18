#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct wlr_surface {int dummy; } ;
struct wlr_seat {int dummy; } ;
struct sway_node {scalar_t__ type; int /*<<< orphan*/  sway_container; } ;
struct sway_cursor {TYPE_1__* seat; } ;
typedef  enum wlr_edges { ____Placeholder_wlr_edges } wlr_edges ;
struct TYPE_2__ {struct wlr_seat* wlr_seat; } ;

/* Variables and functions */
 scalar_t__ N_CONTAINER ; 
 int WLR_EDGE_LEFT ; 
 int WLR_EDGE_NONE ; 
 int WLR_EDGE_RIGHT ; 
 scalar_t__ container_is_floating (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cursor_set_image (struct sway_cursor*,char*,int /*<<< orphan*/ *) ; 
 int find_resize_edge (int /*<<< orphan*/ ,struct wlr_surface*,struct sway_cursor*) ; 
 scalar_t__ seat_is_input_allowed (TYPE_1__*,struct wlr_surface*) ; 
 int /*<<< orphan*/  wlr_seat_pointer_clear_focus (struct wlr_seat*) ; 
 int /*<<< orphan*/  wlr_seat_pointer_notify_enter (struct wlr_seat*,struct wlr_surface*,double,double) ; 
 char* wlr_xcursor_get_resize_name (int) ; 

__attribute__((used)) static void cursor_do_rebase(struct sway_cursor *cursor, uint32_t time_msec,
		struct sway_node *node, struct wlr_surface *surface,
		double sx, double sy) {
	struct wlr_seat *wlr_seat = cursor->seat->wlr_seat;
	if (surface) {
		if (seat_is_input_allowed(cursor->seat, surface)) {
			wlr_seat_pointer_notify_enter(wlr_seat, surface, sx, sy);
		}
	} else if (node && node->type == N_CONTAINER) {
		// Try a node's resize edge
		enum wlr_edges edge = find_resize_edge(node->sway_container, surface, cursor);
		if (edge == WLR_EDGE_NONE) {
			cursor_set_image(cursor, "left_ptr", NULL);
		} else if (container_is_floating(node->sway_container)) {
			cursor_set_image(cursor, wlr_xcursor_get_resize_name(edge), NULL);
		} else {
			if (edge & (WLR_EDGE_LEFT | WLR_EDGE_RIGHT)) {
				cursor_set_image(cursor, "col-resize", NULL);
			} else {
				cursor_set_image(cursor, "row-resize", NULL);
			}
		}
	} else {
		cursor_set_image(cursor, "left_ptr", NULL);
	}

	if (surface == NULL) {
		wlr_seat_pointer_clear_focus(wlr_seat);
	}
}