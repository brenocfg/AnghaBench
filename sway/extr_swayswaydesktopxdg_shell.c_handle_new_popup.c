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
struct sway_xdg_shell_view {int /*<<< orphan*/  view; } ;

/* Variables and functions */
 int /*<<< orphan*/  new_popup ; 
 int /*<<< orphan*/  popup_create (struct wlr_xdg_popup*,int /*<<< orphan*/ *) ; 
 struct sway_xdg_shell_view* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sway_xdg_shell_view* xdg_shell_view ; 

__attribute__((used)) static void handle_new_popup(struct wl_listener *listener, void *data) {
	struct sway_xdg_shell_view *xdg_shell_view =
		wl_container_of(listener, xdg_shell_view, new_popup);
	struct wlr_xdg_popup *wlr_popup = data;
	popup_create(wlr_popup, &xdg_shell_view->view);
}