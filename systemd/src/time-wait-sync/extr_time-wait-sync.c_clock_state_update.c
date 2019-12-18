#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usec_t ;
struct TYPE_7__ {int tv_usec; } ;
struct timex {int status; TYPE_2__ time; } ;
typedef  int /*<<< orphan*/  sd_event ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_6__ {int timerfd_fd; int adjtime_state; int has_watchfile; int /*<<< orphan*/  timerfd_event_source; } ;
typedef  TYPE_1__ ClockState ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLLIN ; 
 int /*<<< orphan*/  FORMAT_TIMESTAMP_MAX ; 
 int /*<<< orphan*/  F_OK ; 
 int MAX (size_t,int /*<<< orphan*/ ) ; 
 int STA_NANO ; 
 int /*<<< orphan*/  STRLEN (char*) ; 
 int TIME_ERROR ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int adjtimex (struct timex*) ; 
 int /*<<< orphan*/  clock_state_release_timerfd (TYPE_1__*) ; 
 int errno ; 
 char* format_timestamp_us_utc (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_error_errno (int,char*) ; 
 int /*<<< orphan*/  log_info (char*,int,int,char const*) ; 
 int sd_event_add_io (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  sd_event_exit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int time_change_fd () ; 
 int /*<<< orphan*/  timerfd_handler ; 
 int /*<<< orphan*/  timeval_load (TYPE_2__*) ; 

__attribute__((used)) static int clock_state_update(
                ClockState *sp,
                sd_event *event) {

        char buf[MAX((size_t)FORMAT_TIMESTAMP_MAX, STRLEN("unrepresentable"))];
        struct timex tx = {};
        const char * ts;
        usec_t t;
        int r;

        clock_state_release_timerfd(sp);

        /* The kernel supports cancelling timers whenever its realtime clock is "set" (which can happen in a variety of
         * ways, generally adjustments of at least 500 ms). The way this module works is we set up a timerfd that will
         * wake when the clock is set, and when that happens we read the clock synchronization state from the return
         * value of adjtimex(2), which supports the NTP time adjustment protocol.
         *
         * The kernel determines whether the clock is synchronized using driver-specific tests, based on time
         * information passed by an application, generally through adjtimex(2). If the application asserts the clock is
         * synchronized, but does not also do something that "sets the clock", the timer will not be cancelled and
         * synchronization will not be detected.
         *
         * Similarly, this service will never complete if the application sets the time without also providing
         * information that adjtimex(2) can use to determine that the clock is synchronized. This generally doesn't
         * happen, but can if the system has a hardware clock that is accurate enough that the adjustment is too small
         * to be a "set".
         *
         * Both these failure-to-detect situations are covered by having the presence/creation of
         * /run/systemd/timesync/synchronized, which is considered sufficient to indicate a synchronized clock even if
         * the kernel has not been updated.
         *
         * For timesyncd the initial setting of the time uses settimeofday(2), which sets the clock but does not mark
         * it synchronized. When an NTP source is selected it sets the clock again with clock_adjtime(2) which marks it
         * synchronized and also touches /run/systemd/timesync/synchronized which covers the case when the clock wasn't
         * "set". */

        r = time_change_fd();
        if (r < 0) {
                log_error_errno(r, "Failed to create timerfd: %m");
                goto finish;
        }
        sp->timerfd_fd = r;

        r = adjtimex(&tx);
        if (r < 0) {
                log_error_errno(errno, "Failed to read adjtimex state: %m");
                goto finish;
        }
        sp->adjtime_state = r;

        if (tx.status & STA_NANO)
                tx.time.tv_usec /= 1000;
        t = timeval_load(&tx.time);
        ts = format_timestamp_us_utc(buf, sizeof(buf), t);
        if (!ts)
                strcpy(buf, "unrepresentable");
        log_info("adjtime state %d status %x time %s", sp->adjtime_state, tx.status, ts);

        sp->has_watchfile = access("/run/systemd/timesync/synchronized", F_OK) >= 0;
        if (sp->has_watchfile)
                /* Presence of watch file overrides adjtime_state */
                r = 0;
        else if (sp->adjtime_state == TIME_ERROR) {
                /* Not synchronized.  Do a one-shot wait on the descriptor and inform the caller we need to keep
                 * running. */
                r = sd_event_add_io(event, &sp->timerfd_event_source, sp->timerfd_fd,
                                    EPOLLIN, timerfd_handler, sp);
                if (r < 0) {
                        log_error_errno(r, "Failed to create time change monitor source: %m");
                        goto finish;
                }
                r = 1;
        } else
                /* Synchronized; we can exit. */
                r = 0;

 finish:
        if (r <= 0)
                (void) sd_event_exit(event, r);
        return r;
}