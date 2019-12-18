#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  device_monitor; int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 scalar_t__ detect_container () ; 
 int log_error_errno (int,char*) ; 
 int /*<<< orphan*/  manager_udev_process_link ; 
 int sd_device_monitor_attach_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sd_device_monitor_filter_add_match_subsystem_devtype (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int sd_device_monitor_new (int /*<<< orphan*/ *) ; 
 int sd_device_monitor_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int manager_connect_udev(Manager *m) {
        int r;

        /* udev does not initialize devices inside containers,
         * so we rely on them being already initialized before
         * entering the container */
        if (detect_container() > 0)
                return 0;

        r = sd_device_monitor_new(&m->device_monitor);
        if (r < 0)
                return log_error_errno(r, "Failed to initialize device monitor: %m");

        r = sd_device_monitor_filter_add_match_subsystem_devtype(m->device_monitor, "net", NULL);
        if (r < 0)
                return log_error_errno(r, "Could not add device monitor filter: %m");

        r = sd_device_monitor_attach_event(m->device_monitor, m->event);
        if (r < 0)
                return log_error_errno(r, "Failed to attach event to device monitor: %m");

        r = sd_device_monitor_start(m->device_monitor, manager_udev_process_link, m);
        if (r < 0)
                return log_error_errno(r, "Failed to start device monitor: %m");

        return 0;
}