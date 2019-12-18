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
struct tm {scalar_t__ tm_year; scalar_t__ tm_mon; scalar_t__ tm_mday; scalar_t__ tm_hour; scalar_t__ tm_min; scalar_t__ tm_sec; } ;

/* Variables and functions */
 int ERANGE ; 
 scalar_t__ MAX_YEAR ; 
 int /*<<< orphan*/  assert (struct tm*) ; 
 scalar_t__ mktime_or_timegm (struct tm*,int) ; 
 int negative_errno () ; 

__attribute__((used)) static int tm_within_bounds(struct tm *tm, bool utc) {
        struct tm t;
        assert(tm);

        /*
         * Set an upper bound on the year so impossible dates like "*-02-31"
         * don't cause find_next() to loop forever. tm_year contains years
         * since 1900, so adjust it accordingly.
         */
        if (tm->tm_year + 1900 > MAX_YEAR)
                return -ERANGE;

        t = *tm;
        if (mktime_or_timegm(&t, utc) < 0)
                return negative_errno();

        /* Did any normalization take place? If so, it was out of bounds before */
        bool good = t.tm_year == tm->tm_year &&
                    t.tm_mon  == tm->tm_mon  &&
                    t.tm_mday == tm->tm_mday &&
                    t.tm_hour == tm->tm_hour &&
                    t.tm_min  == tm->tm_min  &&
                    t.tm_sec  == tm->tm_sec;
        if (!good)
                *tm = t;
        return good;
}