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
struct TYPE_3__ {int /*<<< orphan*/  destroy; } ;
struct wlr_idle_inhibitor_v1 {TYPE_1__ events; int /*<<< orphan*/  surface; } ;
struct wl_listener {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  notify; } ;
struct sway_idle_inhibitor_v1 {TYPE_2__ destroy; int /*<<< orphan*/  link; int /*<<< orphan*/  view; int /*<<< orphan*/  mode; struct sway_idle_inhibit_manager_v1* manager; } ;
struct sway_idle_inhibit_manager_v1 {int /*<<< orphan*/  inhibitors; } ;

/* Variables and functions */
 int /*<<< orphan*/  INHIBIT_IDLE_APPLICATION ; 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 struct sway_idle_inhibitor_v1* calloc (int,int) ; 
 int /*<<< orphan*/  handle_destroy ; 
 struct sway_idle_inhibit_manager_v1* manager ; 
 int /*<<< orphan*/  new_idle_inhibitor_v1 ; 
 int /*<<< orphan*/  sway_idle_inhibit_v1_check_active (struct sway_idle_inhibit_manager_v1*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  view_from_wlr_surface (int /*<<< orphan*/ ) ; 
 struct sway_idle_inhibit_manager_v1* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_list_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_signal_add (int /*<<< orphan*/ *,TYPE_2__*) ; 

void handle_idle_inhibitor_v1(struct wl_listener *listener, void *data) {
	struct wlr_idle_inhibitor_v1 *wlr_inhibitor = data;
	struct sway_idle_inhibit_manager_v1 *manager =
		wl_container_of(listener, manager, new_idle_inhibitor_v1);
	sway_log(SWAY_DEBUG, "New sway idle inhibitor");

	struct sway_idle_inhibitor_v1 *inhibitor =
		calloc(1, sizeof(struct sway_idle_inhibitor_v1));
	if (!inhibitor) {
		return;
	}

	inhibitor->manager = manager;
	inhibitor->mode = INHIBIT_IDLE_APPLICATION;
	inhibitor->view = view_from_wlr_surface(wlr_inhibitor->surface);
	wl_list_insert(&manager->inhibitors, &inhibitor->link);

	inhibitor->destroy.notify = handle_destroy;
	wl_signal_add(&wlr_inhibitor->events.destroy, &inhibitor->destroy);

	sway_idle_inhibit_v1_check_active(manager);
}