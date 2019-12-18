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
struct tm {scalar_t__ tm_mon; int tm_mday; } ;

/* Variables and functions */
 scalar_t__ mktime_or_timegm (struct tm*,int) ; 

__attribute__((used)) static int find_end_of_month(struct tm *tm, bool utc, int day) {
        struct tm t = *tm;

        t.tm_mon++;
        t.tm_mday = 1 - day;

        if (mktime_or_timegm(&t, utc) < 0 ||
            t.tm_mon != tm->tm_mon)
                return -1;

        return t.tm_mday;
}