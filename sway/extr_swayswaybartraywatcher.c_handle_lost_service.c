#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct swaybar_watcher {TYPE_1__* hosts; int /*<<< orphan*/  interface; int /*<<< orphan*/  bus; TYPE_1__* items; } ;
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
struct TYPE_3__ {int length; char** items; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  SWAY_ERROR ; 
 int cmp_id (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  list_del (TYPE_1__*,int) ; 
 int list_seq_find (TYPE_1__*,int (*) (char*,char*),char*) ; 
 int /*<<< orphan*/  obj_path ; 
 int /*<<< orphan*/  sd_bus_emit_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,char**,char**,char**) ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int strncmp (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ using_standard_protocol (struct swaybar_watcher*) ; 

__attribute__((used)) static int handle_lost_service(sd_bus_message *msg,
		void *data, sd_bus_error *error) {
	char *service, *old_owner, *new_owner;
	int ret = sd_bus_message_read(msg, "sss", &service, &old_owner, &new_owner);
	if (ret < 0) {
		sway_log(SWAY_ERROR, "Failed to parse owner change message: %s", strerror(-ret));
		return ret;
	}

	if (!*new_owner) {
		struct swaybar_watcher *watcher = data;
		for (int idx = 0; idx < watcher->items->length; ++idx) {
			char *id = watcher->items->items[idx];
			int cmp_res = using_standard_protocol(watcher) ?
				cmp_id(id, service) : strncmp(id, service, strlen(service));
			if (cmp_res == 0) {
				sway_log(SWAY_DEBUG, "Unregistering Status Notifier Item '%s'", id);
				list_del(watcher->items, idx--);
				sd_bus_emit_signal(watcher->bus, obj_path, watcher->interface,
						"StatusNotifierItemUnregistered", "s", id);
				free(id);
				if (using_standard_protocol(watcher)) {
					break;
				}
			}
		}

		int idx = list_seq_find(watcher->hosts, cmp_id, service);
		if (idx != -1) {
			sway_log(SWAY_DEBUG, "Unregistering Status Notifier Host '%s'", service);
			free(watcher->hosts->items[idx]);
			list_del(watcher->hosts, idx);
		}
	}

	return 0;
}