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
struct swaybar_watcher {int /*<<< orphan*/ * interface; scalar_t__ version; void* items; void* hosts; int /*<<< orphan*/ * bus; } ;
typedef  int /*<<< orphan*/  sd_bus_slot ;
typedef  int /*<<< orphan*/  sd_bus ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  SWAY_ERROR ; 
 struct swaybar_watcher* calloc (int,int) ; 
 void* create_list () ; 
 int /*<<< orphan*/  destroy_watcher (struct swaybar_watcher*) ; 
 int /*<<< orphan*/  handle_lost_service ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  obj_path ; 
 int sd_bus_add_object_vtable (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct swaybar_watcher*) ; 
 int sd_bus_match_signal (int /*<<< orphan*/ *,int /*<<< orphan*/ **,char*,char*,char*,char*,int /*<<< orphan*/ ,struct swaybar_watcher*) ; 
 int sd_bus_request_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_bus_slot_set_floating (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_bus_slot_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,size_t,char*,char*) ; 
 int /*<<< orphan*/ * strerror (int) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watcher_vtable ; 

struct swaybar_watcher *create_watcher(char *protocol, sd_bus *bus) {
	struct swaybar_watcher *watcher =
		calloc(1, sizeof(struct swaybar_watcher));
	if (!watcher) {
		return NULL;
	}

	size_t len = snprintf(NULL, 0, "org.%s.StatusNotifierWatcher", protocol) + 1;
	watcher->interface = malloc(len);
	snprintf(watcher->interface, len, "org.%s.StatusNotifierWatcher", protocol);

	sd_bus_slot *signal_slot = NULL, *vtable_slot = NULL;
	int ret = sd_bus_add_object_vtable(bus, &vtable_slot, obj_path,
			watcher->interface, watcher_vtable, watcher);
	if (ret < 0) {
		sway_log(SWAY_ERROR, "Failed to add object vtable: %s", strerror(-ret));
		goto error;
	}

	ret = sd_bus_match_signal(bus, &signal_slot, "org.freedesktop.DBus",
			"/org/freedesktop/DBus", "org.freedesktop.DBus",
			"NameOwnerChanged", handle_lost_service, watcher);
	if (ret < 0) {
		sway_log(SWAY_ERROR, "Failed to subscribe to unregistering events: %s",
				strerror(-ret));
		goto error;
	}

	ret = sd_bus_request_name(bus, watcher->interface, 0);
	if (ret < 0) {
		sway_log(SWAY_ERROR, "Failed to acquire service name: %s", strerror(-ret));
		goto error;
	}

	sd_bus_slot_set_floating(signal_slot, 0);
	sd_bus_slot_set_floating(vtable_slot, 0);

	watcher->bus = bus;
	watcher->hosts = create_list();
	watcher->items = create_list();
	watcher->version = 0;
	sway_log(SWAY_DEBUG, "Registered %s", watcher->interface);
	return watcher;
error:
	sd_bus_slot_unref(signal_slot);
	sd_bus_slot_unref(vtable_slot);
	destroy_watcher(watcher);
	return NULL;
}