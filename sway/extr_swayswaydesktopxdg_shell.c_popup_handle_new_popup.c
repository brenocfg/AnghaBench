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
struct wlr_xdg_popup {int dummy; } ;
struct wl_listener {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  view; } ;
struct sway_xdg_popup {TYPE_1__ child; } ;

/* Variables and functions */
 int /*<<< orphan*/  new_popup ; 
 struct sway_xdg_popup* popup ; 
 int /*<<< orphan*/  popup_create (struct wlr_xdg_popup*,int /*<<< orphan*/ ) ; 
 struct sway_xdg_popup* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void popup_handle_new_popup(struct wl_listener *listener, void *data) {
	struct sway_xdg_popup *popup =
		wl_container_of(listener, popup, new_popup);
	struct wlr_xdg_popup *wlr_popup = data;
	popup_create(wlr_popup, popup->child.view);
}