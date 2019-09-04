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
struct wlr_pointer_constraint_v1 {void* surface; } ;
struct wl_listener {int dummy; } ;
struct sway_cursor {struct wlr_pointer_constraint_v1* active_constraint; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  check_constraint_region (struct sway_cursor*) ; 
 int /*<<< orphan*/  constraint_commit ; 
 struct sway_cursor* cursor ; 
 struct sway_cursor* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_constraint_commit(struct wl_listener *listener,
		void *data) {
	struct sway_cursor *cursor =
		wl_container_of(listener, cursor, constraint_commit);
	struct wlr_pointer_constraint_v1 *constraint = cursor->active_constraint;
	assert(constraint->surface == data);

	check_constraint_region(cursor);
}