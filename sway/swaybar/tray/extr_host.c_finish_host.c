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
struct swaybar_host {int /*<<< orphan*/  watcher_interface; int /*<<< orphan*/  service; TYPE_1__* tray; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_bus_release_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void finish_host(struct swaybar_host *host) {
	sd_bus_release_name(host->tray->bus, host->service);
	free(host->service);
	free(host->watcher_interface);
}