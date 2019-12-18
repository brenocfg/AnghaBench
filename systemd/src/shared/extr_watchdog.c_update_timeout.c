#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int usec_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_UP (int,int) ; 
 int ENOTTY ; 
 int FORMAT_TIMESPAN_MAX ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int USEC_INFINITY ; 
 int USEC_PER_SEC ; 
 int /*<<< orphan*/  WDIOC_KEEPALIVE ; 
 int /*<<< orphan*/  WDIOC_SETOPTIONS ; 
 int /*<<< orphan*/  WDIOC_SETTIMEOUT ; 
 int WDIOS_DISABLECARD ; 
 int WDIOS_ENABLECARD ; 
 int errno ; 
 int /*<<< orphan*/  format_timespan (char*,int,int,int /*<<< orphan*/ ) ; 
 int ioctl (scalar_t__,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  log_full (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  log_info (char*,int /*<<< orphan*/ ) ; 
 int log_warning_errno (int,char*,...) ; 
 scalar_t__ watchdog_fd ; 
 int watchdog_timeout ; 

__attribute__((used)) static int update_timeout(void) {
        int r;

        if (watchdog_fd < 0)
                return 0;

        if (watchdog_timeout == USEC_INFINITY)
                return 0;
        else if (watchdog_timeout == 0) {
                int flags;

                flags = WDIOS_DISABLECARD;
                r = ioctl(watchdog_fd, WDIOC_SETOPTIONS, &flags);
                if (r < 0)
                        return log_warning_errno(errno, "Failed to disable hardware watchdog: %m");
        } else {
                int sec, flags;
                char buf[FORMAT_TIMESPAN_MAX];

                sec = (int) DIV_ROUND_UP(watchdog_timeout, USEC_PER_SEC);
                r = ioctl(watchdog_fd, WDIOC_SETTIMEOUT, &sec);
                if (r < 0)
                        return log_warning_errno(errno, "Failed to set timeout to %is: %m", sec);

                watchdog_timeout = (usec_t) sec * USEC_PER_SEC;
                log_info("Set hardware watchdog to %s.", format_timespan(buf, sizeof(buf), watchdog_timeout, 0));

                flags = WDIOS_ENABLECARD;
                r = ioctl(watchdog_fd, WDIOC_SETOPTIONS, &flags);
                if (r < 0) {
                        /* ENOTTY means the watchdog is always enabled so we're fine */
                        log_full(errno == ENOTTY ? LOG_DEBUG : LOG_WARNING,
                                 "Failed to enable hardware watchdog: %m");
                        if (errno != ENOTTY)
                                return -errno;
                }

                r = ioctl(watchdog_fd, WDIOC_KEEPALIVE, 0);
                if (r < 0)
                        return log_warning_errno(errno, "Failed to ping hardware watchdog: %m");
        }

        return 0;
}