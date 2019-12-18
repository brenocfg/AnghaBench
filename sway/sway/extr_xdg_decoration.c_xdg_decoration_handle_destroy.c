#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wl_listener {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  link; } ;
struct TYPE_5__ {int /*<<< orphan*/  link; } ;
struct sway_xdg_decoration {int /*<<< orphan*/  link; TYPE_3__ request_mode; TYPE_2__ destroy; TYPE_1__* view; } ;
struct TYPE_4__ {int /*<<< orphan*/ * xdg_decoration; } ;

/* Variables and functions */
 struct sway_xdg_decoration* deco ; 
 int /*<<< orphan*/  destroy ; 
 int /*<<< orphan*/  free (struct sway_xdg_decoration*) ; 
 struct sway_xdg_decoration* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_list_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xdg_decoration_handle_destroy(struct wl_listener *listener,
		void *data) {
	struct sway_xdg_decoration *deco =
		wl_container_of(listener, deco, destroy);
	if(deco->view) {
		deco->view->xdg_decoration = NULL;
	}
	wl_list_remove(&deco->destroy.link);
	wl_list_remove(&deco->request_mode.link);
	wl_list_remove(&deco->link);
	free(deco);
}