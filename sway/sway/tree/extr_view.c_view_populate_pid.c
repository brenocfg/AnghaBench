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
struct wlr_xwayland_surface {int /*<<< orphan*/  pid; } ;
struct wl_client {int dummy; } ;
struct sway_view {int type; int /*<<< orphan*/  pid; TYPE_1__* surface; } ;
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_2__ {int /*<<< orphan*/  resource; } ;

/* Variables and functions */
#define  SWAY_VIEW_XDG_SHELL 129 
#define  SWAY_VIEW_XWAYLAND 128 
 int /*<<< orphan*/  wl_client_get_credentials (struct wl_client*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct wl_client* wl_resource_get_client (int /*<<< orphan*/ ) ; 
 struct wlr_xwayland_surface* wlr_xwayland_surface_from_wlr_surface (TYPE_1__*) ; 

__attribute__((used)) static void view_populate_pid(struct sway_view *view) {
	pid_t pid;
	switch (view->type) {
#if HAVE_XWAYLAND
	case SWAY_VIEW_XWAYLAND:;
		struct wlr_xwayland_surface *surf =
			wlr_xwayland_surface_from_wlr_surface(view->surface);
		pid = surf->pid;
		break;
#endif
	case SWAY_VIEW_XDG_SHELL:;
		struct wl_client *client =
			wl_resource_get_client(view->surface->resource);
		wl_client_get_credentials(client, &pid, NULL, NULL);
		break;
	}
	view->pid = pid;
}