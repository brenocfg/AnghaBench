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
struct sway_view {int /*<<< orphan*/ * saved_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  sway_assert (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  wlr_buffer_unref (int /*<<< orphan*/ *) ; 

void view_remove_saved_buffer(struct sway_view *view) {
	if (!sway_assert(view->saved_buffer, "Expected a saved buffer")) {
		return;
	}
	wlr_buffer_unref(view->saved_buffer);
	view->saved_buffer = NULL;
}