#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  notify; } ;
struct sway_seat {int /*<<< orphan*/  link; int /*<<< orphan*/  devices; TYPE_6__ request_set_primary_selection; TYPE_4__* wlr_seat; TYPE_6__ request_set_selection; TYPE_6__ start_drag; TYPE_6__ request_start_drag; TYPE_6__ new_node; int /*<<< orphan*/  deferred_bindings; int /*<<< orphan*/  focus_stack; int /*<<< orphan*/  cursor; } ;
struct sway_node {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  new_node; } ;
struct TYPE_16__ {TYPE_1__ events; int /*<<< orphan*/  node; } ;
struct TYPE_15__ {TYPE_3__* input; int /*<<< orphan*/  wl_display; } ;
struct TYPE_11__ {int /*<<< orphan*/  request_set_primary_selection; int /*<<< orphan*/  request_set_selection; int /*<<< orphan*/  start_drag; int /*<<< orphan*/  request_start_drag; } ;
struct TYPE_13__ {TYPE_2__ events; struct sway_seat* data; } ;
struct TYPE_12__ {int /*<<< orphan*/  seats; } ;

/* Variables and functions */
 struct sway_seat* calloc (int,int) ; 
 int /*<<< orphan*/  collect_focus_container_iter ; 
 int /*<<< orphan*/  collect_focus_workspace_iter ; 
 int /*<<< orphan*/  create_list () ; 
 int /*<<< orphan*/  free (struct sway_seat*) ; 
 int /*<<< orphan*/  handle_new_node ; 
 int /*<<< orphan*/  handle_request_set_primary_selection ; 
 int /*<<< orphan*/  handle_request_set_selection ; 
 int /*<<< orphan*/  handle_request_start_drag ; 
 int /*<<< orphan*/  handle_start_drag ; 
 struct sway_seat* input_manager_current_seat () ; 
 TYPE_9__* root ; 
 int /*<<< orphan*/  root_for_each_container (int /*<<< orphan*/ ,struct sway_seat*) ; 
 int /*<<< orphan*/  root_for_each_workspace (int /*<<< orphan*/ ,struct sway_seat*) ; 
 struct sway_node* seat_get_focus_inactive (struct sway_seat*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seat_set_focus (struct sway_seat*,struct sway_node*) ; 
 int /*<<< orphan*/  seatop_begin_default (struct sway_seat*) ; 
 TYPE_8__ server ; 
 int /*<<< orphan*/  sway_assert (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  sway_cursor_create (struct sway_seat*) ; 
 int /*<<< orphan*/  wl_list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_list_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_signal_add (int /*<<< orphan*/ *,TYPE_6__*) ; 
 TYPE_4__* wlr_seat_create (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  wlr_seat_destroy (TYPE_4__*) ; 

struct sway_seat *seat_create(const char *seat_name) {
	struct sway_seat *seat = calloc(1, sizeof(struct sway_seat));
	if (!seat) {
		return NULL;
	}

	seat->wlr_seat = wlr_seat_create(server.wl_display, seat_name);
	if (!sway_assert(seat->wlr_seat, "could not allocate seat")) {
		free(seat);
		return NULL;
	}
	seat->wlr_seat->data = seat;

	seat->cursor = sway_cursor_create(seat);
	if (!seat->cursor) {
		wlr_seat_destroy(seat->wlr_seat);
		free(seat);
		return NULL;
	}

	// init the focus stack
	wl_list_init(&seat->focus_stack);

	root_for_each_workspace(collect_focus_workspace_iter, seat);
	root_for_each_container(collect_focus_container_iter, seat);

	seat->deferred_bindings = create_list();

	if (!wl_list_empty(&server.input->seats)) {
		// Since this is not the first seat, attempt to set initial focus
		struct sway_seat *current_seat = input_manager_current_seat();
		struct sway_node *current_focus =
			seat_get_focus_inactive(current_seat, &root->node);
		seat_set_focus(seat, current_focus);
	}

	wl_signal_add(&root->events.new_node, &seat->new_node);
	seat->new_node.notify = handle_new_node;

	wl_signal_add(&seat->wlr_seat->events.request_start_drag,
		&seat->request_start_drag);
	seat->request_start_drag.notify = handle_request_start_drag;

	wl_signal_add(&seat->wlr_seat->events.start_drag, &seat->start_drag);
	seat->start_drag.notify = handle_start_drag;

	wl_signal_add(&seat->wlr_seat->events.request_set_selection,
		&seat->request_set_selection);
	seat->request_set_selection.notify = handle_request_set_selection;

	wl_signal_add(&seat->wlr_seat->events.request_set_primary_selection,
		&seat->request_set_primary_selection);
	seat->request_set_primary_selection.notify =
		handle_request_set_primary_selection;

	wl_list_init(&seat->devices);

	wl_list_insert(&server.input->seats, &seat->link);

	seatop_begin_default(seat);

	return seat;
}