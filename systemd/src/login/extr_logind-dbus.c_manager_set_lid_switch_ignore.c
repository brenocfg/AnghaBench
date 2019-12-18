#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ usec_t ;
struct TYPE_5__ {scalar_t__ lid_switch_ignore_event_source; int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  lid_switch_ignore_handler ; 
 scalar_t__ now (int /*<<< orphan*/ ) ; 
 int sd_event_add_time (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int sd_event_source_get_time (scalar_t__,scalar_t__*) ; 
 int sd_event_source_set_time (scalar_t__,scalar_t__) ; 

int manager_set_lid_switch_ignore(Manager *m, usec_t until) {
        int r;

        assert(m);

        if (until <= now(CLOCK_MONOTONIC))
                return 0;

        /* We want to ignore the lid switch for a while after each
         * suspend, and after boot-up. Hence let's install a timer for
         * this. As long as the event source exists we ignore the lid
         * switch. */

        if (m->lid_switch_ignore_event_source) {
                usec_t u;

                r = sd_event_source_get_time(m->lid_switch_ignore_event_source, &u);
                if (r < 0)
                        return r;

                if (until <= u)
                        return 0;

                r = sd_event_source_set_time(m->lid_switch_ignore_event_source, until);
        } else
                r = sd_event_add_time(
                                m->event,
                                &m->lid_switch_ignore_event_source,
                                CLOCK_MONOTONIC,
                                until, 0,
                                lid_switch_ignore_handler, m);

        return r;
}