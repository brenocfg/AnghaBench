#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wlr_surface {int dummy; } ;
struct wlr_box {scalar_t__ y; scalar_t__ height; scalar_t__ x; scalar_t__ width; } ;
struct sway_seat {struct sway_cursor* cursor; struct seatop_move_tiling_event* seatop_data; } ;
struct sway_node {scalar_t__ type; scalar_t__ sway_workspace; struct sway_container* sway_container; } ;
struct sway_cursor {TYPE_1__* cursor; } ;
struct sway_container {scalar_t__ workspace; scalar_t__ content_width; scalar_t__ content_height; size_t y; size_t x; size_t width; size_t height; scalar_t__ content_x; scalar_t__ content_y; TYPE_2__* view; struct sway_container* parent; struct sway_node node; } ;
struct seatop_move_tiling_event {int target_edge; struct wlr_box drop_box; struct sway_node* target_node; TYPE_3__* con; } ;
typedef  enum wlr_edges { ____Placeholder_wlr_edges } wlr_edges ;
typedef  enum sway_container_layout { ____Placeholder_sway_container_layout } sway_container_layout ;
struct TYPE_6__ {scalar_t__ workspace; struct sway_node node; } ;
struct TYPE_5__ {int /*<<< orphan*/  surface; } ;
struct TYPE_4__ {size_t x; size_t y; } ;

/* Variables and functions */
 scalar_t__ DROP_LAYOUT_BORDER ; 
 size_t INT_MAX ; 
 int L_HORIZ ; 
 int L_STACKED ; 
 int L_TABBED ; 
 int L_VERT ; 
 scalar_t__ N_WORKSPACE ; 
 void* WLR_EDGE_BOTTOM ; 
 void* WLR_EDGE_LEFT ; 
 void* WLR_EDGE_NONE ; 
 void* WLR_EDGE_RIGHT ; 
 void* WLR_EDGE_TOP ; 
 int /*<<< orphan*/  container_get_box (struct sway_container*,struct wlr_box*) ; 
 int container_parent_layout (struct sway_container*) ; 
 int /*<<< orphan*/  desktop_damage_box (struct wlr_box*) ; 
 double fmin (scalar_t__,scalar_t__) ; 
 struct sway_node* node_at_coords (struct sway_seat*,size_t,size_t,struct wlr_surface**,double*,double*) ; 
 int /*<<< orphan*/  node_get_box (struct sway_node*,struct wlr_box*) ; 
 void* node_get_parent (struct sway_node*) ; 
 scalar_t__ node_has_ancestor (struct sway_node*,struct sway_node*) ; 
 int /*<<< orphan*/  resize_box (struct wlr_box*,int,size_t) ; 
 int /*<<< orphan*/  workspace_get_box (scalar_t__,struct wlr_box*) ; 
 int workspace_num_tiling_views (scalar_t__) ; 

__attribute__((used)) static void handle_motion_postthreshold(struct sway_seat *seat) {
	struct seatop_move_tiling_event *e = seat->seatop_data;
	struct wlr_surface *surface = NULL;
	double sx, sy;
	struct sway_cursor *cursor = seat->cursor;
	struct sway_node *node = node_at_coords(seat,
			cursor->cursor->x, cursor->cursor->y, &surface, &sx, &sy);
	// Damage the old location
	desktop_damage_box(&e->drop_box);

	if (!node) {
		// Eg. hovered over a layer surface such as swaybar
		e->target_node = NULL;
		e->target_edge = WLR_EDGE_NONE;
		return;
	}

	if (node->type == N_WORKSPACE) {
		// Empty workspace
		e->target_node = node;
		e->target_edge = WLR_EDGE_NONE;
		workspace_get_box(node->sway_workspace, &e->drop_box);
		desktop_damage_box(&e->drop_box);
		return;
	}

	// Deny moving within own workspace if this is the only child
	struct sway_container *con = node->sway_container;
	if (workspace_num_tiling_views(e->con->workspace) == 1 &&
			con->workspace == e->con->workspace) {
		e->target_node = NULL;
		e->target_edge = WLR_EDGE_NONE;
		return;
	}

	// Traverse the ancestors, trying to find a layout container perpendicular
	// to the edge. Eg. close to the top or bottom of a horiz layout.
	while (con) {
		enum wlr_edges edge = WLR_EDGE_NONE;
		enum sway_container_layout layout = container_parent_layout(con);
		struct wlr_box parent;
		con->parent ? container_get_box(con->parent, &parent) :
			workspace_get_box(con->workspace, &parent);
		if (layout == L_HORIZ || layout == L_TABBED) {
			if (cursor->cursor->y < parent.y + DROP_LAYOUT_BORDER) {
				edge = WLR_EDGE_TOP;
			} else if (cursor->cursor->y > parent.y + parent.height
					- DROP_LAYOUT_BORDER) {
				edge = WLR_EDGE_BOTTOM;
			}
		} else if (layout == L_VERT || layout == L_STACKED) {
			if (cursor->cursor->x < parent.x + DROP_LAYOUT_BORDER) {
				edge = WLR_EDGE_LEFT;
			} else if (cursor->cursor->x > parent.x + parent.width
					- DROP_LAYOUT_BORDER) {
				edge = WLR_EDGE_RIGHT;
			}
		}
		if (edge) {
			e->target_node = node_get_parent(&con->node);
			if (e->target_node == &e->con->node) {
				e->target_node = node_get_parent(e->target_node);
			}
			e->target_edge = edge;
			node_get_box(e->target_node, &e->drop_box);
			resize_box(&e->drop_box, edge, DROP_LAYOUT_BORDER);
			desktop_damage_box(&e->drop_box);
			return;
		}
		con = con->parent;
	}

	// Use the hovered view - but we must be over the actual surface
	con = node->sway_container;
	if (!con->view || !con->view->surface || node == &e->con->node
			|| node_has_ancestor(node, &e->con->node)) {
		e->target_node = NULL;
		e->target_edge = WLR_EDGE_NONE;
		return;
	}

	// Find the closest edge
	size_t thickness = fmin(con->content_width, con->content_height) * 0.3;
	size_t closest_dist = INT_MAX;
	size_t dist;
	e->target_edge = WLR_EDGE_NONE;
	if ((dist = cursor->cursor->y - con->y) < closest_dist) {
		closest_dist = dist;
		e->target_edge = WLR_EDGE_TOP;
	}
	if ((dist = cursor->cursor->x - con->x) < closest_dist) {
		closest_dist = dist;
		e->target_edge = WLR_EDGE_LEFT;
	}
	if ((dist = con->x + con->width - cursor->cursor->x) < closest_dist) {
		closest_dist = dist;
		e->target_edge = WLR_EDGE_RIGHT;
	}
	if ((dist = con->y + con->height - cursor->cursor->y) < closest_dist) {
		closest_dist = dist;
		e->target_edge = WLR_EDGE_BOTTOM;
	}

	if (closest_dist > thickness) {
		e->target_edge = WLR_EDGE_NONE;
	}

	e->target_node = node;
	e->drop_box.x = con->content_x;
	e->drop_box.y = con->content_y;
	e->drop_box.width = con->content_width;
	e->drop_box.height = con->content_height;
	resize_box(&e->drop_box, e->target_edge, thickness);
	desktop_damage_box(&e->drop_box);
}