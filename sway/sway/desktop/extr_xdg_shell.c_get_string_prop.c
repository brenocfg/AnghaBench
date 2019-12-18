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
struct sway_view {TYPE_2__* wlr_xdg_surface; } ;
typedef  enum sway_view_prop { ____Placeholder_sway_view_prop } sway_view_prop ;
struct TYPE_4__ {TYPE_1__* toplevel; } ;
struct TYPE_3__ {char const* title; char const* app_id; } ;

/* Variables and functions */
#define  VIEW_PROP_APP_ID 129 
#define  VIEW_PROP_TITLE 128 
 int /*<<< orphan*/ * xdg_shell_view_from_view (struct sway_view*) ; 

__attribute__((used)) static const char *get_string_prop(struct sway_view *view,
		enum sway_view_prop prop) {
	if (xdg_shell_view_from_view(view) == NULL) {
		return NULL;
	}
	switch (prop) {
	case VIEW_PROP_TITLE:
		return view->wlr_xdg_surface->toplevel->title;
	case VIEW_PROP_APP_ID:
		return view->wlr_xdg_surface->toplevel->app_id;
	default:
		return NULL;
	}
}