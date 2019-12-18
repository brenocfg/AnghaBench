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
struct tm {int tm_wday; } ;

/* Variables and functions */
 int BITS_WEEKDAYS ; 
 scalar_t__ mktime_or_timegm (struct tm*,int) ; 

__attribute__((used)) static bool matches_weekday(int weekdays_bits, const struct tm *tm, bool utc) {
        struct tm t;
        int k;

        if (weekdays_bits < 0 || weekdays_bits >= BITS_WEEKDAYS)
                return true;

        t = *tm;
        if (mktime_or_timegm(&t, utc) < 0)
                return false;

        k = t.tm_wday == 0 ? 6 : t.tm_wday - 1;
        return (weekdays_bits & (1 << k));
}