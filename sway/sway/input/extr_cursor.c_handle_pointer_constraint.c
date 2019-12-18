#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct wlr_surface {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  destroy; } ;
struct wlr_pointer_constraint_v1 {struct wlr_surface* surface; TYPE_2__ events; TYPE_1__* seat; } ;
struct wl_listener {int dummy; } ;
struct sway_seat {int /*<<< orphan*/  cursor; } ;
struct TYPE_10__ {int /*<<< orphan*/  notify; } ;
struct sway_pointer_constraint {TYPE_5__ destroy; struct wlr_pointer_constraint_v1* constraint; } ;
struct sway_node {scalar_t__ type; TYPE_4__* sway_container; } ;
struct TYPE_9__ {TYPE_3__* view; } ;
struct TYPE_8__ {struct wlr_surface* surface; } ;
struct TYPE_6__ {struct sway_seat* data; } ;

/* Variables and functions */
 scalar_t__ N_CONTAINER ; 
 struct sway_pointer_constraint* calloc (int,int) ; 
 int /*<<< orphan*/  handle_constraint_destroy ; 
 struct sway_node* seat_get_focus (struct sway_seat*) ; 
 int /*<<< orphan*/  sway_cursor_constrain (int /*<<< orphan*/ ,struct wlr_pointer_constraint_v1*) ; 
 int /*<<< orphan*/  wl_signal_add (int /*<<< orphan*/ *,TYPE_5__*) ; 

void handle_pointer_constraint(struct wl_listener *listener, void *data) {
	struct wlr_pointer_constraint_v1 *constraint = data;
	struct sway_seat *seat = constraint->seat->data;

	struct sway_pointer_constraint *sway_constraint =
		calloc(1, sizeof(struct sway_pointer_constraint));
	sway_constraint->constraint = constraint;

	sway_constraint->destroy.notify = handle_constraint_destroy;
	wl_signal_add(&constraint->events.destroy, &sway_constraint->destroy);

	struct sway_node *focus = seat_get_focus(seat);
	if (focus && focus->type == N_CONTAINER && focus->sway_container->view) {
		struct wlr_surface *surface = focus->sway_container->view->surface;
		if (surface == constraint->surface) {
			sway_cursor_constrain(seat->cursor, constraint);
		}
	}
}