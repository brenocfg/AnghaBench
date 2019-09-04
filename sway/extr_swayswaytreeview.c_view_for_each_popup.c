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
typedef  int /*<<< orphan*/  wlr_surface_iterator_func_t ;
struct sway_view {TYPE_1__* impl; int /*<<< orphan*/  surface; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* for_each_popup ) (struct sway_view*,int /*<<< orphan*/ ,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct sway_view*,int /*<<< orphan*/ ,void*) ; 

void view_for_each_popup(struct sway_view *view,
		wlr_surface_iterator_func_t iterator, void *user_data) {
	if (!view->surface) {
		return;
	}
	if (view->impl->for_each_popup) {
		view->impl->for_each_popup(view, iterator, user_data);
	}
}