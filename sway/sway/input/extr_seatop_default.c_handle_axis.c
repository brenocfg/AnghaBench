#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct wlr_surface {int dummy; } ;
struct wlr_keyboard {int dummy; } ;
struct wlr_input_device {int dummy; } ;
struct wlr_event_pointer_axis {float delta_discrete; float delta; int /*<<< orphan*/  source; int /*<<< orphan*/  orientation; int /*<<< orphan*/  time_msec; TYPE_1__* device; } ;
struct sway_seat {int /*<<< orphan*/  wlr_seat; struct seatop_default_event* seatop_data; struct sway_cursor* cursor; } ;
struct sway_node {scalar_t__ type; struct sway_container* sway_container; } ;
struct sway_input_device {struct wlr_input_device* wlr_device; } ;
struct sway_cursor {TYPE_4__* seat; TYPE_2__* cursor; } ;
struct sway_container {scalar_t__ content_y; struct sway_node node; } ;
struct sway_binding {int dummy; } ;
struct seatop_default_event {int dummy; } ;
struct input_config {float scroll_factor; } ;
struct TYPE_13__ {int length; struct sway_container** items; } ;
typedef  TYPE_5__ list_t ;
typedef  enum wlr_edges { ____Placeholder_wlr_edges } wlr_edges ;
typedef  enum sway_container_layout { ____Placeholder_sway_container_layout } sway_container_layout ;
struct TYPE_14__ {TYPE_3__* current_mode; } ;
struct TYPE_12__ {int /*<<< orphan*/  wlr_seat; } ;
struct TYPE_11__ {int /*<<< orphan*/  mouse_bindings; } ;
struct TYPE_10__ {scalar_t__ y; int /*<<< orphan*/  x; } ;
struct TYPE_9__ {struct sway_input_device* data; } ;

