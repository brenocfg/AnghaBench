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
struct wlr_xdg_popup {int dummy; } ;
struct wl_listener {int dummy; } ;
struct sway_layer_popup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LAYER_PARENT_POPUP ; 
 int /*<<< orphan*/  create_popup (struct wlr_xdg_popup*,int /*<<< orphan*/ ,struct sway_layer_popup*) ; 
 int /*<<< orphan*/  new_popup ; 
 struct sway_layer_popup* sway_layer_popup ; 
 struct sway_layer_popup* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void popup_handle_new_popup(struct wl_listener *listener, void *data) {
	struct sway_layer_popup *sway_layer_popup =
		wl_container_of(listener, sway_layer_popup, new_popup);
	struct wlr_xdg_popup *wlr_popup = data;
	create_popup(wlr_popup, LAYER_PARENT_POPUP, sway_layer_popup);
}