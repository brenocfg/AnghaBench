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
struct wlr_xdg_surface_v6 {int dummy; } ;
struct wlr_surface {int dummy; } ;

/* Variables and functions */
 struct wlr_xdg_surface_v6* wlr_xdg_surface_v6_from_wlr_surface (struct wlr_surface*) ; 
 int /*<<< orphan*/  wlr_xdg_surface_v6_send_close (struct wlr_xdg_surface_v6*) ; 

__attribute__((used)) static void close_popups_iterator(struct wlr_surface *surface,
		int sx, int sy, void *data) {
	struct wlr_xdg_surface_v6 *xdg_surface_v6 =
		wlr_xdg_surface_v6_from_wlr_surface(surface);
	wlr_xdg_surface_v6_send_close(xdg_surface_v6);
}