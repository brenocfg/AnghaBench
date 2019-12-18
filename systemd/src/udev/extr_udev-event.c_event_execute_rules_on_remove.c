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
typedef  int /*<<< orphan*/  usec_t ;
typedef  int /*<<< orphan*/  sd_device ;
typedef  int /*<<< orphan*/  UdevRules ;
struct TYPE_4__ {int /*<<< orphan*/ * dev; } ;
typedef  TYPE_1__ UdevEvent ;
typedef  int /*<<< orphan*/  Hashmap ;

/* Variables and functions */
 int device_delete_db (int /*<<< orphan*/ *) ; 
 int device_read_db_internal (int /*<<< orphan*/ *,int) ; 
 int device_tag_index (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  log_device_debug_errno (int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ sd_device_get_devnum (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udev_node_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udev_rules_apply_to_event (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udev_watch_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void event_execute_rules_on_remove(
                UdevEvent *event,
                usec_t timeout_usec,
                Hashmap *properties_list,
                UdevRules *rules) {

        sd_device *dev = event->dev;
        int r;

        r = device_read_db_internal(dev, true);
        if (r < 0)
                log_device_debug_errno(dev, r, "Failed to read database under /run/udev/data/: %m");

        r = device_tag_index(dev, NULL, false);
        if (r < 0)
                log_device_debug_errno(dev, r, "Failed to remove corresponding tag files under /run/udev/tag/, ignoring: %m");

        r = device_delete_db(dev);
        if (r < 0)
                log_device_debug_errno(dev, r, "Failed to delete database under /run/udev/data/, ignoring: %m");

        if (sd_device_get_devnum(dev, NULL) >= 0)
                (void) udev_watch_end(dev);

        (void) udev_rules_apply_to_event(rules, event, timeout_usec, properties_list);

        if (sd_device_get_devnum(dev, NULL) >= 0)
                (void) udev_node_remove(dev);
}