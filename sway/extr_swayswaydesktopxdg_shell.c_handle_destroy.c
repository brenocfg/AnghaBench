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
struct wl_listener {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  link; } ;
struct TYPE_6__ {int /*<<< orphan*/  link; } ;
struct TYPE_5__ {int /*<<< orphan*/  link; } ;
struct sway_view {TYPE_4__* xdg_decoration; int /*<<< orphan*/ * wlr_xdg_surface; int /*<<< orphan*/ * surface; } ;
struct sway_xdg_shell_view {TYPE_3__ unmap; TYPE_2__ map; TYPE_1__ destroy; struct sway_view view; } ;
struct TYPE_8__ {int /*<<< orphan*/ * view; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy ; 
 int /*<<< orphan*/  sway_assert (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  view_begin_destroy (struct sway_view*) ; 
 struct sway_xdg_shell_view* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_list_remove (int /*<<< orphan*/ *) ; 
 struct sway_xdg_shell_view* xdg_shell_view ; 

__attribute__((used)) static void handle_destroy(struct wl_listener *listener, void *data) {
	struct sway_xdg_shell_view *xdg_shell_view =
		wl_container_of(listener, xdg_shell_view, destroy);
	struct sway_view *view = &xdg_shell_view->view;
	if (!sway_assert(view->surface == NULL, "Tried to destroy a mapped view")) {
		return;
	}
	wl_list_remove(&xdg_shell_view->destroy.link);
	wl_list_remove(&xdg_shell_view->map.link);
	wl_list_remove(&xdg_shell_view->unmap.link);
	view->wlr_xdg_surface = NULL;
	if (view->xdg_decoration) {
		view->xdg_decoration->view = NULL;
	}
	view_begin_destroy(view);
}