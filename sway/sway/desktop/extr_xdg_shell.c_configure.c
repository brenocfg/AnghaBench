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
struct sway_xdg_shell_view {int dummy; } ;
struct sway_view {int /*<<< orphan*/  wlr_xdg_surface; } ;

/* Variables and functions */
 int /*<<< orphan*/  wlr_xdg_toplevel_set_size (int /*<<< orphan*/ ,int,int) ; 
 struct sway_xdg_shell_view* xdg_shell_view_from_view (struct sway_view*) ; 

__attribute__((used)) static uint32_t configure(struct sway_view *view, double lx, double ly,
		int width, int height) {
	struct sway_xdg_shell_view *xdg_shell_view =
		xdg_shell_view_from_view(view);
	if (xdg_shell_view == NULL) {
		return 0;
	}
	return wlr_xdg_toplevel_set_size(view->wlr_xdg_surface, width, height);
}