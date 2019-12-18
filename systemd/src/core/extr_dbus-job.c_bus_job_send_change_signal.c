#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  dbus_job_queue; } ;
struct TYPE_7__ {int in_dbus_queue; int sent_dbus_new_signal; int /*<<< orphan*/  id; int /*<<< orphan*/  bus_track; TYPE_3__* manager; int /*<<< orphan*/  unit; } ;
typedef  TYPE_1__ Job ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int bus_foreach_bus (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  bus_unit_send_pending_change_signal (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dbus_queue ; 
 int /*<<< orphan*/  log_debug_errno (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_changed_signal ; 
 int /*<<< orphan*/  send_new_signal ; 

void bus_job_send_change_signal(Job *j) {
        int r;

        assert(j);

        /* Make sure that any change signal on the unit is reflected before we send out the change signal on the job */
        bus_unit_send_pending_change_signal(j->unit, true);

        if (j->in_dbus_queue) {
                LIST_REMOVE(dbus_queue, j->manager->dbus_job_queue, j);
                j->in_dbus_queue = false;
        }

        r = bus_foreach_bus(j->manager, j->bus_track, j->sent_dbus_new_signal ? send_changed_signal : send_new_signal, j);
        if (r < 0)
                log_debug_errno(r, "Failed to send job change signal for %u: %m", j->id);

        j->sent_dbus_new_signal = true;
}