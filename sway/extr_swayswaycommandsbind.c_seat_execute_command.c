#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct wlr_surface {int dummy; } ;
struct sway_seat {TYPE_2__* cursor; } ;
struct sway_node {scalar_t__ type; struct sway_container* sway_container; } ;
struct sway_container {int dummy; } ;
struct sway_binding {scalar_t__ type; int /*<<< orphan*/  command; } ;
struct cmd_results {scalar_t__ status; int /*<<< orphan*/  error; } ;
struct TYPE_8__ {int length; struct cmd_results** items; } ;
typedef  TYPE_3__ list_t ;
struct TYPE_7__ {TYPE_1__* cursor; } ;
struct TYPE_6__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 scalar_t__ BINDING_MOUSECODE ; 
 scalar_t__ BINDING_MOUSESYM ; 
 scalar_t__ CMD_SUCCESS ; 
 scalar_t__ N_CONTAINER ; 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 TYPE_3__* execute_command (int /*<<< orphan*/ ,struct sway_seat*,struct sway_container*) ; 
 int /*<<< orphan*/  free_cmd_results (struct cmd_results*) ; 
 int /*<<< orphan*/  ipc_event_binding (struct sway_binding*) ; 
 int /*<<< orphan*/  list_free (TYPE_3__*) ; 
 struct sway_node* node_at_coords (struct sway_seat*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wlr_surface**,double*,double*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

void seat_execute_command(struct sway_seat *seat, struct sway_binding *binding) {
	sway_log(SWAY_DEBUG, "running command for binding: %s", binding->command);

	struct sway_container *con = NULL;
	if (binding->type == BINDING_MOUSESYM
			|| binding->type == BINDING_MOUSECODE) {
		struct wlr_surface *surface = NULL;
		double sx, sy;
		struct sway_node *node = node_at_coords(seat,
				seat->cursor->cursor->x, seat->cursor->cursor->y,
				&surface, &sx, &sy);
		if (node && node->type == N_CONTAINER) {
			con = node->sway_container;
		}
	}

	list_t *res_list = execute_command(binding->command, seat, con);
	bool success = true;
	for (int i = 0; i < res_list->length; ++i) {
		struct cmd_results *results = res_list->items[i];
		if (results->status != CMD_SUCCESS) {
			sway_log(SWAY_DEBUG, "could not run command for binding: %s (%s)",
				binding->command, results->error);
			success = false;
		}
		free_cmd_results(results);
	}
	list_free(res_list);
	if (success) {
		ipc_event_binding(binding);
	}
}