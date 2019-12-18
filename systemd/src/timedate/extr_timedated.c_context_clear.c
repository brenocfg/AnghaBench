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
typedef  int /*<<< orphan*/  UnitStatusInfo ;
struct TYPE_4__ {int /*<<< orphan*/ * units; int /*<<< orphan*/  slot_job_removed; int /*<<< orphan*/  cache; int /*<<< orphan*/  polkit_registry; int /*<<< orphan*/  zone; } ;
typedef  TYPE_1__ Context ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  bus_verify_polkit_async_registry_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_bus_message_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_bus_slot_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_status_info_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  units ; 

__attribute__((used)) static void context_clear(Context *c) {
        UnitStatusInfo *p;

        assert(c);

        free(c->zone);
        bus_verify_polkit_async_registry_free(c->polkit_registry);
        sd_bus_message_unref(c->cache);

        sd_bus_slot_unref(c->slot_job_removed);

        while ((p = c->units)) {
                LIST_REMOVE(units, c->units, p);
                unit_status_info_free(p);
        }
}