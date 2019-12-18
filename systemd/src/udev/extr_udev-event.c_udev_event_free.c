#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  name; int /*<<< orphan*/  program_result; int /*<<< orphan*/  seclabel_list; int /*<<< orphan*/  run_list; int /*<<< orphan*/  rtnl; int /*<<< orphan*/  dev_db_clone; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ UdevEvent ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 
 int /*<<< orphan*/  ordered_hashmap_free_free_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ordered_hashmap_free_free_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_device_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_netlink_unref (int /*<<< orphan*/ ) ; 

UdevEvent *udev_event_free(UdevEvent *event) {
        if (!event)
                return NULL;

        sd_device_unref(event->dev);
        sd_device_unref(event->dev_db_clone);
        sd_netlink_unref(event->rtnl);
        ordered_hashmap_free_free_key(event->run_list);
        ordered_hashmap_free_free_free(event->seclabel_list);
        free(event->program_result);
        free(event->name);

        return mfree(event);
}