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
typedef  int /*<<< orphan*/  uint32_t ;
struct sway_view {int using_csd; TYPE_1__* xdg_decoration; } ;
struct TYPE_2__ {int /*<<< orphan*/  wlr_xdg_decoration; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  WLR_XDG_TOPLEVEL_DECORATION_V1_MODE_CLIENT_SIDE ; 
 int /*<<< orphan*/  WLR_XDG_TOPLEVEL_DECORATION_V1_MODE_SERVER_SIDE ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,struct sway_view*,int) ; 
 int /*<<< orphan*/  wlr_xdg_toplevel_decoration_v1_set_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void view_set_csd_from_server(struct sway_view *view, bool enabled) {
	sway_log(SWAY_DEBUG, "Telling view %p to set CSD to %i", view, enabled);
	if (view->xdg_decoration) {
		uint32_t mode = enabled ?
			WLR_XDG_TOPLEVEL_DECORATION_V1_MODE_CLIENT_SIDE :
			WLR_XDG_TOPLEVEL_DECORATION_V1_MODE_SERVER_SIDE;
		wlr_xdg_toplevel_decoration_v1_set_mode(
				view->xdg_decoration->wlr_xdg_decoration, mode);
	}
	view->using_csd = enabled;
}