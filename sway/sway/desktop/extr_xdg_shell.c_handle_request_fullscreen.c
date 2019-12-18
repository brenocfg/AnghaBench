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
struct wlr_xdg_toplevel_set_fullscreen_event {scalar_t__ fullscreen; TYPE_1__* output; } ;
struct wlr_xdg_surface {scalar_t__ role; int /*<<< orphan*/  mapped; } ;
struct wl_listener {int dummy; } ;
struct sway_view {int /*<<< orphan*/  container; struct wlr_xdg_surface* wlr_xdg_surface; } ;
struct sway_xdg_shell_view {struct sway_view view; } ;
struct sway_workspace {int dummy; } ;
struct sway_output {int dummy; } ;
struct TYPE_2__ {struct sway_output* data; } ;

/* Variables and functions */
 scalar_t__ WLR_XDG_SURFACE_ROLE_TOPLEVEL ; 
 int /*<<< orphan*/  arrange_root () ; 
 scalar_t__ container_is_floating (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  container_is_scratchpad_hidden (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  container_set_fullscreen (int /*<<< orphan*/ ,scalar_t__) ; 
 struct sway_workspace* output_get_active_workspace (struct sway_output*) ; 
 int /*<<< orphan*/  request_fullscreen ; 
 int /*<<< orphan*/  sway_assert (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  transaction_commit_dirty () ; 
 struct sway_xdg_shell_view* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  workspace_add_floating (struct sway_workspace*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  workspace_add_tiling (struct sway_workspace*,int /*<<< orphan*/ ) ; 
 struct sway_xdg_shell_view* xdg_shell_view ; 

__attribute__((used)) static void handle_request_fullscreen(struct wl_listener *listener, void *data) {
	struct sway_xdg_shell_view *xdg_shell_view =
		wl_container_of(listener, xdg_shell_view, request_fullscreen);
	struct wlr_xdg_toplevel_set_fullscreen_event *e = data;
	struct wlr_xdg_surface *xdg_surface =
		xdg_shell_view->view.wlr_xdg_surface;
	struct sway_view *view = &xdg_shell_view->view;

	if (!sway_assert(xdg_surface->role == WLR_XDG_SURFACE_ROLE_TOPLEVEL,
				"xdg_shell requested fullscreen of surface with role %i",
				xdg_surface->role)) {
		return;
	}
	if (!xdg_surface->mapped) {
		return;
	}

	if (e->fullscreen && e->output && e->output->data) {
		struct sway_output *output = e->output->data;
		struct sway_workspace *ws = output_get_active_workspace(output);
		if (ws && !container_is_scratchpad_hidden(view->container)) {
			if (container_is_floating(view->container)) {
				workspace_add_floating(ws, view->container);
			} else {
				workspace_add_tiling(ws, view->container);
			}
		}
	}

	container_set_fullscreen(view->container, e->fullscreen);

	arrange_root();
	transaction_commit_dirty();
}