#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int pid; TYPE_2__* machine; TYPE_1__* manager; int /*<<< orphan*/  message; int /*<<< orphan*/  extra_fd; int /*<<< orphan*/  errno_fd; int /*<<< orphan*/  event_source; } ;
struct TYPE_10__ {int /*<<< orphan*/  operations; } ;
struct TYPE_9__ {int /*<<< orphan*/  n_operations; int /*<<< orphan*/  operations; } ;
typedef  TYPE_3__ Operation ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_3__* mfree (TYPE_3__*) ; 
 int /*<<< orphan*/  operations ; 
 int /*<<< orphan*/  operations_by_machine ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_bus_message_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigkill_wait (int) ; 

Operation *operation_free(Operation *o) {
        if (!o)
                return NULL;

        sd_event_source_unref(o->event_source);

        safe_close(o->errno_fd);
        safe_close(o->extra_fd);

        if (o->pid > 1)
                (void) sigkill_wait(o->pid);

        sd_bus_message_unref(o->message);

        if (o->manager) {
                LIST_REMOVE(operations, o->manager->operations, o);
                o->manager->n_operations--;
        }

        if (o->machine)
                LIST_REMOVE(operations_by_machine, o->machine->operations, o);

        return mfree(o);
}