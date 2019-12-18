#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  bus; int /*<<< orphan*/  slot_disconnected; } ;
typedef  TYPE_1__ BusWaitForUnits ;

/* Variables and functions */
 int /*<<< orphan*/  bus_wait_for_units_clear (TYPE_1__*) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 
 int /*<<< orphan*/  sd_bus_slot_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_bus_unref (int /*<<< orphan*/ ) ; 

BusWaitForUnits* bus_wait_for_units_free(BusWaitForUnits *d) {
        if (!d)
                return NULL;

        bus_wait_for_units_clear(d);
        sd_bus_slot_unref(d->slot_disconnected);
        sd_bus_unref(d->bus);

        return mfree(d);
}