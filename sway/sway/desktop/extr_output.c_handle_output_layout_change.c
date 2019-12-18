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
struct sway_server {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  output_layout_change ; 
 struct sway_server* server ; 
 int /*<<< orphan*/  update_output_manager_config (struct sway_server*) ; 
 struct sway_server* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void handle_output_layout_change(struct wl_listener *listener,
		void *data) {
	struct sway_server *server =
		wl_container_of(listener, server, output_layout_change);
	update_output_manager_config(server);
}