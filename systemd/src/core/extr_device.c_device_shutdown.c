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
struct TYPE_4__ {int /*<<< orphan*/  devices_by_sysfs; int /*<<< orphan*/  device_monitor; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  hashmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_device_monitor_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void device_shutdown(Manager *m) {
        assert(m);

        m->device_monitor = sd_device_monitor_unref(m->device_monitor);
        m->devices_by_sysfs = hashmap_free(m->devices_by_sysfs);
}