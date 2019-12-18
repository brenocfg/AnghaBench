#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ usec_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_10__ {int retransmit_time; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  fd; int /*<<< orphan*/  event_priority; int /*<<< orphan*/  timeout_event_source; struct TYPE_10__* event; } ;
typedef  TYPE_1__ sd_ndisc ;
typedef  TYPE_1__ sd_event_source ;

/* Variables and functions */
 int FORMAT_TIMESPAN_MAX ; 
 int NDISC_MAX_ROUTER_SOLICITATION_INTERVAL ; 
 int NDISC_ROUTER_SOLICITATION_INTERVAL ; 
 int USEC_PER_MSEC ; 
 int /*<<< orphan*/  USEC_PER_SEC ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  clock_boottime_or_monotonic () ; 
 int event_reset_time (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int,int (*) (TYPE_1__*,int /*<<< orphan*/ ,void*),TYPE_1__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  format_timespan (char*,int,int,int /*<<< orphan*/ ) ; 
 int icmp6_send_router_solicitation (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_ndisc (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_ndisc_errno (int,char*) ; 
 void* ndisc_timeout_compute_random (int) ; 
 scalar_t__ sd_event_now (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  sd_ndisc_stop (TYPE_1__*) ; 

__attribute__((used)) static int ndisc_timeout(sd_event_source *s, uint64_t usec, void *userdata) {
        char time_string[FORMAT_TIMESPAN_MAX];
        sd_ndisc *nd = userdata;
        usec_t time_now;
        int r;

        assert(s);
        assert(nd);
        assert(nd->event);

        assert_se(sd_event_now(nd->event, clock_boottime_or_monotonic(), &time_now) >= 0);

        if (!nd->retransmit_time)
                nd->retransmit_time = ndisc_timeout_compute_random(NDISC_ROUTER_SOLICITATION_INTERVAL);
        else {
                if (nd->retransmit_time > NDISC_MAX_ROUTER_SOLICITATION_INTERVAL / 2)
                        nd->retransmit_time = ndisc_timeout_compute_random(NDISC_MAX_ROUTER_SOLICITATION_INTERVAL);
                else
                        nd->retransmit_time += ndisc_timeout_compute_random(nd->retransmit_time);
        }

        r = event_reset_time(nd->event, &nd->timeout_event_source,
                             clock_boottime_or_monotonic(),
                             time_now + nd->retransmit_time, 10 * USEC_PER_MSEC,
                             ndisc_timeout, nd,
                             nd->event_priority, "ndisc-timeout-no-ra", true);
        if (r < 0)
                goto fail;

        r = icmp6_send_router_solicitation(nd->fd, &nd->mac_addr);
        if (r < 0) {
                log_ndisc_errno(r, "Error sending Router Solicitation: %m");
                goto fail;
        }

        log_ndisc("Sent Router Solicitation, next solicitation in %s",
                  format_timespan(time_string, FORMAT_TIMESPAN_MAX,
                                  nd->retransmit_time, USEC_PER_SEC));

        return 0;

fail:
        (void) sd_ndisc_stop(nd);
        return 0;
}