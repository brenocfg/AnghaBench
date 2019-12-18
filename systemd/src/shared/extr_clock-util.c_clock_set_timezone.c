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
struct tm {int tm_gmtoff; } ;
struct timezone {int tz_minuteswest; scalar_t__ tz_dsttime; } ;
struct timeval {int dummy; } ;
struct timespec {int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int localtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 int negative_errno () ; 
 scalar_t__ settimeofday (struct timeval const*,struct timezone*) ; 

int clock_set_timezone(int *min) {
        const struct timeval *tv_null = NULL;
        struct timespec ts;
        struct tm tm;
        int minutesdelta;
        struct timezone tz;

        assert_se(clock_gettime(CLOCK_REALTIME, &ts) == 0);
        assert_se(localtime_r(&ts.tv_sec, &tm));
        minutesdelta = tm.tm_gmtoff / 60;

        tz.tz_minuteswest = -minutesdelta;
        tz.tz_dsttime = 0; /* DST_NONE */

        /*
         * If the RTC does not run in UTC but in local time, the very first
         * call to settimeofday() will set the kernel's timezone and will warp the
         * system clock, so that it runs in UTC instead of the local time we
         * have read from the RTC.
         */
        if (settimeofday(tv_null, &tz) < 0)
                return negative_errno();

        if (min)
                *min = minutesdelta;
        return 0;
}