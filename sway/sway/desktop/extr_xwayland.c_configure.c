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
typedef  int /*<<< orphan*/  uint32_t ;
struct wlr_xwayland_surface {int dummy; } ;
struct sway_xwayland_view {int dummy; } ;
struct sway_view {struct wlr_xwayland_surface* wlr_xwayland_surface; } ;

/* Variables and functions */
 int /*<<< orphan*/  wlr_xwayland_surface_configure (struct wlr_xwayland_surface*,double,double,int,int) ; 
 struct sway_xwayland_view* xwayland_view_from_view (struct sway_view*) ; 

__attribute__((used)) static uint32_t configure(struct sway_view *view, double lx, double ly, int width,
		int height) {
	struct sway_xwayland_view *xwayland_view = xwayland_view_from_view(view);
	if (xwayland_view == NULL) {
		return 0;
	}
	struct wlr_xwayland_surface *xsurface = view->wlr_xwayland_surface;

	wlr_xwayland_surface_configure(xsurface, lx, ly, width, height);

	// xwayland doesn't give us a serial for the configure
	return 0;
}