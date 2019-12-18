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
struct sway_layer_surface {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LAYER_PARENT_LAYER ; 
 int /*<<< orphan*/  create_popup (struct wlr_xdg_popup*,int /*<<< orphan*/ ,struct sway_layer_surface*) ; 
 int /*<<< orphan*/  new_popup ; 
 struct sway_layer_surface* sway_layer_surface ; 
 struct sway_layer_surface* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_new_popup(struct wl_listener *listener, void *data) {
	struct sway_layer_surface *sway_layer_surface =
		wl_container_of(listener, sway_layer_surface, new_popup);
	struct wlr_xdg_popup *wlr_popup = data;
	create_popup(wlr_popup, LAYER_PARENT_LAYER, sway_layer_surface);
}