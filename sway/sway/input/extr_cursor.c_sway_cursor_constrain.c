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
struct TYPE_5__ {int /*<<< orphan*/  region; } ;
struct wlr_pointer_constraint_v1 {TYPE_3__* surface; int /*<<< orphan*/  region; TYPE_1__ current; } ;
struct TYPE_8__ {int /*<<< orphan*/  notify; int /*<<< orphan*/  link; } ;
struct sway_cursor {TYPE_4__ constraint_commit; struct wlr_pointer_constraint_v1* active_constraint; int /*<<< orphan*/  seat; } ;
struct seat_config {scalar_t__ allow_constrain; } ;
struct TYPE_6__ {int /*<<< orphan*/  commit; } ;
struct TYPE_7__ {TYPE_2__ events; int /*<<< orphan*/  input_region; } ;

/* Variables and functions */
 scalar_t__ CONSTRAIN_DISABLE ; 
 int /*<<< orphan*/  check_constraint_region (struct sway_cursor*) ; 
 int /*<<< orphan*/  handle_constraint_commit ; 
 int /*<<< orphan*/  pixman_region32_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pixman_region32_intersect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pixman_region32_not_empty (int /*<<< orphan*/ *) ; 
 struct seat_config* seat_get_config (int /*<<< orphan*/ ) ; 
 struct seat_config* seat_get_config_by_name (char*) ; 
 int /*<<< orphan*/  warp_to_constraint_cursor_hint (struct sway_cursor*) ; 
 int /*<<< orphan*/  wl_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_signal_add (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  wlr_pointer_constraint_v1_send_activated (struct wlr_pointer_constraint_v1*) ; 
 int /*<<< orphan*/  wlr_pointer_constraint_v1_send_deactivated (struct wlr_pointer_constraint_v1*) ; 

void sway_cursor_constrain(struct sway_cursor *cursor,
		struct wlr_pointer_constraint_v1 *constraint) {
	struct seat_config *config = seat_get_config(cursor->seat);
	if (!config) {
		config = seat_get_config_by_name("*");
	}

	if (!config || config->allow_constrain == CONSTRAIN_DISABLE) {
		return;
	}

	if (cursor->active_constraint == constraint) {
		return;
	}

	wl_list_remove(&cursor->constraint_commit.link);
	if (cursor->active_constraint) {
		if (constraint == NULL) {
			warp_to_constraint_cursor_hint(cursor);
		}
		wlr_pointer_constraint_v1_send_deactivated(
			cursor->active_constraint);
	}

	cursor->active_constraint = constraint;

	if (constraint == NULL) {
		wl_list_init(&cursor->constraint_commit.link);
		return;
	}

	// FIXME: Big hack, stolen from wlr_pointer_constraints_v1.c:121.
	// This is necessary because the focus may be set before the surface
	// has finished committing, which means that warping won't work properly,
	// since this code will be run *after* the focus has been set.
	// That is why we duplicate the code here.
	if (pixman_region32_not_empty(&constraint->current.region)) {
		pixman_region32_intersect(&constraint->region,
			&constraint->surface->input_region, &constraint->current.region);
	} else {
		pixman_region32_copy(&constraint->region,
			&constraint->surface->input_region);
	}

	check_constraint_region(cursor);

	wlr_pointer_constraint_v1_send_activated(constraint);

	cursor->constraint_commit.notify = handle_constraint_commit;
	wl_signal_add(&constraint->surface->events.commit,
		&cursor->constraint_commit);
}