#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sway_workspace {int dummy; } ;
struct sway_seat {int dummy; } ;
struct sway_container {struct sway_workspace* workspace; int /*<<< orphan*/  scratchpad; } ;

/* Variables and functions */
 struct sway_seat* input_manager_current_seat () ; 
 int /*<<< orphan*/  ipc_event_window (struct sway_container*,char*) ; 
 int /*<<< orphan*/  root_scratchpad_hide (struct sway_container*) ; 
 int /*<<< orphan*/  root_scratchpad_show (struct sway_container*) ; 
 struct sway_workspace* seat_get_focused_workspace (struct sway_seat*) ; 
 int /*<<< orphan*/  sway_assert (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void scratchpad_toggle_container(struct sway_container *con) {
	if (!sway_assert(con->scratchpad, "Container isn't in the scratchpad")) {
		return;
	}

	struct sway_seat *seat = input_manager_current_seat();
	struct sway_workspace *ws = seat_get_focused_workspace(seat);
	// Check if it matches a currently visible scratchpad window and hide it.
	if (con->workspace && ws == con->workspace) {
		root_scratchpad_hide(con);
		return;
	}

	root_scratchpad_show(con);
	ipc_event_window(con, "move");
}