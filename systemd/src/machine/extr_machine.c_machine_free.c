#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ leader; int /*<<< orphan*/  netif; int /*<<< orphan*/  root_directory; int /*<<< orphan*/  service; int /*<<< orphan*/  state_file; int /*<<< orphan*/  name; int /*<<< orphan*/  create_message; TYPE_1__* manager; int /*<<< orphan*/  scope_job; scalar_t__ in_gc_queue; scalar_t__ operations; } ;
struct TYPE_10__ {int /*<<< orphan*/  machine_leaders; TYPE_2__* host_machine; int /*<<< orphan*/  machines; int /*<<< orphan*/  machine_gc_queue; } ;
typedef  TYPE_2__ Machine ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  PID_TO_PTR (scalar_t__) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gc_queue ; 
 int /*<<< orphan*/  hashmap_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap_remove_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  machine_release_unit (TYPE_2__*) ; 
 TYPE_2__* mfree (TYPE_2__*) ; 
 int /*<<< orphan*/  operation_free (scalar_t__) ; 
 int /*<<< orphan*/  sd_bus_message_unref (int /*<<< orphan*/ ) ; 

Machine* machine_free(Machine *m) {
        if (!m)
                return NULL;

        while (m->operations)
                operation_free(m->operations);

        if (m->in_gc_queue)
                LIST_REMOVE(gc_queue, m->manager->machine_gc_queue, m);

        machine_release_unit(m);

        free(m->scope_job);

        (void) hashmap_remove(m->manager->machines, m->name);

        if (m->manager->host_machine == m)
                m->manager->host_machine = NULL;

        if (m->leader > 0)
                (void) hashmap_remove_value(m->manager->machine_leaders, PID_TO_PTR(m->leader), m);

        sd_bus_message_unref(m->create_message);

        free(m->name);
        free(m->state_file);
        free(m->service);
        free(m->root_directory);
        free(m->netif);
        return mfree(m);
}