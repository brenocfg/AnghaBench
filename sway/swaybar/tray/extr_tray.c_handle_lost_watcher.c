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
struct swaybar_tray {int /*<<< orphan*/  bus; void* watcher_kde; void* watcher_xdg; } ;
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_ERROR ; 
 void* create_watcher (char*,int /*<<< orphan*/ ) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,char**,char**,char**) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_lost_watcher(sd_bus_message *msg,
		void *data, sd_bus_error *error) {
	char *service, *old_owner, *new_owner;
	int ret = sd_bus_message_read(msg, "sss", &service, &old_owner, &new_owner);
	if (ret < 0) {
		sway_log(SWAY_ERROR, "Failed to parse owner change message: %s", strerror(-ret));
		return ret;
	}

	if (!*new_owner) {
		struct swaybar_tray *tray = data;
		if (strcmp(service, "org.freedesktop.StatusNotifierWatcher") == 0) {
			tray->watcher_xdg = create_watcher("freedesktop", tray->bus);
		} else if (strcmp(service, "org.kde.StatusNotifierWatcher") == 0) {
			tray->watcher_kde = create_watcher("kde", tray->bus);
		}
	}

	return 0;
}