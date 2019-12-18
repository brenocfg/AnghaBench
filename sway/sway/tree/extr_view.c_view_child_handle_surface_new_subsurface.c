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
struct wlr_subsurface {int dummy; } ;
struct wl_listener {int dummy; } ;
struct sway_view_child {int dummy; } ;

/* Variables and functions */
 struct sway_view_child* child ; 
 int /*<<< orphan*/  surface_new_subsurface ; 
 int /*<<< orphan*/  view_child_subsurface_create (struct sway_view_child*,struct wlr_subsurface*) ; 
 struct sway_view_child* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void view_child_handle_surface_new_subsurface(
		struct wl_listener *listener, void *data) {
	struct sway_view_child *child =
		wl_container_of(listener, child, surface_new_subsurface);
	struct wlr_subsurface *subsurface = data;
	view_child_subsurface_create(child, subsurface);
}