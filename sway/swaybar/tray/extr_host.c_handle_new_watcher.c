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
struct swaybar_host {int /*<<< orphan*/  watcher_interface; } ;
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_ERROR ; 
 int /*<<< orphan*/  register_to_watcher (struct swaybar_host*) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,char**,char**,char**) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_new_watcher(sd_bus_message *msg,
		void *data, sd_bus_error *error) {
	char *service, *old_owner, *new_owner;
	int ret = sd_bus_message_read(msg, "sss", &service, &old_owner, &new_owner);
	if (ret < 0) {
		sway_log(SWAY_ERROR, "Failed to parse owner change message: %s", strerror(-ret));
		return ret;
	}

	if (!*old_owner) {
		struct swaybar_host *host = data;
		if (strcmp(service, host->watcher_interface) == 0) {
			register_to_watcher(host);
		}
	}

	return 0;
}