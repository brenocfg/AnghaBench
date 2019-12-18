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
struct wlr_xwayland_surface {int dummy; } ;
struct sway_view {struct wlr_xwayland_surface* wlr_xwayland_surface; } ;

/* Variables and functions */
 int /*<<< orphan*/  wlr_xwayland_surface_set_fullscreen (struct wlr_xwayland_surface*,int) ; 
 int /*<<< orphan*/ * xwayland_view_from_view (struct sway_view*) ; 

__attribute__((used)) static void set_fullscreen(struct sway_view *view, bool fullscreen) {
	if (xwayland_view_from_view(view) == NULL) {
		return;
	}
	struct wlr_xwayland_surface *surface = view->wlr_xwayland_surface;
	wlr_xwayland_surface_set_fullscreen(surface, fullscreen);
}