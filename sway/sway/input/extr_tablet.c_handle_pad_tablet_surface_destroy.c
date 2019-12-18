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
struct TYPE_2__ {int /*<<< orphan*/  link; } ;
struct sway_tablet_pad {int /*<<< orphan*/ * current_surface; TYPE_1__ surface_destroy; int /*<<< orphan*/  tablet_v2_pad; } ;

/* Variables and functions */
 int /*<<< orphan*/  surface_destroy ; 
 struct sway_tablet_pad* tablet_pad ; 
 struct sway_tablet_pad* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wlr_tablet_v2_tablet_pad_notify_leave (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_pad_tablet_surface_destroy(struct wl_listener *listener,
		void *data) {
	struct sway_tablet_pad *tablet_pad =
		wl_container_of(listener, tablet_pad, surface_destroy);

	wlr_tablet_v2_tablet_pad_notify_leave(tablet_pad->tablet_v2_pad,
		tablet_pad->current_surface);
	wl_list_remove(&tablet_pad->surface_destroy.link);
	wl_list_init(&tablet_pad->surface_destroy.link);
	tablet_pad->current_surface = NULL;
}