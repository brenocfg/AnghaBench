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
struct TYPE_5__ {scalar_t__ event_timer; int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  SD_EVENT_ONESHOT ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  clock_boottime_or_monotonic () ; 
 int /*<<< orphan*/  manager_timer ; 
 scalar_t__ now (int /*<<< orphan*/ ) ; 
 int sd_event_add_time (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int sd_event_source_set_enabled (scalar_t__,int /*<<< orphan*/ ) ; 
 int sd_event_source_set_time (scalar_t__,scalar_t__) ; 
 scalar_t__ sd_event_source_unref (scalar_t__) ; 

__attribute__((used)) static int manager_arm_timer(Manager *m, usec_t next) {
        int r;

        assert(m);

        if (next == 0) {
                m->event_timer = sd_event_source_unref(m->event_timer);
                return 0;
        }

        if (m->event_timer) {
                r = sd_event_source_set_time(m->event_timer, now(clock_boottime_or_monotonic()) + next);
                if (r < 0)
                        return r;

                return sd_event_source_set_enabled(m->event_timer, SD_EVENT_ONESHOT);
        }

        return sd_event_add_time(
                        m->event,
                        &m->event_timer,
                        clock_boottime_or_monotonic(),
                        now(clock_boottime_or_monotonic()) + next, 0,
                        manager_timer, m);
}