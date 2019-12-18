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
struct sway_view {TYPE_1__* wlr_xwayland_surface; } ;
typedef  enum sway_view_prop { ____Placeholder_sway_view_prop } sway_view_prop ;
struct TYPE_2__ {char const* title; char const* class; char const* instance; char const* role; } ;

/* Variables and functions */
#define  VIEW_PROP_CLASS 131 
#define  VIEW_PROP_INSTANCE 130 
#define  VIEW_PROP_TITLE 129 
#define  VIEW_PROP_WINDOW_ROLE 128 
 int /*<<< orphan*/ * xwayland_view_from_view (struct sway_view*) ; 

__attribute__((used)) static const char *get_string_prop(struct sway_view *view, enum sway_view_prop prop) {
	if (xwayland_view_from_view(view) == NULL) {
		return NULL;
	}
	switch (prop) {
	case VIEW_PROP_TITLE:
		return view->wlr_xwayland_surface->title;
	case VIEW_PROP_CLASS:
		return view->wlr_xwayland_surface->class;
	case VIEW_PROP_INSTANCE:
		return view->wlr_xwayland_surface->instance;
	case VIEW_PROP_WINDOW_ROLE:
		return view->wlr_xwayland_surface->role;
	default:
		return NULL;
	}
}