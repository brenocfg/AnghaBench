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
struct sway_container {int dummy; } ;
struct cmd_results {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_FAILURE ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  seat_consider_warp_to_focus (struct sway_seat*) ; 
 struct sway_container* seat_get_focus_inactive_floating (struct sway_seat*,struct sway_workspace*) ; 
 struct sway_container* seat_get_focus_inactive_tiling (struct sway_seat*,struct sway_workspace*) ; 
 int /*<<< orphan*/  seat_set_focus_container (struct sway_seat*,struct sway_container*) ; 

__attribute__((used)) static struct cmd_results *focus_mode(struct sway_workspace *ws,
		struct sway_seat *seat, bool floating) {
	struct sway_container *new_focus = NULL;
	if (floating) {
		new_focus = seat_get_focus_inactive_floating(seat, ws);
	} else {
		new_focus = seat_get_focus_inactive_tiling(seat, ws);
	}
	if (new_focus) {
		seat_set_focus_container(seat, new_focus);
		seat_consider_warp_to_focus(seat);
	} else {
		return cmd_results_new(CMD_FAILURE,
				"Failed to find a %s container in workspace",
				floating ? "floating" : "tiling");
	}
	return cmd_results_new(CMD_SUCCESS, NULL);
}