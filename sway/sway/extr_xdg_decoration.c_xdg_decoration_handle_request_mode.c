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
struct wl_listener {int dummy; } ;
struct sway_xdg_decoration {int /*<<< orphan*/  wlr_xdg_decoration; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLR_XDG_TOPLEVEL_DECORATION_V1_MODE_SERVER_SIDE ; 
 struct sway_xdg_decoration* deco ; 
 int /*<<< orphan*/  request_mode ; 
 struct sway_xdg_decoration* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_xdg_toplevel_decoration_v1_set_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xdg_decoration_handle_request_mode(struct wl_listener *listener,
		void *data) {
	struct sway_xdg_decoration *deco =
		wl_container_of(listener, deco, request_mode);
	wlr_xdg_toplevel_decoration_v1_set_mode(deco->wlr_xdg_decoration,
			WLR_XDG_TOPLEVEL_DECORATION_V1_MODE_SERVER_SIDE);
}