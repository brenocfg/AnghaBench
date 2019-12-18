#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct wlr_xwayland_surface {TYPE_6__* surface; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct wlr_xwayland {int dummy; } ;
struct wl_listener {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  notify; } ;
struct sway_xwayland_unmanaged {int /*<<< orphan*/  ly; int /*<<< orphan*/  lx; TYPE_4__ commit; int /*<<< orphan*/  link; struct wlr_xwayland_surface* wlr_xwayland_surface; } ;
struct sway_seat {int /*<<< orphan*/  wlr_seat; } ;
struct TYPE_9__ {int /*<<< orphan*/  prev; } ;
struct TYPE_15__ {TYPE_1__ xwayland_unmanaged; } ;
struct TYPE_10__ {int /*<<< orphan*/  commit; } ;
struct TYPE_14__ {TYPE_2__ events; } ;
struct TYPE_11__ {struct wlr_xwayland* wlr_xwayland; } ;
struct TYPE_13__ {TYPE_3__ xwayland; } ;

/* Variables and functions */
 int /*<<< orphan*/  desktop_damage_surface (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct sway_seat* input_manager_current_seat () ; 
 int /*<<< orphan*/  map ; 
 TYPE_7__* root ; 
 int /*<<< orphan*/  seat_set_focus_surface (struct sway_seat*,TYPE_6__*,int) ; 
 TYPE_5__ server ; 
 struct sway_xwayland_unmanaged* surface ; 
 int /*<<< orphan*/  unmanaged_handle_commit ; 
 struct sway_xwayland_unmanaged* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_list_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_signal_add (int /*<<< orphan*/ *,TYPE_4__*) ; 
 scalar_t__ wlr_xwayland_or_surface_wants_focus (struct wlr_xwayland_surface*) ; 
 int /*<<< orphan*/  wlr_xwayland_set_seat (struct wlr_xwayland*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unmanaged_handle_map(struct wl_listener *listener, void *data) {
	struct sway_xwayland_unmanaged *surface =
		wl_container_of(listener, surface, map);
	struct wlr_xwayland_surface *xsurface = surface->wlr_xwayland_surface;

	wl_list_insert(root->xwayland_unmanaged.prev, &surface->link);

	wl_signal_add(&xsurface->surface->events.commit, &surface->commit);
	surface->commit.notify = unmanaged_handle_commit;

	surface->lx = xsurface->x;
	surface->ly = xsurface->y;
	desktop_damage_surface(xsurface->surface, surface->lx, surface->ly, true);

	if (wlr_xwayland_or_surface_wants_focus(xsurface)) {
		struct sway_seat *seat = input_manager_current_seat();
		struct wlr_xwayland *xwayland = server.xwayland.wlr_xwayland;
		wlr_xwayland_set_seat(xwayland, seat->wlr_seat);
		seat_set_focus_surface(seat, xsurface->surface, false);
	}
}