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
struct sway_config {int /*<<< orphan*/ * swaybg_client; TYPE_1__ swaybg_client_destroy; } ;

/* Variables and functions */
 struct sway_config* sway_config ; 
 int /*<<< orphan*/  swaybg_client_destroy ; 
 struct sway_config* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_list_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_swaybg_client_destroy(struct wl_listener *listener,
		void *data) {
	struct sway_config *sway_config =
		wl_container_of(listener, sway_config, swaybg_client_destroy);
	wl_list_remove(&sway_config->swaybg_client_destroy.link);
	wl_list_init(&sway_config->swaybg_client_destroy.link);
	sway_config->swaybg_client = NULL;
}