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
typedef  int usec_t ;
typedef  void sd_event_source ;
struct TYPE_6__ {scalar_t__ lldp_tx_fast; } ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 int LLDP_FAST_TX_USEC ; 
 int LLDP_JITTER_USEC ; 
 int LLDP_TX_INTERVAL_USEC ; 
 int /*<<< orphan*/  SD_EVENT_ONESHOT ; 
 int /*<<< orphan*/  assert (void*) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  clock_boottime_or_monotonic () ; 
 int link_send_lldp (TYPE_1__*) ; 
 int /*<<< orphan*/  log_link_debug (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  log_link_debug_errno (TYPE_1__*,int,char*) ; 
 int log_link_error_errno (TYPE_1__*,int,char*) ; 
 scalar_t__ random_u64 () ; 
 scalar_t__ sd_event_now (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sd_event_source_get_event (void*) ; 
 int sd_event_source_set_enabled (void*,int /*<<< orphan*/ ) ; 
 int sd_event_source_set_time (void*,int) ; 
 int usec_add (int,int) ; 

__attribute__((used)) static int on_lldp_timer(sd_event_source *s, usec_t t, void *userdata) {
        Link *link = userdata;
        usec_t current, delay, next;
        int r;

        assert(s);
        assert(userdata);

        log_link_debug(link, "Sending LLDP packet...");

        r = link_send_lldp(link);
        if (r < 0)
                log_link_debug_errno(link, r, "Failed to send LLDP packet, ignoring: %m");

        if (link->lldp_tx_fast > 0)
                link->lldp_tx_fast--;

        assert_se(sd_event_now(sd_event_source_get_event(s), clock_boottime_or_monotonic(), &current) >= 0);

        delay = link->lldp_tx_fast > 0 ? LLDP_FAST_TX_USEC : LLDP_TX_INTERVAL_USEC;
        next = usec_add(usec_add(current, delay), (usec_t) random_u64() % LLDP_JITTER_USEC);

        r = sd_event_source_set_time(s, next);
        if (r < 0)
                return log_link_error_errno(link, r, "Failed to restart LLDP timer: %m");

        r = sd_event_source_set_enabled(s, SD_EVENT_ONESHOT);
        if (r < 0)
                return log_link_error_errno(link, r, "Failed to enable LLDP timer: %m");

        return 0;
}