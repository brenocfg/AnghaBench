#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usec_t ;
typedef  int /*<<< orphan*/  sd_device ;
struct TYPE_13__ {scalar_t__ dev_db_clone; int /*<<< orphan*/ * dev; } ;
typedef  TYPE_1__ UdevRules ;
typedef  TYPE_1__ UdevEvent ;
typedef  int /*<<< orphan*/  Hashmap ;
typedef  scalar_t__ DeviceAction ;

/* Variables and functions */
 scalar_t__ DEVICE_ACTION_MOVE ; 
 scalar_t__ DEVICE_ACTION_REMOVE ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int device_clone_with_db (int /*<<< orphan*/ *,scalar_t__*) ; 
 int device_ensure_usec_initialized (int /*<<< orphan*/ *,scalar_t__) ; 
 int device_get_action (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  device_set_is_initialized (int /*<<< orphan*/ *) ; 
 int device_tag_index (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int device_update_db (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_execute_rules_on_remove (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int log_device_debug_errno (int /*<<< orphan*/ *,int,char*) ; 
 int log_device_error_errno (int /*<<< orphan*/ *,int,char*) ; 
 int rename_netif (TYPE_1__*) ; 
 scalar_t__ sd_device_get_devnum (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sd_device_get_subsystem (int /*<<< orphan*/ *,char const**) ; 
 scalar_t__ sd_device_unref (scalar_t__) ; 
 int udev_event_on_move (TYPE_1__*) ; 
 int udev_rules_apply_to_event (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udev_watch_end (scalar_t__) ; 
 int update_devnode (TYPE_1__*) ; 

int udev_event_execute_rules(UdevEvent *event,
                             usec_t timeout_usec,
                             Hashmap *properties_list,
                             UdevRules *rules) {
        const char *subsystem;
        DeviceAction action;
        sd_device *dev;
        int r;

        assert(event);
        assert(rules);

        dev = event->dev;

        r = sd_device_get_subsystem(dev, &subsystem);
        if (r < 0)
                return log_device_error_errno(dev, r, "Failed to get subsystem: %m");

        r = device_get_action(dev, &action);
        if (r < 0)
                return log_device_error_errno(dev, r, "Failed to get ACTION: %m");

        if (action == DEVICE_ACTION_REMOVE) {
                event_execute_rules_on_remove(event, timeout_usec, properties_list, rules);
                return 0;
        }

        r = device_clone_with_db(dev, &event->dev_db_clone);
        if (r < 0)
                return log_device_debug_errno(dev, r, "Failed to clone sd_device object: %m");

        if (event->dev_db_clone && sd_device_get_devnum(dev, NULL) >= 0)
                /* Disable watch during event processing. */
                (void) udev_watch_end(event->dev_db_clone);

        if (action == DEVICE_ACTION_MOVE) {
                r = udev_event_on_move(event);
                if (r < 0)
                        return r;
        }

        r = udev_rules_apply_to_event(rules, event, timeout_usec, properties_list);
        if (r < 0)
                return log_device_debug_errno(dev, r, "Failed to apply udev rules: %m");

        r = rename_netif(event);
        if (r < 0)
                return r;

        r = update_devnode(event);
        if (r < 0)
                return r;

        /* preserve old, or get new initialization timestamp */
        r = device_ensure_usec_initialized(dev, event->dev_db_clone);
        if (r < 0)
                return log_device_debug_errno(dev, r, "Failed to set initialization timestamp: %m");

        /* (re)write database file */
        r = device_tag_index(dev, event->dev_db_clone, true);
        if (r < 0)
                return log_device_debug_errno(dev, r, "Failed to update tags under /run/udev/tag/: %m");

        r = device_update_db(dev);
        if (r < 0)
                return log_device_debug_errno(dev, r, "Failed to update database under /run/udev/data/: %m");

        device_set_is_initialized(dev);

        event->dev_db_clone = sd_device_unref(event->dev_db_clone);

        return 0;
}