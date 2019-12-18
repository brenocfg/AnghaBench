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
typedef  scalar_t__ DeviceAction ;

/* Variables and functions */
 scalar_t__ DEVICE_ACTION_CHANGE ; 
 scalar_t__ DEVICE_ACTION_REMOVE ; 
 int DEVICE_FOUND_MOUNT ; 
 int DEVICE_FOUND_SWAP ; 
 int DEVICE_FOUND_UDEV ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int device_get_action (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ device_is_ready (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_process_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_propagate_reload_by_sysfs (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  device_update_found_by_sysfs (int /*<<< orphan*/ *,char const*,int,int) ; 
 int /*<<< orphan*/  log_device_error_errno (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  log_device_warning_errno (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  manager_dispatch_load_queue (int /*<<< orphan*/ *) ; 
 int sd_device_get_syspath (int /*<<< orphan*/ *,char const**) ; 
 int swap_process_device_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int swap_process_device_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int device_dispatch_io(sd_device_monitor *monitor, sd_device *dev, void *userdata) {
        Manager *m = userdata;
        DeviceAction action;
        const char *sysfs;
        int r;

        assert(m);
        assert(dev);

        r = sd_device_get_syspath(dev, &sysfs);
        if (r < 0) {
                log_device_error_errno(dev, r, "Failed to get device sys path: %m");
                return 0;
        }

        r = device_get_action(dev, &action);
        if (r < 0) {
                log_device_error_errno(dev, r, "Failed to get udev action: %m");
                return 0;
        }

        if (action == DEVICE_ACTION_CHANGE)
                device_propagate_reload_by_sysfs(m, sysfs);

        /* A change event can signal that a device is becoming ready, in particular if
         * the device is using the SYSTEMD_READY logic in udev
         * so we need to reach the else block of the following if, even for change events */
        if (action == DEVICE_ACTION_REMOVE) {
                r = swap_process_device_remove(m, dev);
                if (r < 0)
                        log_device_warning_errno(dev, r, "Failed to process swap device remove event, ignoring: %m");

                /* If we get notified that a device was removed by
                 * udev, then it's completely gone, hence unset all
                 * found bits */
                device_update_found_by_sysfs(m, sysfs, 0, DEVICE_FOUND_UDEV|DEVICE_FOUND_MOUNT|DEVICE_FOUND_SWAP);

        } else if (device_is_ready(dev)) {

                (void) device_process_new(m, dev);

                r = swap_process_device_new(m, dev);
                if (r < 0)
                        log_device_warning_errno(dev, r, "Failed to process swap device new event, ignoring: %m");

                manager_dispatch_load_queue(m);

                /* The device is found now, set the udev found bit */
                device_update_found_by_sysfs(m, sysfs, DEVICE_FOUND_UDEV, DEVICE_FOUND_UDEV);

        } else {
                /* The device is nominally around, but not ready for
                 * us. Hence unset the udev bit, but leave the rest
                 * around. */

                device_update_found_by_sysfs(m, sysfs, 0, DEVICE_FOUND_UDEV);
        }

        return 0;
}