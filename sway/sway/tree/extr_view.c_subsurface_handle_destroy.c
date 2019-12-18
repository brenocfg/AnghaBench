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
struct wl_listener {int dummy; } ;
struct sway_view_child {int dummy; } ;
struct sway_subsurface {struct sway_view_child child; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy ; 
 struct sway_subsurface* subsurface ; 
 int /*<<< orphan*/  view_child_destroy (struct sway_view_child*) ; 
 struct sway_subsurface* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void subsurface_handle_destroy(struct wl_listener *listener,
		void *data) {
	struct sway_subsurface *subsurface =
		wl_container_of(listener, subsurface, destroy);
	struct sway_view_child *child = &subsurface->child;
	view_child_destroy(child);
}