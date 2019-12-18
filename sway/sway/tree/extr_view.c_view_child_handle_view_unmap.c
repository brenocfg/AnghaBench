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
struct sway_view_child {int mapped; } ;

/* Variables and functions */
 struct sway_view_child* child ; 
 int /*<<< orphan*/  view_child_damage (struct sway_view_child*,int) ; 
 int /*<<< orphan*/  view_unmap ; 
 struct sway_view_child* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void view_child_handle_view_unmap(struct wl_listener *listener,
		void *data) {
	struct sway_view_child *child =
		wl_container_of(listener, child, view_unmap);
	view_child_damage(child, true);
	child->mapped = false;
}