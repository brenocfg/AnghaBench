#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* in_dbus_queue; } ;
typedef  TYPE_1__ Unit ;
struct TYPE_14__ {TYPE_2__* in_dbus_queue; } ;
struct TYPE_13__ {int send_reloading_done; scalar_t__ pending_reload_message; TYPE_3__* dbus_job_queue; TYPE_1__* dbus_unit_queue; } ;
typedef  TYPE_2__ Manager ;
typedef  TYPE_3__ Job ;

/* Variables and functions */
 scalar_t__ MANAGER_BUS_BUSY_THRESHOLD ; 
 unsigned int MANAGER_BUS_MESSAGE_BUDGET ; 
 scalar_t__ MANAGER_IS_RELOADING (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  bus_job_send_change_signal (TYPE_3__*) ; 
 int /*<<< orphan*/  bus_manager_send_reloading (TYPE_2__*,int) ; 
 int /*<<< orphan*/  bus_send_pending_reload_message (TYPE_2__*) ; 
 int /*<<< orphan*/  bus_unit_send_change_signal (TYPE_1__*) ; 
 scalar_t__ manager_bus_n_queued_write (TYPE_2__*) ; 

__attribute__((used)) static unsigned manager_dispatch_dbus_queue(Manager *m) {
        unsigned n = 0, budget;
        Unit *u;
        Job *j;

        assert(m);

        /* When we are reloading, let's not wait with generating signals, since we need to exit the manager as quickly
         * as we can. There's no point in throttling generation of signals in that case. */
        if (MANAGER_IS_RELOADING(m) || m->send_reloading_done || m->pending_reload_message)
                budget = (unsigned) -1; /* infinite budget in this case */
        else {
                /* Anything to do at all? */
                if (!m->dbus_unit_queue && !m->dbus_job_queue)
                        return 0;

                /* Do we have overly many messages queued at the moment? If so, let's not enqueue more on top, let's
                 * sit this cycle out, and process things in a later cycle when the queues got a bit emptier. */
                if (manager_bus_n_queued_write(m) > MANAGER_BUS_BUSY_THRESHOLD)
                        return 0;

                /* Only process a certain number of units/jobs per event loop iteration. Even if the bus queue wasn't
                 * overly full before this call we shouldn't increase it in size too wildly in one step, and we
                 * shouldn't monopolize CPU time with generating these messages. Note the difference in counting of
                 * this "budget" and the "threshold" above: the "budget" is decreased only once per generated message,
                 * regardless how many buses/direct connections it is enqueued on, while the "threshold" is applied to
                 * each queued instance of bus message, i.e. if the same message is enqueued to five buses/direct
                 * connections it will be counted five times. This difference in counting ("references"
                 * vs. "instances") is primarily a result of the fact that it's easier to implement it this way,
                 * however it also reflects the thinking that the "threshold" should put a limit on used queue memory,
                 * i.e. space, while the "budget" should put a limit on time. Also note that the "threshold" is
                 * currently chosen much higher than the "budget". */
                budget = MANAGER_BUS_MESSAGE_BUDGET;
        }

        while (budget != 0 && (u = m->dbus_unit_queue)) {

                assert(u->in_dbus_queue);

                bus_unit_send_change_signal(u);
                n++;

                if (budget != (unsigned) -1)
                        budget--;
        }

        while (budget != 0 && (j = m->dbus_job_queue)) {
                assert(j->in_dbus_queue);

                bus_job_send_change_signal(j);
                n++;

                if (budget != (unsigned) -1)
                        budget--;
        }

        if (m->send_reloading_done) {
                m->send_reloading_done = false;
                bus_manager_send_reloading(m, false);
                n++;
        }

        if (m->pending_reload_message) {
                bus_send_pending_reload_message(m);
                n++;
        }

        return n;
}