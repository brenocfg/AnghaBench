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
typedef  int /*<<< orphan*/  MonitorNetlinkGroup ;

/* Variables and functions */
 int /*<<< orphan*/  MONITOR_GROUP_KERNEL ; 
 int /*<<< orphan*/  MONITOR_GROUP_NONE ; 
 int /*<<< orphan*/  MONITOR_GROUP_UDEV ; 
 int /*<<< orphan*/  _MONITOR_NETLINK_GROUP_INVALID ; 
 scalar_t__ streq (char const*,char*) ; 

__attribute__((used)) static MonitorNetlinkGroup monitor_netlink_group_from_string(const char *name) {
        if (!name)
                return MONITOR_GROUP_NONE;
        if (streq(name, "udev"))
                return MONITOR_GROUP_UDEV;
        if (streq(name, "kernel"))
                return MONITOR_GROUP_KERNEL;
        return _MONITOR_NETLINK_GROUP_INVALID;
}