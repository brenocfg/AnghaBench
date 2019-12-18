#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int x; int y; } ;
struct wlr_xdg_surface {TYPE_5__* popup; TYPE_3__ geometry; } ;
struct sway_xdg_popup {struct wlr_xdg_surface* wlr_xdg_surface; } ;
struct sway_view_child {TYPE_2__* view; } ;
struct TYPE_9__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_10__ {TYPE_4__ geometry; } ;
struct TYPE_6__ {int x; int y; } ;
struct TYPE_7__ {TYPE_1__ geometry; } ;

/* Variables and functions */
 int /*<<< orphan*/  wlr_xdg_popup_get_toplevel_coords (TYPE_5__*,scalar_t__,scalar_t__,int*,int*) ; 

__attribute__((used)) static void popup_get_root_coords(struct sway_view_child *child,
		int *root_sx, int *root_sy) {
	struct sway_xdg_popup *popup = (struct sway_xdg_popup *)child;
	struct wlr_xdg_surface *surface = popup->wlr_xdg_surface;

	int x_offset = -child->view->geometry.x - surface->geometry.x;
	int y_offset = -child->view->geometry.y - surface->geometry.y;

	wlr_xdg_popup_get_toplevel_coords(surface->popup,
		x_offset + surface->popup->geometry.x,
		y_offset + surface->popup->geometry.y,
		root_sx, root_sy);
}