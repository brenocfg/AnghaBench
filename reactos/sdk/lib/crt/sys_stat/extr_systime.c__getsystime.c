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
struct tm {int tm_year; int tm_mon; int tm_isdst; int tm_yday; int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_wday; } ;
struct TYPE_3__ {int wYear; int wMonth; unsigned int wMilliseconds; int /*<<< orphan*/  wSecond; int /*<<< orphan*/  wMinute; int /*<<< orphan*/  wHour; int /*<<< orphan*/  wDay; int /*<<< orphan*/  wDayOfWeek; } ;
typedef  int /*<<< orphan*/  TIME_ZONE_INFORMATION ;
typedef  TYPE_1__ SYSTEMTIME ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetLocalTime (TYPE_1__*) ; 
 scalar_t__ GetTimeZoneInformation (int /*<<< orphan*/ *) ; 
 scalar_t__ TIME_ZONE_ID_DAYLIGHT ; 
 scalar_t__* month ; 

unsigned int _getsystime(struct tm* tp)
{
    SYSTEMTIME Time;
    int i;
    DWORD TimeZoneId;
    TIME_ZONE_INFORMATION TimeZoneInformation;

    GetLocalTime(&Time);

    tp->tm_year = Time.wYear - 1900;
    tp->tm_mon = Time.wMonth - 1;
    tp->tm_wday = Time.wDayOfWeek;
    tp->tm_mday = Time.wDay;
    tp->tm_hour = Time.wHour;
    tp->tm_min = Time.wMinute;
    tp->tm_sec = Time.wSecond;

    tp->tm_isdst = -1;

    TimeZoneId =  GetTimeZoneInformation(&TimeZoneInformation);
    if (TimeZoneId == TIME_ZONE_ID_DAYLIGHT){
      tp->tm_isdst = 1;
    }
    else
      tp->tm_isdst = 0;

    if (tp->tm_year % 4 == 0) {
        if (tp->tm_year % 100 != 0)
            tp->tm_yday = 1;
        else if ((tp->tm_year-100) % 1000 == 0)
            tp->tm_yday = 1;
    }

    for (i = 0; i <= tp->tm_mon; i++)
        tp->tm_yday += month[i];

    return Time.wMilliseconds;
}