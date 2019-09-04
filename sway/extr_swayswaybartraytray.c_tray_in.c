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
typedef  int /*<<< orphan*/  sd_bus ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_ERROR ; 
 int sd_bus_process (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void tray_in(int fd, short mask, void *data) {
	sd_bus *bus = data;
	int ret;
	while ((ret = sd_bus_process(bus, NULL)) > 0) {
		// This space intentionally left blank
	}
	if (ret < 0) {
		sway_log(SWAY_ERROR, "Failed to process bus: %s", strerror(-ret));
	}
}