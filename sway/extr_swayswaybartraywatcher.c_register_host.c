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
struct swaybar_watcher {int /*<<< orphan*/  interface; int /*<<< orphan*/  bus; int /*<<< orphan*/  hosts; } ;
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  SWAY_ERROR ; 
 int /*<<< orphan*/  cmp_id ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int list_seq_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  obj_path ; 
 int /*<<< orphan*/  sd_bus_emit_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,char**) ; 
 int sd_bus_reply_method_return (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int register_host(sd_bus_message *msg, void *data, sd_bus_error *error) {
	char *service;
	int ret = sd_bus_message_read(msg, "s", &service);
	if (ret < 0) {
		sway_log(SWAY_ERROR, "Failed to parse register host message: %s", strerror(-ret));
		return ret;
	}

	struct swaybar_watcher *watcher = data;
	if (list_seq_find(watcher->hosts, cmp_id, service) == -1) {
		sway_log(SWAY_DEBUG, "Registering Status Notifier Host '%s'", service);
		list_add(watcher->hosts, strdup(service));
		sd_bus_emit_signal(watcher->bus, obj_path, watcher->interface,
				"StatusNotifierHostRegistered", "s", service);
	} else {
		sway_log(SWAY_DEBUG, "Status Notifier Host '%s' already registered", service);
	}

	return sd_bus_reply_method_return(msg, "");
}