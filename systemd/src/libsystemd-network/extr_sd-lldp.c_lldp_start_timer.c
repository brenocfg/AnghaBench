#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  until; } ;
typedef  TYPE_1__ sd_lldp_neighbor ;
struct TYPE_10__ {int /*<<< orphan*/  event_priority; int /*<<< orphan*/  timer_event_source; int /*<<< orphan*/  event; int /*<<< orphan*/  neighbor_by_expiry; } ;
typedef  TYPE_2__ sd_lldp ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  clock_boottime_or_monotonic () ; 
 int event_reset_time (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,char*,int) ; 
 int event_source_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lldp_neighbor_start_ttl (TYPE_1__*) ; 
 int /*<<< orphan*/  on_timer_event ; 
 TYPE_1__* prioq_peek (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lldp_start_timer(sd_lldp *lldp, sd_lldp_neighbor *neighbor) {
        sd_lldp_neighbor *n;

        assert(lldp);

        if (neighbor)
                lldp_neighbor_start_ttl(neighbor);

        n = prioq_peek(lldp->neighbor_by_expiry);
        if (!n)
                return event_source_disable(lldp->timer_event_source);

        if (!lldp->event)
                return 0;

        return event_reset_time(lldp->event, &lldp->timer_event_source,
                                clock_boottime_or_monotonic(),
                                n->until, 0,
                                on_timer_event, lldp,
                                lldp->event_priority, "lldp-timer", true);
}