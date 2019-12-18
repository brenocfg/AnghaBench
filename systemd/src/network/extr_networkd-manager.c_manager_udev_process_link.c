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
typedef  int /*<<< orphan*/  sd_device_monitor ;
typedef  int /*<<< orphan*/  sd_device ;
typedef  int /*<<< orphan*/  Manager ;
typedef  int /*<<< orphan*/  Link ;
typedef  int /*<<< orphan*/  DeviceAction ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_ACTION_ADD ; 
 int /*<<< orphan*/  DEVICE_ACTION_CHANGE ; 
 int /*<<< orphan*/  DEVICE_ACTION_MOVE ; 
 int ENODEV ; 
 int /*<<< orphan*/  IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_action_to_string (int /*<<< orphan*/ ) ; 
 int device_get_action (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int device_is_renaming (int /*<<< orphan*/ *) ; 
 int link_get (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  link_initialized (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug_errno (int,char*,int) ; 
 int /*<<< orphan*/  log_device_debug (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  log_device_debug_errno (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  log_device_error_errno (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 int sd_device_get_ifindex (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int manager_udev_process_link(sd_device_monitor *monitor, sd_device *device, void *userdata) {
        Manager *m = userdata;
        DeviceAction action;
        Link *link = NULL;
        int r, ifindex;

        assert(m);
        assert(device);

        r = device_get_action(device, &action);
        if (r < 0) {
                log_device_debug_errno(device, r, "Failed to get udev action, ignoring device: %m");
                return 0;
        }

        if (!IN_SET(action, DEVICE_ACTION_ADD, DEVICE_ACTION_CHANGE, DEVICE_ACTION_MOVE)) {
                log_device_debug(device, "Ignoring udev %s event for device.", device_action_to_string(action));
                return 0;
        }

        r = sd_device_get_ifindex(device, &ifindex);
        if (r < 0) {
                log_device_debug_errno(device, r, "Ignoring udev ADD event for device without ifindex or with invalid ifindex: %m");
                return 0;
        }

        r = device_is_renaming(device);
        if (r < 0) {
                log_device_error_errno(device, r, "Failed to determine the device is renamed or not, ignoring '%s' uevent: %m",
                                       device_action_to_string(action));
                return 0;
        }
        if (r > 0) {
                log_device_debug(device, "Interface is under renaming, wait for the interface to be renamed: %m");
                return 0;
        }

        r = link_get(m, ifindex, &link);
        if (r < 0) {
                if (r != -ENODEV)
                        log_debug_errno(r, "Failed to get link from ifindex %i, ignoring: %m", ifindex);
                return 0;
        }

        (void) link_initialized(link, device);

        return 0;
}