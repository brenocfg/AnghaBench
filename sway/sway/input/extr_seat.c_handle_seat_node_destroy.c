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
struct wl_listener {int dummy; } ;
struct sway_node {scalar_t__ type; TYPE_2__* sway_container; int /*<<< orphan*/ * sway_workspace; } ;
struct sway_workspace {struct sway_node node; } ;
struct sway_seat_node {struct sway_node* node; struct sway_seat* seat; } ;
struct sway_seat {int /*<<< orphan*/ * workspace; } ;
struct sway_container {struct sway_node node; } ;
struct TYPE_6__ {int /*<<< orphan*/  node; } ;
struct TYPE_5__ {TYPE_1__* workspace; scalar_t__ scratchpad; } ;
struct TYPE_4__ {struct sway_node node; } ;

/* Variables and functions */
 scalar_t__ N_CONTAINER ; 
 scalar_t__ N_WORKSPACE ; 
 int /*<<< orphan*/  destroy ; 
 struct sway_node* node_get_parent (struct sway_node*) ; 
 scalar_t__ node_has_ancestor (struct sway_node*,struct sway_node*) ; 
 TYPE_3__* root ; 
 struct sway_node* seat_get_focus (struct sway_seat*) ; 
 struct sway_node* seat_get_focus_inactive (struct sway_seat*,int /*<<< orphan*/ *) ; 
 struct sway_container* seat_get_focus_inactive_view (struct sway_seat*,struct sway_node*) ; 
 struct sway_workspace* seat_get_last_known_workspace (struct sway_seat*) ; 
 struct sway_seat_node* seat_node ; 
 int /*<<< orphan*/  seat_node_destroy (struct sway_seat_node*) ; 
 int /*<<< orphan*/  seat_send_focus (struct sway_node*,struct sway_seat*) ; 
 int /*<<< orphan*/  seat_set_focus (struct sway_seat*,struct sway_node*) ; 
 int /*<<< orphan*/  seat_set_raw_focus (struct sway_seat*,struct sway_node*) ; 
 struct sway_seat_node* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  workspace_is_visible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_seat_node_destroy(struct wl_listener *listener, void *data) {
	struct sway_seat_node *seat_node =
		wl_container_of(listener, seat_node, destroy);
	struct sway_seat *seat = seat_node->seat;
	struct sway_node *node = seat_node->node;
	struct sway_node *parent = node_get_parent(node);
	struct sway_node *focus = seat_get_focus(seat);

	if (node->type == N_WORKSPACE) {
		seat_node_destroy(seat_node);
		// If an unmanaged or layer surface is focused when an output gets
		// disabled and an empty workspace on the output was focused by the
		// seat, the seat needs to refocus it's focus inactive to update the
		// value of seat->workspace.
		if (seat->workspace == node->sway_workspace) {
			struct sway_node *node = seat_get_focus_inactive(seat, &root->node);
			seat_set_focus(seat, NULL);
			if (node) {
				seat_set_focus(seat, node);
			} else {
				seat->workspace = NULL;
			}
		}
		return;
	}

	// Even though the container being destroyed might be nowhere near the
	// focused container, we still need to set focus_inactive on a sibling of
	// the container being destroyed.
	bool needs_new_focus = focus &&
		(focus == node || node_has_ancestor(focus, node));

	seat_node_destroy(seat_node);

	if (!parent && !needs_new_focus) {
		// Destroying a container that is no longer in the tree
		return;
	}

	// Find new focus_inactive (ie. sibling, or workspace if no siblings left)
	struct sway_node *next_focus = NULL;
	while (next_focus == NULL && parent != NULL) {
		struct sway_container *con =
			seat_get_focus_inactive_view(seat, parent);
		next_focus = con ? &con->node : NULL;

		if (next_focus == NULL && parent->type == N_WORKSPACE) {
			next_focus = parent;
			break;
		}

		parent = node_get_parent(parent);
	}

	if (!next_focus) {
		struct sway_workspace *ws = seat_get_last_known_workspace(seat);
		if (!ws) {
			return;
		}
		struct sway_container *con =
			seat_get_focus_inactive_view(seat, &ws->node);
		next_focus = con ? &(con->node) : &(ws->node);
	}

	if (next_focus->type == N_WORKSPACE &&
			!workspace_is_visible(next_focus->sway_workspace)) {
		// Do not change focus to a non-visible workspace
		return;
	}

	if (needs_new_focus) {
		// Make sure the workspace IPC event gets sent
		if (node->type == N_CONTAINER && node->sway_container->scratchpad) {
			seat_set_focus(seat, NULL);
		}
		// The structure change might have caused it to move up to the top of
		// the focus stack without sending focus notifications to the view
		seat_send_focus(next_focus, seat);
		seat_set_focus(seat, next_focus);
	} else {
		// Setting focus_inactive
		focus = seat_get_focus_inactive(seat, &root->node);
		seat_set_raw_focus(seat, next_focus);
		if (focus->type == N_CONTAINER && focus->sway_container->workspace) {
			seat_set_raw_focus(seat, &focus->sway_container->workspace->node);
		}
		seat_set_raw_focus(seat, focus);
	}
}