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
struct wlr_xwayland_surface {int /*<<< orphan*/  mapped; } ;
struct wl_listener {int dummy; } ;
struct sway_view {int /*<<< orphan*/  container; struct wlr_xwayland_surface* wlr_xwayland_surface; } ;
struct sway_xwayland_view {struct sway_view view; } ;
struct sway_seat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  container_is_floating (int /*<<< orphan*/ ) ; 
 struct sway_seat* input_manager_current_seat () ; 
 int /*<<< orphan*/  request_move ; 
 int /*<<< orphan*/  seatop_begin_move_floating (struct sway_seat*,int /*<<< orphan*/ ) ; 
 struct sway_xwayland_view* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sway_xwayland_view* xwayland_view ; 

__attribute__((used)) static void handle_request_move(struct wl_listener *listener, void *data) {
	struct sway_xwayland_view *xwayland_view =
		wl_container_of(listener, xwayland_view, request_move);
	struct sway_view *view = &xwayland_view->view;
	struct wlr_xwayland_surface *xsurface = view->wlr_xwayland_surface;
	if (!xsurface->mapped) {
		return;
	}
	if (!container_is_floating(view->container)) {
		return;
	}
	struct sway_seat *seat = input_manager_current_seat();
	seatop_begin_move_floating(seat, view->container);
}