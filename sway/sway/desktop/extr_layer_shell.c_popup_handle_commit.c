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
struct sway_layer_popup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  commit ; 
 struct sway_layer_popup* popup ; 
 int /*<<< orphan*/  popup_damage (struct sway_layer_popup*,int) ; 
 struct sway_layer_popup* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void popup_handle_commit(struct wl_listener *listener, void *data) {
	struct sway_layer_popup *popup = wl_container_of(listener, popup, commit);
	popup_damage(popup, false);
}