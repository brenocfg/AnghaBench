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
typedef  int /*<<< orphan*/  Transfer ;
struct TYPE_6__ {int /*<<< orphan*/  event; int /*<<< orphan*/  bus; int /*<<< orphan*/  polkit_registry; int /*<<< orphan*/  transfers; int /*<<< orphan*/  notify_fd; int /*<<< orphan*/  notify_event_source; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  bus_verify_polkit_async_registry_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hashmap_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap_free (int /*<<< orphan*/ ) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_bus_flush_close_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transfer_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static Manager *manager_unref(Manager *m) {
        Transfer *t;

        if (!m)
                return NULL;

        sd_event_source_unref(m->notify_event_source);
        safe_close(m->notify_fd);

        while ((t = hashmap_first(m->transfers)))
                transfer_unref(t);

        hashmap_free(m->transfers);

        bus_verify_polkit_async_registry_free(m->polkit_registry);

        m->bus = sd_bus_flush_close_unref(m->bus);
        sd_event_unref(m->event);

        return mfree(m);
}