#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  userdata; int /*<<< orphan*/  bus_path; int /*<<< orphan*/  (* unit_callback ) (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ WaitForItem ;
struct TYPE_9__ {int /*<<< orphan*/  items; TYPE_1__* current; int /*<<< orphan*/  bus; int /*<<< orphan*/  slot_disconnected; } ;
typedef  TYPE_2__ BusWaitForUnits ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 TYPE_1__* hashmap_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_bus_slot_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_bus_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_item_free (TYPE_1__*) ; 

__attribute__((used)) static void bus_wait_for_units_clear(BusWaitForUnits *d) {
        WaitForItem *item;

        assert(d);

        d->slot_disconnected = sd_bus_slot_unref(d->slot_disconnected);
        d->bus = sd_bus_unref(d->bus);

        while ((item = hashmap_first(d->items))) {
                d->current = item;

                item->unit_callback(d, item->bus_path, false, item->userdata);
                wait_for_item_free(item);
        }

        d->items = hashmap_free(d->items);
}