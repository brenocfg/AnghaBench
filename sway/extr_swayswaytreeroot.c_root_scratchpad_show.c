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
struct wlr_box {int dummy; } ;
struct sway_workspace {scalar_t__ fullscreen; } ;
struct sway_seat {int dummy; } ;
struct sway_container {int x; int width; int y; int height; int /*<<< orphan*/  node; struct sway_workspace* workspace; } ;
struct TYPE_2__ {scalar_t__ fullscreen_global; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  arrange_workspace (struct sway_workspace*) ; 
 int /*<<< orphan*/  container_detach (struct sway_container*) ; 
 int /*<<< orphan*/  container_floating_resize_and_center (struct sway_container*) ; 
 int /*<<< orphan*/  container_fullscreen_disable (scalar_t__) ; 
 struct sway_seat* input_manager_current_seat () ; 
 TYPE_1__* root ; 
 int /*<<< orphan*/  seat_get_focus_inactive (struct sway_seat*,int /*<<< orphan*/ *) ; 
 struct sway_workspace* seat_get_focused_workspace (struct sway_seat*) ; 
 int /*<<< orphan*/  seat_set_focus (struct sway_seat*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wlr_box_contains_point (struct wlr_box*,double,double) ; 
 int /*<<< orphan*/  workspace_add_floating (struct sway_workspace*,struct sway_container*) ; 
 int /*<<< orphan*/  workspace_get_box (struct sway_workspace*,struct wlr_box*) ; 

void root_scratchpad_show(struct sway_container *con) {
	struct sway_seat *seat = input_manager_current_seat();
	struct sway_workspace *new_ws = seat_get_focused_workspace(seat);
	if (!new_ws) {
		sway_log(SWAY_DEBUG, "No focused workspace to show scratchpad on");
		return;
	}
	struct sway_workspace *old_ws = con->workspace;

	// If the current con or any of its parents are in fullscreen mode, we
	// first need to disable it before showing the scratchpad con.
	if (new_ws->fullscreen) {
		container_fullscreen_disable(new_ws->fullscreen);
	}
	if (root->fullscreen_global) {
		container_fullscreen_disable(root->fullscreen_global);
	}

	// Show the container
	if (old_ws) {
		container_detach(con);
	}
	workspace_add_floating(new_ws, con);

	// Make sure the container's center point overlaps this workspace
	double center_lx = con->x + con->width / 2;
	double center_ly = con->y + con->height / 2;

	struct wlr_box workspace_box;
	workspace_get_box(new_ws, &workspace_box);
	if (!wlr_box_contains_point(&workspace_box, center_lx, center_ly)) {
		container_floating_resize_and_center(con);
	}

	arrange_workspace(new_ws);
	seat_set_focus(seat, seat_get_focus_inactive(seat, &con->node));
}