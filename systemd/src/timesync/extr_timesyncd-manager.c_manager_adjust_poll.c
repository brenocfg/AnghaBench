#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int poll_resync; int poll_interval_usec; int poll_interval_min_usec; int poll_interval_max_usec; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 double NTP_ACCURACY_SEC ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 double fabs (double) ; 

__attribute__((used)) static void manager_adjust_poll(Manager *m, double offset, bool spike) {
        assert(m);

        if (m->poll_resync) {
                m->poll_interval_usec = m->poll_interval_min_usec;
                m->poll_resync = false;
                return;
        }

        /* set to minimal poll interval */
        if (!spike && fabs(offset) > NTP_ACCURACY_SEC) {
                m->poll_interval_usec = m->poll_interval_min_usec;
                return;
        }

        /* increase polling interval */
        if (fabs(offset) < NTP_ACCURACY_SEC * 0.25) {
                if (m->poll_interval_usec < m->poll_interval_max_usec)
                        m->poll_interval_usec *= 2;
                return;
        }

        /* decrease polling interval */
        if (spike || fabs(offset) > NTP_ACCURACY_SEC * 0.75) {
                if (m->poll_interval_usec > m->poll_interval_min_usec)
                        m->poll_interval_usec /= 2;
                return;
        }
}