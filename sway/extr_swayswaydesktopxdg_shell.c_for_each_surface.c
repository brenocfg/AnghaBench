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
typedef  int /*<<< orphan*/  wlr_surface_iterator_func_t ;
struct sway_view {int /*<<< orphan*/  wlr_xdg_surface; } ;

/* Variables and functions */
 int /*<<< orphan*/  wlr_xdg_surface_for_each_surface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/ * xdg_shell_view_from_view (struct sway_view*) ; 

__attribute__((used)) static void for_each_surface(struct sway_view *view,
		wlr_surface_iterator_func_t iterator, void *user_data) {
	if (xdg_shell_view_from_view(view) == NULL) {
		return;
	}
	wlr_xdg_surface_for_each_surface(view->wlr_xdg_surface, iterator,
		user_data);
}