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
struct sway_view {int /*<<< orphan*/  wlr_xdg_surface_v6; } ;

/* Variables and functions */
 int /*<<< orphan*/  close_popups_iterator ; 
 int /*<<< orphan*/  wlr_xdg_surface_v6_for_each_popup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void close_popups(struct sway_view *view) {
	wlr_xdg_surface_v6_for_each_popup(view->wlr_xdg_surface_v6,
			close_popups_iterator, NULL);
}