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
struct TYPE_9__ {int pid; TYPE_1__* manager; int /*<<< orphan*/  message; int /*<<< orphan*/  extra_fd; int /*<<< orphan*/  errno_fd; int /*<<< orphan*/  event_source; } ;
struct TYPE_8__ {int /*<<< orphan*/  n_operations; int /*<<< orphan*/  operations; } ;
typedef  TYPE_2__ Operation ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__* mfree (TYPE_2__*) ; 
 int /*<<< orphan*/  operations ; 
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

        return mfree(o);
}