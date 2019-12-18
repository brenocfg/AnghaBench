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
struct swaybar_watcher {int /*<<< orphan*/  interface; int /*<<< orphan*/  bus; int /*<<< orphan*/  items; } ;
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  SWAY_ERROR ; 
 int /*<<< orphan*/  cmp_id ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ ,char*) ; 
 int list_seq_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  obj_path ; 
 int /*<<< orphan*/  sd_bus_emit_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*) ; 
 char* sd_bus_message_get_sender (int /*<<< orphan*/ *) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,char**) ; 
 int sd_bus_reply_method_return (int /*<<< orphan*/ *,char*) ; 
 int snprintf (char*,size_t,char*,char const*,char const*) ; 
 char* strdup (char*) ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ using_standard_protocol (struct swaybar_watcher*) ; 

__attribute__((used)) static int register_sni(sd_bus_message *msg, void *data, sd_bus_error *error) {
	char *service_or_path, *id;
	int ret = sd_bus_message_read(msg, "s", &service_or_path);
	if (ret < 0) {
		sway_log(SWAY_ERROR, "Failed to parse register SNI message: %s", strerror(-ret));
		return ret;
	}

	struct swaybar_watcher *watcher = data;
	if (using_standard_protocol(watcher)) {
		id = strdup(service_or_path);
	} else {
		const char *service, *path;
		if (service_or_path[0] == '/') {
			service = sd_bus_message_get_sender(msg);
			path = service_or_path;
		} else {
			service = service_or_path;
			path = "/StatusNotifierItem";
		}
		size_t id_len = snprintf(NULL, 0, "%s%s", service, path) + 1;
		id = malloc(id_len);
		snprintf(id, id_len, "%s%s", service, path);
	}

	if (list_seq_find(watcher->items, cmp_id, id) == -1) {
		sway_log(SWAY_DEBUG, "Registering Status Notifier Item '%s'", id);
		list_add(watcher->items, id);
		sd_bus_emit_signal(watcher->bus, obj_path, watcher->interface,
				"StatusNotifierItemRegistered", "s", id);
	} else {
		sway_log(SWAY_DEBUG, "Status Notifier Item '%s' already registered", id);
		free(id);
	}

	return sd_bus_reply_method_return(msg, "");
}