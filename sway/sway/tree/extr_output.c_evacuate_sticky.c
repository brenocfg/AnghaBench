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
struct sway_workspace {TYPE_1__* floating; } ;
struct sway_output {int dummy; } ;
struct sway_container {int dummy; } ;
struct TYPE_2__ {struct sway_container** items; scalar_t__ length; } ;

/* Variables and functions */
 int /*<<< orphan*/  container_detach (struct sway_container*) ; 
 int /*<<< orphan*/  container_floating_move_to_center (struct sway_container*) ; 
 int /*<<< orphan*/  container_handle_fullscreen_reparent (struct sway_container*) ; 
 int /*<<< orphan*/  ipc_event_window (struct sway_container*,char*) ; 
 struct sway_workspace* output_get_active_workspace (struct sway_output*) ; 
 int /*<<< orphan*/  sway_assert (struct sway_workspace*,char*) ; 
 int /*<<< orphan*/  workspace_add_floating (struct sway_workspace*,struct sway_container*) ; 
 int /*<<< orphan*/  workspace_detect_urgent (struct sway_workspace*) ; 

__attribute__((used)) static void evacuate_sticky(struct sway_workspace *old_ws,
		struct sway_output *new_output) {
	struct sway_workspace *new_ws = output_get_active_workspace(new_output);
	if (!sway_assert(new_ws, "New output does not have a workspace")) {
		return;
	}
	while (old_ws->floating->length) {
		struct sway_container *sticky = old_ws->floating->items[0];
		container_detach(sticky);
		workspace_add_floating(new_ws, sticky);
		container_handle_fullscreen_reparent(sticky);
		container_floating_move_to_center(sticky);
		ipc_event_window(sticky, "move");
	}
	workspace_detect_urgent(new_ws);
}