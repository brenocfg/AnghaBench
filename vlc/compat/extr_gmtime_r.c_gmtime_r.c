#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct tm {int tm_sec; int tm_min; int tm_hour; int tm_wday; int tm_year; scalar_t__ tm_yday; size_t tm_mon; int tm_mday; scalar_t__ tm_isdst; } ;
struct TYPE_3__ {scalar_t__ quot; int rem; } ;
typedef  TYPE_1__ lldiv_t ;

/* Variables and functions */
 TYPE_1__ lldiv (scalar_t__,int) ; 

struct tm *gmtime_r (const time_t *timep, struct tm *tm)
{
    static const unsigned short normal[12] =
        { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    static const unsigned short leap[12] =
        { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    lldiv_t d;
    const unsigned short *months;

    /* Rebase from 1970 Unix epoch to fictitious year 0 (i.e. would-be
     * year 1 BC had the Gregorian calendar already existed then) */
    d.quot = 60LL * 60 * 24 * (4 * 146097 + 135140) + *timep;

    d = lldiv (d.quot, 60); /* 60 seconds per minute */
    if (*timep < 0)
    {
        d.rem += 60;
        d.quot--;
    }
    tm->tm_sec = d.rem;

    d = lldiv (d.quot, 60); /* 60 minutes per hour */
    tm->tm_min = d.rem;

    d = lldiv (d.quot, 24); /* 24 hours per day */
    tm->tm_hour = d.rem;

    tm->tm_wday = (d.quot + 6) % 7; /* 7 days per week */

    d = lldiv (d.quot, 146097); /* 146097 days per 4 centuries */
    tm->tm_year = 400 * d.quot;

    if (d.rem >= 36525)
    {    /* Century with 24 leap years */
        d.rem -= 36525;
        tm->tm_year += 100;

        d = lldiv (d.rem, 36524); /* 36524 days per normal century */
        tm->tm_year += d.quot * 100;
        if (d.rem >= 59) /* not in January or February of year 00 */
            d.rem++; /* insert missing February 29th 00*/
    }
    tm->tm_year -= 1900; /* Rebase to 1900 for struct tm */

    d = lldiv (d.rem, 1461); /* 1461 days per 4 years */
    tm->tm_year += 4 * d.quot;

    if (d.rem >= 366)
    {    /* Non-leap year */
        d.rem -= 366;
        tm->tm_year++;

        d = lldiv (d.rem, 365); /* 365 days per normal year */
        tm->tm_year += d.quot;
        months = normal;
    }
    else
        months = leap;
    tm->tm_yday = d.rem;

    for (tm->tm_mon = 0; d.rem >= months[tm->tm_mon]; tm->tm_mon++)
        d.rem -= months[tm->tm_mon]; /* 28 to 31 days in a month */
    tm->tm_mday = d.rem + 1;

    tm->tm_isdst = 0; /* UTC time */
    return tm;
}