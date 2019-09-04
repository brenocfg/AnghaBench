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
struct wl_listener {int dummy; } ;
struct sway_view {int dummy; } ;
struct sway_xdg_shell_view {struct sway_view view; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_app_id ; 
 int /*<<< orphan*/  view_execute_criteria (struct sway_view*) ; 
 struct sway_xdg_shell_view* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sway_xdg_shell_view* xdg_shell_view ; 

__attribute__((used)) static void handle_set_app_id(struct wl_listener *listener, void *data) {
	struct sway_xdg_shell_view *xdg_shell_view =
		wl_container_of(listener, xdg_shell_view, set_app_id);
	struct sway_view *view = &xdg_shell_view->view;
	view_execute_criteria(view);
}