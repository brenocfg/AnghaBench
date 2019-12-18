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
typedef  int usec_t ;
struct TYPE_5__ {int /*<<< orphan*/  event_priority; int /*<<< orphan*/  timer_event_source; int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ sd_ipv4acd ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  clock_boottime_or_monotonic () ; 
 int event_reset_time (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ipv4acd_on_timeout ; 
 scalar_t__ random_u64 () ; 
 scalar_t__ sd_event_now (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int ipv4acd_set_next_wakeup(sd_ipv4acd *acd, usec_t usec, usec_t random_usec) {
        usec_t next_timeout, time_now;

        assert(acd);

        next_timeout = usec;

        if (random_usec > 0)
                next_timeout += (usec_t) random_u64() % random_usec;

        assert_se(sd_event_now(acd->event, clock_boottime_or_monotonic(), &time_now) >= 0);

        return event_reset_time(acd->event, &acd->timer_event_source,
                                clock_boottime_or_monotonic(),
                                time_now + next_timeout, 0,
                                ipv4acd_on_timeout, acd,
                                acd->event_priority, "ipv4acd-timer", true);
}