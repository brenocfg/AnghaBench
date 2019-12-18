#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_1__* manager; } ;
struct TYPE_12__ {scalar_t__ sysfs; } ;
struct TYPE_11__ {int /*<<< orphan*/ * devices_by_sysfs; } ;
typedef  int /*<<< orphan*/  Hashmap ;
typedef  TYPE_2__ Device ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*) ; 
 TYPE_7__* UNIT (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 TYPE_2__* hashmap_get (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  hashmap_remove (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  hashmap_remove_and_replace (int /*<<< orphan*/ *,scalar_t__,scalar_t__,TYPE_2__*) ; 
 scalar_t__ mfree (scalar_t__) ; 
 int /*<<< orphan*/  same_sysfs ; 

__attribute__((used)) static void device_unset_sysfs(Device *d) {
        Hashmap *devices;
        Device *first;

        assert(d);

        if (!d->sysfs)
                return;

        /* Remove this unit from the chain of devices which share the
         * same sysfs path. */
        devices = UNIT(d)->manager->devices_by_sysfs;
        first = hashmap_get(devices, d->sysfs);
        LIST_REMOVE(same_sysfs, first, d);

        if (first)
                hashmap_remove_and_replace(devices, d->sysfs, first->sysfs, first);
        else
                hashmap_remove(devices, d->sysfs);

        d->sysfs = mfree(d->sysfs);
}