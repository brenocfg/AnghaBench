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
struct tm {unsigned int tm_year; int tm_isdst; unsigned int tm_yday; unsigned int tm_mon; int tm_mday; unsigned int tm_wday; unsigned int tm_hour; unsigned int tm_min; unsigned int tm_sec; } ;
typedef  unsigned int __time64_t ;

/* Variables and functions */
 scalar_t__ DIFFDAYS ; 
 unsigned int SECONDSPERDAY ; 
 unsigned int SECONDSPERHOUR ; 
 scalar_t__ _dstbias ; 
 int dst_begin ; 
 int dst_end ; 
 unsigned int* g_lpmonthdays ; 
 unsigned int* g_monthdays ; 
 unsigned int leapdays_passed (unsigned int) ; 
 unsigned int leapyears_passed (unsigned int) ; 

struct tm *
_gmtime_worker(struct tm *ptm, __time64_t time, int do_dst)
{
    unsigned int days, daystoyear, dayinyear, leapdays, leapyears, years, month;
    unsigned int secondinday, secondinhour;
    unsigned int *padays;

    if (time < 0)
    {
        return 0;
    }

    /* Divide into date and time */
    days = (unsigned int)(time / SECONDSPERDAY);
    secondinday = time % SECONDSPERDAY;

    /* Shift to days from 1.1.1601 */
    days += DIFFDAYS;

    /* Calculate leap days passed till today */
    leapdays = leapdays_passed(days);

    /* Calculate number of full leap years passed */
    leapyears = leapyears_passed(days);

    /* Are more leap days passed than leap years? */
    if (leapdays > leapyears)
    {
        /* Yes, we're in a leap year */
        padays = g_lpmonthdays;
    }
    else
    {
        /* No, normal year */
        padays = g_monthdays;
    }

    /* Calculate year */
    years = (days - leapdays) / 365;
    ptm->tm_year = years - 299;

    /* Calculate number of days till 1.1. of this year */
    daystoyear = years * 365 + leapyears;

    /* Calculate the day in this year */
    dayinyear = days - daystoyear;

    /* Shall we do DST corrections? */
    ptm->tm_isdst = 0;
    if (do_dst)
    {
        int yeartime = dayinyear * SECONDSPERDAY + secondinday ;
        if (yeartime >= dst_begin && yeartime <= dst_end) // FIXME! DST in winter
        {
            time -= _dstbias;
            days = (unsigned int)(time / SECONDSPERDAY + DIFFDAYS);
            dayinyear = days - daystoyear;
            ptm->tm_isdst = 1;
        }
    }

    ptm->tm_yday = dayinyear;

    /* dayinyear < 366 => terminates with i <= 11 */
    for (month = 0; dayinyear >= padays[month+1]; month++)
        ;

    /* Set month and day in month */
    ptm->tm_mon = month;
    ptm->tm_mday = 1 + dayinyear - padays[month];

    /* Get weekday */
    ptm->tm_wday = (days + 1) % 7;

    /* Calculate hour and second in hour */
    ptm->tm_hour = secondinday / SECONDSPERHOUR;
    secondinhour = secondinday % SECONDSPERHOUR;

    /* Calculate minute and second */
    ptm->tm_min = secondinhour / 60;
    ptm->tm_sec = secondinhour % 60;

    return ptm;
}