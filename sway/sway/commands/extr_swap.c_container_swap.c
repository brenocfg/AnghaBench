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
struct sway_workspace {int /*<<< orphan*/  node; } ;
struct sway_seat {char* prev_workspace_name; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct sway_container {int scratchpad; int fullscreen_mode; TYPE_3__* workspace; TYPE_1__ node; } ;
typedef  enum sway_fullscreen_mode { ____Placeholder_sway_fullscreen_mode } sway_fullscreen_mode ;
struct TYPE_6__ {struct sway_seat* seat; } ;
struct TYPE_8__ {TYPE_2__ handler_context; } ;
struct TYPE_7__ {int /*<<< orphan*/  output; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 TYPE_4__* config ; 
 int /*<<< orphan*/  container_fullscreen_disable (struct sway_container*) ; 
 int /*<<< orphan*/  container_has_ancestor (struct sway_container*,struct sway_container*) ; 
 int container_is_scratchpad_hidden (struct sway_container*) ; 
 int /*<<< orphan*/  container_set_fullscreen (struct sway_container*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct sway_workspace* output_get_active_workspace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  root_scratchpad_add_container (struct sway_container*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  root_scratchpad_remove_container (struct sway_container*) ; 
 int /*<<< orphan*/  root_scratchpad_show (struct sway_container*) ; 
 int /*<<< orphan*/  seat_get_focus_inactive (struct sway_seat*,int /*<<< orphan*/ *) ; 
 struct sway_container* seat_get_focused_container (struct sway_seat*) ; 
 int /*<<< orphan*/  seat_set_focus (struct sway_seat*,int /*<<< orphan*/ ) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  swap_focus (struct sway_container*,struct sway_container*,struct sway_seat*,struct sway_container*) ; 
 int /*<<< orphan*/  swap_places (struct sway_container*,struct sway_container*) ; 
 int /*<<< orphan*/  sway_assert (int,char*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  workspace_is_visible (struct sway_workspace*) ; 

void container_swap(struct sway_container *con1, struct sway_container *con2) {
	if (!sway_assert(con1 && con2, "Cannot swap with nothing")) {
		return;
	}
	if (!sway_assert(!container_has_ancestor(con1, con2)
				&& !container_has_ancestor(con2, con1),
				"Cannot swap ancestor and descendant")) {
		return;
	}

	sway_log(SWAY_DEBUG, "Swapping containers %zu and %zu",
			con1->node.id, con2->node.id);

	bool scratch1 = con1->scratchpad;
	bool hidden1 = container_is_scratchpad_hidden(con1);
	bool scratch2 = con2->scratchpad;
	bool hidden2 = container_is_scratchpad_hidden(con2);
	if (scratch1) {
		if (hidden1) {
			root_scratchpad_show(con1);
		}
		root_scratchpad_remove_container(con1);
	}
	if (scratch2) {
		if (hidden2) {
			root_scratchpad_show(con2);
		}
		root_scratchpad_remove_container(con2);
	}

	enum sway_fullscreen_mode fs1 = con1->fullscreen_mode;
	enum sway_fullscreen_mode fs2 = con2->fullscreen_mode;
	if (fs1) {
		container_fullscreen_disable(con1);
	}
	if (fs2) {
		container_fullscreen_disable(con2);
	}

	struct sway_seat *seat = config->handler_context.seat;
	struct sway_container *focus = seat_get_focused_container(seat);
	struct sway_workspace *vis1 =
		output_get_active_workspace(con1->workspace->output);
	struct sway_workspace *vis2 =
		output_get_active_workspace(con2->workspace->output);
	if (!sway_assert(vis1 && vis2, "con1 or con2 are on an output without a"
				"workspace. This should not happen")) {
		return;
	}

	char *stored_prev_name = NULL;
	if (seat->prev_workspace_name) {
		stored_prev_name = strdup(seat->prev_workspace_name);
	}

	swap_places(con1, con2);

	if (!workspace_is_visible(vis1)) {
		seat_set_focus(seat, seat_get_focus_inactive(seat, &vis1->node));
	}
	if (!workspace_is_visible(vis2)) {
		seat_set_focus(seat, seat_get_focus_inactive(seat, &vis2->node));
	}

	swap_focus(con1, con2, seat, focus);

	if (stored_prev_name) {
		free(seat->prev_workspace_name);
		seat->prev_workspace_name = stored_prev_name;
	}

	if (scratch1) {
		root_scratchpad_add_container(con2, NULL);
		if (!hidden1) {
			root_scratchpad_show(con2);
		}
	}
	if (scratch2) {
		root_scratchpad_add_container(con1, NULL);
		if (!hidden2) {
			root_scratchpad_show(con1);
		}
	}

	if (fs1) {
		container_set_fullscreen(con2, fs1);
	}
	if (fs2) {
		container_set_fullscreen(con1, fs2);
	}
}