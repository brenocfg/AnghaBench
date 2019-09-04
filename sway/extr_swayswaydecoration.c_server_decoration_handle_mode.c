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
struct wl_listener {int dummy; } ;
struct sway_view {scalar_t__ surface; int /*<<< orphan*/  container; } ;
struct sway_server_decoration {TYPE_1__* wlr_server_decoration; } ;
struct TYPE_2__ {scalar_t__ surface; scalar_t__ mode; } ;

/* Variables and functions */
 scalar_t__ WLR_SERVER_DECORATION_MANAGER_MODE_CLIENT ; 
 int /*<<< orphan*/  arrange_container (int /*<<< orphan*/ ) ; 
 struct sway_server_decoration* deco ; 
 int /*<<< orphan*/  mode ; 
 int /*<<< orphan*/  transaction_commit_dirty () ; 
 struct sway_view* view_from_wlr_surface (scalar_t__) ; 
 int /*<<< orphan*/  view_update_csd_from_client (struct sway_view*,int) ; 
 struct sway_server_decoration* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void server_decoration_handle_mode(struct wl_listener *listener,
		void *data) {
	struct sway_server_decoration *deco =
		wl_container_of(listener, deco, mode);
	struct sway_view *view =
		view_from_wlr_surface(deco->wlr_server_decoration->surface);
	if (view == NULL || view->surface != deco->wlr_server_decoration->surface) {
		return;
	}

	bool csd = deco->wlr_server_decoration->mode ==
			WLR_SERVER_DECORATION_MANAGER_MODE_CLIENT;
	view_update_csd_from_client(view, csd);

	arrange_container(view->container);
	transaction_commit_dirty();
}