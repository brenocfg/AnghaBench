#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wl_listener {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  link; } ;
struct TYPE_5__ {int /*<<< orphan*/  link; } ;
struct TYPE_4__ {int /*<<< orphan*/  link; } ;
struct sway_view {int /*<<< orphan*/ * wlr_xdg_surface_v6; } ;
struct sway_xdg_shell_v6_view {TYPE_3__ unmap; TYPE_2__ map; TYPE_1__ destroy; struct sway_view view; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy ; 
 int /*<<< orphan*/  view_begin_destroy (struct sway_view*) ; 
 struct sway_xdg_shell_v6_view* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_list_remove (int /*<<< orphan*/ *) ; 
 struct sway_xdg_shell_v6_view* xdg_shell_v6_view ; 

__attribute__((used)) static void handle_destroy(struct wl_listener *listener, void *data) {
	struct sway_xdg_shell_v6_view *xdg_shell_v6_view =
		wl_container_of(listener, xdg_shell_v6_view, destroy);
	struct sway_view *view = &xdg_shell_v6_view->view;
	wl_list_remove(&xdg_shell_v6_view->destroy.link);
	wl_list_remove(&xdg_shell_v6_view->map.link);
	wl_list_remove(&xdg_shell_v6_view->unmap.link);
	view->wlr_xdg_surface_v6 = NULL;
	view_begin_destroy(view);
}