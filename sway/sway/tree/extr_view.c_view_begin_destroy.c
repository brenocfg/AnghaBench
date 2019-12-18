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
struct sway_view {int destroying; int /*<<< orphan*/  container; int /*<<< orphan*/ * surface; } ;

/* Variables and functions */
 int /*<<< orphan*/  sway_assert (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  view_destroy (struct sway_view*) ; 

void view_begin_destroy(struct sway_view *view) {
	if (!sway_assert(view->surface == NULL, "Tried to destroy a mapped view")) {
		return;
	}
	view->destroying = true;

	if (!view->container) {
		view_destroy(view);
	}
}