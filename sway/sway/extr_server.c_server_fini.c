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
struct TYPE_2__ {int /*<<< orphan*/  wlr_xwayland; } ;
struct sway_server {int /*<<< orphan*/  transactions; int /*<<< orphan*/  dirty_nodes; int /*<<< orphan*/  wl_display; TYPE_1__ xwayland; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_display_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_display_destroy_clients (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_xwayland_destroy (int /*<<< orphan*/ ) ; 

void server_fini(struct sway_server *server) {
	// TODO: free sway-specific resources
#if HAVE_XWAYLAND
	wlr_xwayland_destroy(server->xwayland.wlr_xwayland);
#endif
	wl_display_destroy_clients(server->wl_display);
	wl_display_destroy(server->wl_display);
	list_free(server->dirty_nodes);
	list_free(server->transactions);
}