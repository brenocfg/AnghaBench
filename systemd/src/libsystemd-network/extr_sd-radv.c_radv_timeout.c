#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int usec_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_11__ {int lifetime; scalar_t__ ra_sent; int /*<<< orphan*/  event_priority; int /*<<< orphan*/  timeout_event_source; struct TYPE_11__* event; } ;
typedef  TYPE_1__ sd_radv ;
typedef  TYPE_1__ sd_event_source ;

/* Variables and functions */
 int FORMAT_TIMESPAN_MAX ; 
 int /*<<< orphan*/  MSEC_PER_SEC ; 
 int SD_RADV_DEFAULT_MAX_TIMEOUT_USEC ; 
 int SD_RADV_DEFAULT_MIN_TIMEOUT_USEC ; 
 scalar_t__ SD_RADV_MAX_INITIAL_RTR_ADVERTISEMENTS ; 
 int SD_RADV_MAX_INITIAL_RTR_ADVERT_INTERVAL_USEC ; 
 int USEC_PER_SEC ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  clock_boottime_or_monotonic () ; 
 int event_reset_time (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int (*) (TYPE_1__*,int /*<<< orphan*/ ,void*),TYPE_1__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  format_timespan (char*,int,int,int) ; 
 int /*<<< orphan*/  log_radv (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_radv_errno (int,char*) ; 
 int radv_compute_timeout (int,int) ; 
 int radv_send (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int sd_event_now (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sd_radv_stop (TYPE_1__*) ; 

__attribute__((used)) static int radv_timeout(sd_event_source *s, uint64_t usec, void *userdata) {
        int r;
        sd_radv *ra = userdata;
        usec_t min_timeout = SD_RADV_DEFAULT_MIN_TIMEOUT_USEC;
        usec_t max_timeout = SD_RADV_DEFAULT_MAX_TIMEOUT_USEC;
        usec_t time_now, timeout;
        char time_string[FORMAT_TIMESPAN_MAX];

        assert(s);
        assert(ra);
        assert(ra->event);

        r = sd_event_now(ra->event, clock_boottime_or_monotonic(), &time_now);
        if (r < 0)
                goto fail;

        r = radv_send(ra, NULL, ra->lifetime);
        if (r < 0)
                log_radv_errno(r, "Unable to send Router Advertisement: %m");

        /* RFC 4861, Section 6.2.4, sending initial Router Advertisements */
        if (ra->ra_sent < SD_RADV_MAX_INITIAL_RTR_ADVERTISEMENTS) {
                max_timeout = SD_RADV_MAX_INITIAL_RTR_ADVERT_INTERVAL_USEC;
                min_timeout = SD_RADV_MAX_INITIAL_RTR_ADVERT_INTERVAL_USEC / 3;
        }

        /* RFC 4861, Section 6.2.1, lifetime must be at least MaxRtrAdvInterval,
           so lower the interval here */
        if (ra->lifetime > 0 && (ra->lifetime * USEC_PER_SEC) < max_timeout) {
                max_timeout = ra->lifetime * USEC_PER_SEC;
                min_timeout = max_timeout / 3;
        }

        timeout = radv_compute_timeout(min_timeout, max_timeout);

        log_radv("Next Router Advertisement in %s",
                 format_timespan(time_string, FORMAT_TIMESPAN_MAX,
                                 timeout, USEC_PER_SEC));

        r = event_reset_time(ra->event, &ra->timeout_event_source,
                             clock_boottime_or_monotonic(),
                             time_now + timeout, MSEC_PER_SEC,
                             radv_timeout, ra,
                             ra->event_priority, "radv-timeout", true);
        if (r < 0)
                goto fail;

        ra->ra_sent++;

        return 0;

fail:
        sd_radv_stop(ra);

        return 0;
}