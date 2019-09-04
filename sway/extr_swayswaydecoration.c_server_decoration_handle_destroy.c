#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wl_listener {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  link; } ;
struct TYPE_3__ {int /*<<< orphan*/  link; } ;
struct sway_server_decoration {int /*<<< orphan*/  link; TYPE_2__ mode; TYPE_1__ destroy; } ;

/* Variables and functions */
 struct sway_server_decoration* deco ; 
 int /*<<< orphan*/  destroy ; 
 int /*<<< orphan*/  free (struct sway_server_decoration*) ; 
 struct sway_server_decoration* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_list_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void server_decoration_handle_destroy(struct wl_listener *listener,
		void *data) {
	struct sway_server_decoration *deco =
		wl_container_of(listener, deco, destroy);
	wl_list_remove(&deco->destroy.link);
	wl_list_remove(&deco->mode.link);
	wl_list_remove(&deco->link);
	free(deco);
}