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
struct sway_view {TYPE_1__* impl; struct sway_view* title_format; int /*<<< orphan*/  executed_criteria; int /*<<< orphan*/ * container; int /*<<< orphan*/  destroying; int /*<<< orphan*/ * surface; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* destroy ) (struct sway_view*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct sway_view*) ; 
 int /*<<< orphan*/  list_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sway_view*) ; 
 int /*<<< orphan*/  sway_assert (int /*<<< orphan*/ ,char*) ; 

void view_destroy(struct sway_view *view) {
	if (!sway_assert(view->surface == NULL, "Tried to free mapped view")) {
		return;
	}
	if (!sway_assert(view->destroying,
				"Tried to free view which wasn't marked as destroying")) {
		return;
	}
	if (!sway_assert(view->container == NULL,
				"Tried to free view which still has a container "
				"(might have a pending transaction?)")) {
		return;
	}
	list_free(view->executed_criteria);

	free(view->title_format);

	if (view->impl->destroy) {
		view->impl->destroy(view);
	} else {
		free(view);
	}
}