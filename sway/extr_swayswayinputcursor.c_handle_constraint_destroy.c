#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct wlr_pointer_constraint_v1 {TYPE_3__* seat; } ;
struct wl_listener {int dummy; } ;
struct sway_seat {struct sway_cursor* cursor; } ;
struct TYPE_9__ {int /*<<< orphan*/ * next; } ;
struct TYPE_6__ {TYPE_4__ link; } ;
struct sway_pointer_constraint {TYPE_1__ destroy; } ;
struct TYPE_7__ {TYPE_4__ link; } ;
struct sway_cursor {struct wlr_pointer_constraint_v1* active_constraint; TYPE_2__ constraint_commit; } ;
struct TYPE_8__ {struct sway_seat* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy ; 
 int /*<<< orphan*/  free (struct sway_pointer_constraint*) ; 
 struct sway_pointer_constraint* sway_constraint ; 
 int /*<<< orphan*/  warp_to_constraint_cursor_hint (struct sway_cursor*) ; 
 struct sway_pointer_constraint* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_list_init (TYPE_4__*) ; 
 int /*<<< orphan*/  wl_list_remove (TYPE_4__*) ; 

void handle_constraint_destroy(struct wl_listener *listener, void *data) {
	struct sway_pointer_constraint *sway_constraint =
		wl_container_of(listener, sway_constraint, destroy);
	struct wlr_pointer_constraint_v1 *constraint = data;
	struct sway_seat *seat = constraint->seat->data;
	struct sway_cursor *cursor = seat->cursor;

	wl_list_remove(&sway_constraint->destroy.link);

	if (cursor->active_constraint == constraint) {
		warp_to_constraint_cursor_hint(cursor);

		if (cursor->constraint_commit.link.next != NULL) {
			wl_list_remove(&cursor->constraint_commit.link);
		}
		wl_list_init(&cursor->constraint_commit.link);
		cursor->active_constraint = NULL;
	}

	free(sway_constraint);
}