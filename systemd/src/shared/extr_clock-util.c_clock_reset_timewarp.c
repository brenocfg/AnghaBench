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
struct timezone {scalar_t__ tz_dsttime; scalar_t__ tz_minuteswest; } ;
struct timeval {int dummy; } ;

/* Variables and functions */
 int errno ; 
 scalar_t__ settimeofday (struct timeval const*,struct timezone*) ; 

int clock_reset_timewarp(void) {
        const struct timeval *tv_null = NULL;
        struct timezone tz;

        tz.tz_minuteswest = 0;
        tz.tz_dsttime = 0; /* DST_NONE */

        /*
         * The very first call to settimeofday() does time warp magic. Do a
         * dummy call here, so the time warping is sealed and all later calls
         * behave as expected.
         */
        if (settimeofday(tv_null, &tz) < 0)
                return -errno;

        return 0;
}