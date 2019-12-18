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
struct TYPE_7__ {TYPE_1__* unit; int /*<<< orphan*/  sent_dbus_new_signal; int /*<<< orphan*/  in_dbus_queue; } ;
struct TYPE_6__ {int /*<<< orphan*/  manager; } ;
typedef  TYPE_2__ Job ;

/* Variables and functions */
 scalar_t__ MANAGER_IS_RELOADING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  bus_job_send_change_signal (TYPE_2__*) ; 

void bus_job_send_pending_change_signal(Job *j, bool including_new) {
        assert(j);

        if (!j->in_dbus_queue)
                return;

        if (!j->sent_dbus_new_signal && !including_new)
                return;

        if (MANAGER_IS_RELOADING(j->unit->manager))
                return;

        bus_job_send_change_signal(j);
}