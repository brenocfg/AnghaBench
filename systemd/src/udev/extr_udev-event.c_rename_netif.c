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
typedef  int /*<<< orphan*/  sd_device ;
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  rtnl; int /*<<< orphan*/ * dev; } ;
typedef  TYPE_1__ UdevEvent ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_ACTION_ADD ; 
 int ENOENT ; 
 int device_add_property (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  device_for_action (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int device_rename (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_device_debug (int /*<<< orphan*/ *,char*,int,char const*,int /*<<< orphan*/ ) ; 
 int log_device_error_errno (int /*<<< orphan*/ *,int,char*,...) ; 
 int log_device_warning_errno (int /*<<< orphan*/ *,int,char*,...) ; 
 int rtnl_set_link_name (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int sd_device_get_ifindex (int /*<<< orphan*/ *,int*) ; 
 int sd_device_get_sysname (int /*<<< orphan*/ *,char const**) ; 
 scalar_t__ streq (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int rename_netif(UdevEvent *event) {
        sd_device *dev = event->dev;
        const char *oldname;
        int ifindex, r;

        if (!event->name)
                return 0; /* No new name is requested. */

        r = sd_device_get_sysname(dev, &oldname);
        if (r < 0)
                return log_device_error_errno(dev, r, "Failed to get sysname: %m");

        if (streq(event->name, oldname))
                return 0; /* The interface name is already requested name. */

        if (!device_for_action(dev, DEVICE_ACTION_ADD))
                return 0; /* Rename the interface only when it is added. */

        r = sd_device_get_ifindex(dev, &ifindex);
        if (r == -ENOENT)
                return 0; /* Device is not a network interface. */
        if (r < 0)
                return log_device_error_errno(dev, r, "Failed to get ifindex: %m");

        r = rtnl_set_link_name(&event->rtnl, ifindex, event->name);
        if (r < 0)
                return log_device_error_errno(dev, r, "Failed to rename network interface %i from '%s' to '%s': %m",
                                              ifindex, oldname, event->name);

        /* Set ID_RENAMING boolean property here, and drop it in the corresponding move uevent later. */
        r = device_add_property(dev, "ID_RENAMING", "1");
        if (r < 0)
                return log_device_warning_errno(dev, r, "Failed to add 'ID_RENAMING' property: %m");

        r = device_rename(dev, event->name);
        if (r < 0)
                return log_device_warning_errno(dev, r, "Failed to update properties with new name '%s': %m", event->name);

        log_device_debug(dev, "Network interface %i is renamed from '%s' to '%s'", ifindex, oldname, event->name);

        return 1;
}