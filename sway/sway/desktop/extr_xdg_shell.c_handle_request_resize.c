#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wlr_xdg_toplevel_resize_event {scalar_t__ serial; int /*<<< orphan*/  edges; TYPE_2__* seat; } ;
struct wl_listener {int dummy; } ;
struct sway_view {int /*<<< orphan*/  container; } ;
struct sway_xdg_shell_view {struct sway_view view; } ;
struct sway_seat {scalar_t__ last_button_serial; } ;
struct TYPE_4__ {TYPE_1__* seat; } ;
struct TYPE_3__ {struct sway_seat* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  container_is_floating (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_resize ; 
 int /*<<< orphan*/  seatop_begin_resize_floating (struct sway_seat*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sway_xdg_shell_view* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sway_xdg_shell_view* xdg_shell_view ; 

__attribute__((used)) static void handle_request_resize(struct wl_listener *listener, void *data) {
	struct sway_xdg_shell_view *xdg_shell_view =
		wl_container_of(listener, xdg_shell_view, request_resize);
	struct sway_view *view = &xdg_shell_view->view;
	if (!container_is_floating(view->container)) {
		return;
	}
	struct wlr_xdg_toplevel_resize_event *e = data;
	struct sway_seat *seat = e->seat->seat->data;
	if (e->serial == seat->last_button_serial) {
		seatop_begin_resize_floating(seat, view->container, e->edges);
	}
}