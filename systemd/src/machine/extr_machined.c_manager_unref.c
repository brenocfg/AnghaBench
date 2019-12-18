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
struct TYPE_6__ {scalar_t__ n_operations; int /*<<< orphan*/  event; int /*<<< orphan*/  bus; int /*<<< orphan*/  polkit_registry; int /*<<< orphan*/  nscd_cache_flush_event; int /*<<< orphan*/  image_cache_defer_event; int /*<<< orphan*/  image_cache; int /*<<< orphan*/  machine_leaders; int /*<<< orphan*/  machine_units; int /*<<< orphan*/  machines; scalar_t__ operations; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bus_verify_polkit_async_registry_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap_free (int /*<<< orphan*/ ) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 
 int /*<<< orphan*/  operation_free (scalar_t__) ; 
 int /*<<< orphan*/  sd_bus_flush_close_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Manager* manager_unref(Manager *m) {
        if (!m)
                return NULL;

        while (m->operations)
                operation_free(m->operations);

        assert(m->n_operations == 0);

        hashmap_free(m->machines); /* This will free all machines, so that the machine_units/machine_leaders is empty */
        hashmap_free(m->machine_units);
        hashmap_free(m->machine_leaders);
        hashmap_free(m->image_cache);

        sd_event_source_unref(m->image_cache_defer_event);
        sd_event_source_unref(m->nscd_cache_flush_event);

        bus_verify_polkit_async_registry_free(m->polkit_registry);

        sd_bus_flush_close_unref(m->bus);
        sd_event_unref(m->event);

        return mfree(m);
}