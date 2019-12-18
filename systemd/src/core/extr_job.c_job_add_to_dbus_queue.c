#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int in_dbus_queue; TYPE_1__* manager; struct TYPE_7__* installed; } ;
struct TYPE_6__ {int /*<<< orphan*/  dbus_job_queue; } ;
typedef  TYPE_2__ Job ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_PREPEND (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  dbus_queue ; 

void job_add_to_dbus_queue(Job *j) {
        assert(j);
        assert(j->installed);

        if (j->in_dbus_queue)
                return;

        /* We don't check if anybody is subscribed here, since this
         * job might just have been created and not yet assigned to a
         * connection/client. */

        LIST_PREPEND(dbus_queue, j->manager->dbus_job_queue, j);
        j->in_dbus_queue = true;
}