/* Variables and functions */
 float FLT_MIN ; 
 int L_STACKED ; 
 int L_TABBED ; 
 scalar_t__ N_CONTAINER ; 
 scalar_t__ N_WORKSPACE ; 
 int WLR_EDGE_NONE ; 
 TYPE_8__* config ; 
 TYPE_5__* container_get_siblings (struct sway_container*) ; 
 int container_parent_layout (struct sway_container*) ; 
 int find_edge (struct sway_container*,struct wlr_surface*,struct sway_cursor*) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct sway_binding* get_active_mouse_binding (struct seatop_default_event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,char*) ; 
 struct input_config* input_device_get_config (struct sway_input_device*) ; 
 char* input_device_get_identifier (struct wlr_input_device*) ; 
 int list_find (TYPE_5__*,struct sway_container*) ; 
 struct sway_node* node_at_coords (struct sway_seat*,int /*<<< orphan*/ ,scalar_t__,struct wlr_surface**,double*,double*) ; 
 struct sway_node* node_get_parent (struct sway_node*) ; 
 scalar_t__ node_has_ancestor (struct sway_node*,struct sway_node*) ; 
 int round (float) ; 
 int /*<<< orphan*/  seat_execute_command (struct sway_seat*,struct sway_binding*) ; 
 struct sway_node* seat_get_active_tiling_child (struct sway_seat*,struct sway_node*) ; 
 struct sway_node* seat_get_focus (struct sway_seat*) ; 
 struct sway_node* seat_get_focus_inactive (struct sway_seat*,struct sway_node*) ; 
 int /*<<< orphan*/  seat_set_focus (struct sway_seat*,struct sway_node*) ; 
 int /*<<< orphan*/  seat_set_raw_focus (struct sway_seat*,struct sway_node*) ; 
 int /*<<< orphan*/  state_add_button (struct seatop_default_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  state_erase_button (struct seatop_default_event*,int /*<<< orphan*/ ) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  wl_axis_to_button (struct wlr_event_pointer_axis*) ; 
 int /*<<< orphan*/  wlr_keyboard_get_modifiers (struct wlr_keyboard*) ; 
 struct wlr_keyboard* wlr_seat_get_keyboard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_seat_pointer_notify_axis (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_axis(struct sway_seat *seat,
		struct wlr_event_pointer_axis *event) {
	struct sway_input_device *input_device =
		event->device ? event->device->data : NULL;
	struct input_config *ic =
		input_device ? input_device_get_config(input_device) : NULL;
	struct sway_cursor *cursor = seat->cursor;
	struct seatop_default_event *e = seat->seatop_data;

	// Determine what's under the cursor
	struct wlr_surface *surface = NULL;
	double sx, sy;
	struct sway_node *node = node_at_coords(seat,
			cursor->cursor->x, cursor->cursor->y, &surface, &sx, &sy);
	struct sway_container *cont = node && node->type == N_CONTAINER ?
		node->sway_container : NULL;
	enum wlr_edges edge = cont ? find_edge(cont, surface, cursor) : WLR_EDGE_NONE;
	bool on_border = edge != WLR_EDGE_NONE;
	bool on_titlebar = cont && !on_border && !surface;
	bool on_titlebar_border = cont && on_border &&
		cursor->cursor->y < cont->content_y;
	bool on_contents = cont && !on_border && surface;
	bool on_workspace = node && node->type == N_WORKSPACE;
	float scroll_factor =
		(ic == NULL || ic->scroll_factor == FLT_MIN) ? 1.0f : ic->scroll_factor;

	bool handled = false;

	// Gather information needed for mouse bindings
	struct wlr_keyboard *keyboard = wlr_seat_get_keyboard(seat->wlr_seat);
	uint32_t modifiers = keyboard ? wlr_keyboard_get_modifiers(keyboard) : 0;
	struct wlr_input_device *device =
		input_device ? input_device->wlr_device : NULL;
	char *dev_id = device ? input_device_get_identifier(device) : strdup("*");
	uint32_t button = wl_axis_to_button(event);

	// Handle mouse bindings - x11 mouse buttons 4-7 - press event
	struct sway_binding *binding = NULL;
	state_add_button(e, button);
	binding = get_active_mouse_binding(e, config->current_mode->mouse_bindings,
			modifiers, false, on_titlebar, on_border, on_contents, on_workspace,
			dev_id);
	if (binding) {
		seat_execute_command(seat, binding);
		handled = true;
	}

	// Scrolling on a tabbed or stacked title bar (handled as press event)
	if (!handled && (on_titlebar || on_titlebar_border)) {
		enum sway_container_layout layout = container_parent_layout(cont);
		if (layout == L_TABBED || layout == L_STACKED) {
			struct sway_node *tabcontainer = node_get_parent(node);
			struct sway_node *active =
				seat_get_active_tiling_child(seat, tabcontainer);
			list_t *siblings = container_get_siblings(cont);
			int desired = list_find(siblings, active->sway_container) +
				round(scroll_factor * event->delta_discrete);
			if (desired < 0) {
				desired = 0;
			} else if (desired >= siblings->length) {
				desired = siblings->length - 1;
			}
			struct sway_node *old_focus = seat_get_focus(seat);
			struct sway_container *new_sibling_con = siblings->items[desired];
			struct sway_node *new_sibling = &new_sibling_con->node;
			struct sway_node *new_focus =
				seat_get_focus_inactive(seat, new_sibling);
			if (node_has_ancestor(old_focus, tabcontainer)) {
				seat_set_focus(seat, new_focus);
			} else {
				// Scrolling when focus is not in the tabbed container at all
				seat_set_raw_focus(seat, new_sibling);
				seat_set_raw_focus(seat, new_focus);
				seat_set_raw_focus(seat, old_focus);
			}
			handled = true;
		}
	}

	// Handle mouse bindings - x11 mouse buttons 4-7 - release event
	binding = get_active_mouse_binding(e, config->current_mode->mouse_bindings,
			modifiers, true, on_titlebar, on_border, on_contents, on_workspace,
			dev_id);
	state_erase_button(e, button);
	if (binding) {
		seat_execute_command(seat, binding);
		handled = true;
	}
	free(dev_id);

	if (!handled) {
		wlr_seat_pointer_notify_axis(cursor->seat->wlr_seat, event->time_msec,
			event->orientation, scroll_factor * event->delta,
			round(scroll_factor * event->delta_discrete), event->source);
	}
}