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
typedef  struct tm {int tm_year; int tm_mon; int tm_mday; int tm_hour; int tm_min; int tm_sec; int /*<<< orphan*/  utc; int /*<<< orphan*/  microsecond; int /*<<< orphan*/  minute; int /*<<< orphan*/  hour; int /*<<< orphan*/  weekdays_bits; int /*<<< orphan*/  day; int /*<<< orphan*/  month; int /*<<< orphan*/  year; int /*<<< orphan*/  dst; int /*<<< orphan*/  tm_isdst; } const tm ;
typedef  struct tm CalendarSpec ;

/* Variables and functions */
 int ENOENT ; 
 int USEC_PER_SEC ; 
 int /*<<< orphan*/  assert (struct tm const*) ; 
 int find_matching_component (struct tm const*,int /*<<< orphan*/ ,struct tm const*,int*) ; 
 int /*<<< orphan*/  matches_weekday (int /*<<< orphan*/ ,struct tm const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mktime_or_timegm (struct tm const*,int /*<<< orphan*/ ) ; 
 int tm_within_bounds (struct tm const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int find_next(const CalendarSpec *spec, struct tm *tm, usec_t *usec) {
        struct tm c;
        int tm_usec;
        int r;

        /* Returns -ENOENT if the expression is not going to elapse anymore */

        assert(spec);
        assert(tm);

        c = *tm;
        tm_usec = *usec;

        for (;;) {
                /* Normalize the current date */
                (void) mktime_or_timegm(&c, spec->utc);
                c.tm_isdst = spec->dst;

                c.tm_year += 1900;
                r = find_matching_component(spec, spec->year, &c, &c.tm_year);
                c.tm_year -= 1900;

                if (r > 0) {
                        c.tm_mon = 0;
                        c.tm_mday = 1;
                        c.tm_hour = c.tm_min = c.tm_sec = tm_usec = 0;
                }
                if (r < 0)
                        return r;
                if (tm_within_bounds(&c, spec->utc) <= 0)
                        return -ENOENT;

                c.tm_mon += 1;
                r = find_matching_component(spec, spec->month, &c, &c.tm_mon);
                c.tm_mon -= 1;

                if (r > 0) {
                        c.tm_mday = 1;
                        c.tm_hour = c.tm_min = c.tm_sec = tm_usec = 0;
                }
                if (r < 0 || (r = tm_within_bounds(&c, spec->utc)) < 0) {
                        c.tm_year++;
                        c.tm_mon = 0;
                        c.tm_mday = 1;
                        c.tm_hour = c.tm_min = c.tm_sec = tm_usec = 0;
                        continue;
                }
                if (r == 0)
                        continue;

                r = find_matching_component(spec, spec->day, &c, &c.tm_mday);
                if (r > 0)
                        c.tm_hour = c.tm_min = c.tm_sec = tm_usec = 0;
                if (r < 0 || (r = tm_within_bounds(&c, spec->utc)) < 0) {
                        c.tm_mon++;
                        c.tm_mday = 1;
                        c.tm_hour = c.tm_min = c.tm_sec = tm_usec = 0;
                        continue;
                }
                if (r == 0)
                        continue;

                if (!matches_weekday(spec->weekdays_bits, &c, spec->utc)) {
                        c.tm_mday++;
                        c.tm_hour = c.tm_min = c.tm_sec = tm_usec = 0;
                        continue;
                }

                r = find_matching_component(spec, spec->hour, &c, &c.tm_hour);
                if (r > 0)
                        c.tm_min = c.tm_sec = tm_usec = 0;
                if (r < 0 || (r = tm_within_bounds(&c, spec->utc)) < 0) {
                        c.tm_mday++;
                        c.tm_hour = c.tm_min = c.tm_sec = tm_usec = 0;
                        continue;
                }
                if (r == 0)
                        /* The next hour we set might be missing if there
                         * are time zone changes. Let's try again starting at
                         * normalized time. */
                        continue;

                r = find_matching_component(spec, spec->minute, &c, &c.tm_min);
                if (r > 0)
                        c.tm_sec = tm_usec = 0;
                if (r < 0 || (r = tm_within_bounds(&c, spec->utc)) < 0) {
                        c.tm_hour++;
                        c.tm_min = c.tm_sec = tm_usec = 0;
                        continue;
                }
                if (r == 0)
                        continue;

                c.tm_sec = c.tm_sec * USEC_PER_SEC + tm_usec;
                r = find_matching_component(spec, spec->microsecond, &c, &c.tm_sec);
                tm_usec = c.tm_sec % USEC_PER_SEC;
                c.tm_sec /= USEC_PER_SEC;

                if (r < 0 || (r = tm_within_bounds(&c, spec->utc)) < 0) {
                        c.tm_min++;
                        c.tm_sec = tm_usec = 0;
                        continue;
                }
                if (r == 0)
                        continue;

                *tm = c;
                *usec = tm_usec;
                return 0;
        }
}