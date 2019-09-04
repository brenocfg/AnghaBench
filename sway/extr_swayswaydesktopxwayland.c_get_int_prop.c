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
typedef  int /*<<< orphan*/  uint32_t ;
struct sway_view {TYPE_2__* wlr_xwayland_surface; } ;
typedef  enum sway_view_prop { ____Placeholder_sway_view_prop } sway_view_prop ;
struct TYPE_4__ {int /*<<< orphan*/ * window_type; TYPE_1__* parent; int /*<<< orphan*/  window_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  window_id; } ;

/* Variables and functions */
#define  VIEW_PROP_WINDOW_TYPE 130 
#define  VIEW_PROP_X11_PARENT_ID 129 
#define  VIEW_PROP_X11_WINDOW_ID 128 
 int /*<<< orphan*/ * xwayland_view_from_view (struct sway_view*) ; 

__attribute__((used)) static uint32_t get_int_prop(struct sway_view *view, enum sway_view_prop prop) {
	if (xwayland_view_from_view(view) == NULL) {
		return 0;
	}
	switch (prop) {
	case VIEW_PROP_X11_WINDOW_ID:
		return view->wlr_xwayland_surface->window_id;
	case VIEW_PROP_X11_PARENT_ID:
		if (view->wlr_xwayland_surface->parent) {
			return view->wlr_xwayland_surface->parent->window_id;
		}
		return 0;
	case VIEW_PROP_WINDOW_TYPE:
		return *view->wlr_xwayland_surface->window_type;
	default:
		return 0;
	}
}