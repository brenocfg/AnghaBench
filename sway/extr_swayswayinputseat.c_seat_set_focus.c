#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wlr_layer_surface_v1 {int dummy; } ;
struct sway_workspace {TYPE_1__* floating; int /*<<< orphan*/  node; struct sway_output* output; struct sway_container* fullscreen; } ;
struct sway_view {scalar_t__ urgent_timer; } ;
struct sway_seat {int has_focus; struct wlr_layer_surface_v1* focused_layer; } ;
struct sway_node {scalar_t__ type; struct sway_container* sway_container; struct sway_workspace* sway_workspace; } ;
struct sway_output {struct sway_node node; } ;
struct sway_container {struct sway_view* view; scalar_t__ is_sticky; int /*<<< orphan*/  node; struct sway_container* parent; struct sway_workspace* workspace; } ;
struct TYPE_8__ {scalar_t__ urgent_timeout; scalar_t__ smart_gaps; } ;
struct TYPE_7__ {struct sway_container* fullscreen_global; } ;
struct TYPE_6__ {int /*<<< orphan*/  wl_event_loop; } ;
struct TYPE_5__ {int length; struct sway_container** items; } ;

/* Variables and functions */
 scalar_t__ N_CONTAINER ; 
 scalar_t__ N_WORKSPACE ; 
 int /*<<< orphan*/  SWAY_ERROR ; 
 int /*<<< orphan*/  arrange_workspace (struct sway_workspace*) ; 
 TYPE_4__* config ; 
 int /*<<< orphan*/  container_detach (struct sway_container*) ; 
 int /*<<< orphan*/  container_has_ancestor (struct sway_container*,struct sway_container*) ; 
 int /*<<< orphan*/  container_is_fullscreen_or_child (struct sway_container*) ; 
 int /*<<< orphan*/  container_is_transient_for (struct sway_container*,struct sway_container*) ; 
 int /*<<< orphan*/  handle_urgent_timeout (struct sway_view*) ; 
 int /*<<< orphan*/  ipc_event_window (struct sway_container*,char*) ; 
 struct sway_node* node_get_parent (struct sway_node*) ; 
 scalar_t__ node_is_view (struct sway_node*) ; 
 int /*<<< orphan*/  node_set_dirty (struct sway_node*) ; 
 struct sway_workspace* output_get_active_workspace (struct sway_output*) ; 
 TYPE_3__* root ; 
 struct sway_node* seat_get_focus (struct sway_seat*) ; 
 struct sway_workspace* seat_get_focused_workspace (struct sway_seat*) ; 
 int /*<<< orphan*/  seat_send_focus (int /*<<< orphan*/ *,struct sway_seat*) ; 
 int /*<<< orphan*/  seat_send_unfocus (struct sway_node*,struct sway_seat*) ; 
 int /*<<< orphan*/  seat_set_focus_layer (struct sway_seat*,struct wlr_layer_surface_v1*) ; 
 int /*<<< orphan*/  seat_set_raw_focus (struct sway_seat*,int /*<<< orphan*/ *) ; 
 TYPE_2__ server ; 
 int /*<<< orphan*/  set_workspace (struct sway_seat*,struct sway_workspace*) ; 
 int /*<<< orphan*/  sway_log_errno (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  view_close_popups (struct sway_view*) ; 
 scalar_t__ view_is_urgent (struct sway_view*) ; 
 int /*<<< orphan*/  view_set_urgent (struct sway_view*,int) ; 
 scalar_t__ wl_event_loop_add_timer (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (struct sway_view*),struct sway_view*) ; 
 int /*<<< orphan*/  wl_event_source_timer_update (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  workspace_add_floating (struct sway_workspace*,struct sway_container*) ; 
 int /*<<< orphan*/  workspace_consider_destroy (struct sway_workspace*) ; 

void seat_set_focus(struct sway_seat *seat, struct sway_node *node) {
	if (seat->focused_layer) {
		struct wlr_layer_surface_v1 *layer = seat->focused_layer;
		seat_set_focus_layer(seat, NULL);
		seat_set_focus(seat, node);
		seat_set_focus_layer(seat, layer);
		return;
	}

	struct sway_node *last_focus = seat_get_focus(seat);
	if (last_focus == node) {
		return;
	}

	struct sway_workspace *last_workspace = seat_get_focused_workspace(seat);

	if (node == NULL) {
		// Close any popups on the old focus
		if (node_is_view(last_focus)) {
			view_close_popups(last_focus->sway_container->view);
		}
		seat_send_unfocus(last_focus, seat);
		seat->has_focus = false;
		return;
	}

	struct sway_workspace *new_workspace = node->type == N_WORKSPACE ?
		node->sway_workspace : node->sway_container->workspace;
	struct sway_container *container = node->type == N_CONTAINER ?
		node->sway_container : NULL;

	// Deny setting focus to a view which is hidden by a fullscreen container
	if (new_workspace && new_workspace->fullscreen && container &&
			!container_is_fullscreen_or_child(container)) {
		// Unless it's a transient container
		if (!container_is_transient_for(container, new_workspace->fullscreen)) {
			return;
		}
	}
	// Deny setting focus to a workspace node when using fullscreen global
	if (root->fullscreen_global && !container && new_workspace) {
		return;
	}
	// Deny setting focus to a view which is hidden by a fullscreen global
	if (root->fullscreen_global && container != root->fullscreen_global &&
				!container_has_ancestor(container, root->fullscreen_global)) {
		// Unless it's a transient container
		if (!container_is_transient_for(container, root->fullscreen_global)) {
			return;
		}
	}

	struct sway_output *new_output =
		new_workspace ? new_workspace->output : NULL;

	if (last_workspace != new_workspace && new_output) {
		node_set_dirty(&new_output->node);
	}

	// find new output's old workspace, which might have to be removed if empty
	struct sway_workspace *new_output_last_ws =
		new_output ? output_get_active_workspace(new_output) : NULL;

	// Unfocus the previous focus
	if (last_focus) {
		seat_send_unfocus(last_focus, seat);
		node_set_dirty(last_focus);
		struct sway_node *parent = node_get_parent(last_focus);
		if (parent) {
			node_set_dirty(parent);
		}
	}

	// Put the container parents on the focus stack, then the workspace, then
	// the focused container.
	if (container) {
		struct sway_container *parent = container->parent;
		while (parent) {
			seat_set_raw_focus(seat, &parent->node);
			parent = parent->parent;
		}
	}
	if (new_workspace) {
		seat_set_raw_focus(seat, &new_workspace->node);
	}
	if (container) {
		seat_set_raw_focus(seat, &container->node);
		seat_send_focus(&container->node, seat);
	}

	// emit ipc events
	set_workspace(seat, new_workspace);
	if (container && container->view) {
		ipc_event_window(container, "focus");
	}

	// Move sticky containers to new workspace
	if (new_workspace && new_output_last_ws
			&& new_workspace != new_output_last_ws) {
		for (int i = 0; i < new_output_last_ws->floating->length; ++i) {
			struct sway_container *floater =
				new_output_last_ws->floating->items[i];
			if (floater->is_sticky) {
				container_detach(floater);
				workspace_add_floating(new_workspace, floater);
				--i;
			}
		}
	}

	// Close any popups on the old focus
	if (last_focus && node_is_view(last_focus)) {
		view_close_popups(last_focus->sway_container->view);
	}

	// If urgent, either unset the urgency or start a timer to unset it
	if (container && container->view && view_is_urgent(container->view) &&
			!container->view->urgent_timer) {
		struct sway_view *view = container->view;
		if (last_workspace && last_workspace != new_workspace &&
				config->urgent_timeout > 0) {
			view->urgent_timer = wl_event_loop_add_timer(server.wl_event_loop,
					handle_urgent_timeout, view);
			if (view->urgent_timer) {
				wl_event_source_timer_update(view->urgent_timer,
						config->urgent_timeout);
			} else {
				sway_log_errno(SWAY_ERROR, "Unable to create urgency timer");
				handle_urgent_timeout(view);
			}
		} else {
			view_set_urgent(view, false);
		}
	}

	if (new_output_last_ws) {
		workspace_consider_destroy(new_output_last_ws);
	}
	if (last_workspace && last_workspace != new_output_last_ws) {
		workspace_consider_destroy(last_workspace);
	}

	seat->has_focus = true;

	if (config->smart_gaps && new_workspace) {
		// When smart gaps is on, gaps may change when the focus changes so
		// the workspace needs to be arranged
		arrange_workspace(new_workspace);
	}
}