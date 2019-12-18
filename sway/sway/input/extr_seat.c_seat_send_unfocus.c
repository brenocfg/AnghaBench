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
struct sway_seat {int /*<<< orphan*/  wlr_seat; int /*<<< orphan*/  cursor; } ;
struct sway_node {scalar_t__ type; int /*<<< orphan*/  sway_container; int /*<<< orphan*/  sway_workspace; } ;

/* Variables and functions */
 scalar_t__ N_WORKSPACE ; 
 int /*<<< orphan*/  container_for_each_child (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,struct sway_seat*),struct sway_seat*) ; 
 int /*<<< orphan*/  send_unfocus (int /*<<< orphan*/ ,struct sway_seat*) ; 
 int /*<<< orphan*/  sway_cursor_constrain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wlr_seat_keyboard_clear_focus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  workspace_for_each_container (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,struct sway_seat*),struct sway_seat*) ; 

__attribute__((used)) static void seat_send_unfocus(struct sway_node *node, struct sway_seat *seat) {
	sway_cursor_constrain(seat->cursor, NULL);
	wlr_seat_keyboard_clear_focus(seat->wlr_seat);
	if (node->type == N_WORKSPACE) {
		workspace_for_each_container(node->sway_workspace, send_unfocus, seat);
	} else {
		send_unfocus(node->sway_container, seat);
		container_for_each_child(node->sway_container, send_unfocus, seat);
	}
}