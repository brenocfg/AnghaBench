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
struct TYPE_6__ {int /*<<< orphan*/  id; int /*<<< orphan*/  bus_track; int /*<<< orphan*/  manager; int /*<<< orphan*/  unit; int /*<<< orphan*/  sent_dbus_new_signal; } ;
typedef  TYPE_1__ Job ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int bus_foreach_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  bus_job_send_change_signal (TYPE_1__*) ; 
 int /*<<< orphan*/  bus_unit_send_pending_change_signal (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  log_debug_errno (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_removed_signal ; 

void bus_job_send_removed_signal(Job *j) {
        int r;

        assert(j);

        if (!j->sent_dbus_new_signal)
                bus_job_send_change_signal(j);

        /* Make sure that any change signal on the unit is reflected before we send out the change signal on the job */
        bus_unit_send_pending_change_signal(j->unit, true);

        r = bus_foreach_bus(j->manager, j->bus_track, send_removed_signal, j);
        if (r < 0)
                log_debug_errno(r, "Failed to send job remove signal for %u: %m", j->id);
}