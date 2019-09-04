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
struct swaybar_host {int /*<<< orphan*/  watcher_interface; TYPE_1__* tray; int /*<<< orphan*/  service; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_ERROR ; 
 int /*<<< orphan*/  get_registered_snis_callback ; 
 int sd_bus_call_method_async (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,TYPE_1__*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watcher_path ; 

__attribute__((used)) static bool register_to_watcher(struct swaybar_host *host) {
	// this is called asynchronously in case the watcher is owned by this process
	int ret = sd_bus_call_method_async(host->tray->bus, NULL,
			host->watcher_interface, watcher_path, host->watcher_interface,
			"RegisterStatusNotifierHost", NULL, NULL, "s", host->service);
	if (ret < 0) {
		sway_log(SWAY_ERROR, "Failed to send register call: %s", strerror(-ret));
		return false;
	}

	ret = sd_bus_call_method_async(host->tray->bus, NULL,
			host->watcher_interface, watcher_path,
			"org.freedesktop.DBus.Properties", "Get",
			get_registered_snis_callback, host->tray, "ss",
			host->watcher_interface, "RegisteredStatusNotifierItems");
	if (ret < 0) {
		sway_log(SWAY_ERROR, "Failed to get registered SNIs: %s", strerror(-ret));
	}

	return ret >= 0;
}