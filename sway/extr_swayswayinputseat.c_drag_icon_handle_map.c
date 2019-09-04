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
struct sway_drag_icon {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drag_icon_damage_whole (struct sway_drag_icon*) ; 
 struct sway_drag_icon* icon ; 
 int /*<<< orphan*/  map ; 
 struct sway_drag_icon* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void drag_icon_handle_map(struct wl_listener *listener, void *data) {
	struct sway_drag_icon *icon = wl_container_of(listener, icon, map);
	drag_icon_damage_whole(icon);
}