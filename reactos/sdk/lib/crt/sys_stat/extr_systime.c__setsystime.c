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
struct tm {int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_wday; scalar_t__ tm_mon; scalar_t__ tm_year; } ;
struct TYPE_3__ {unsigned int wMilliseconds; int /*<<< orphan*/  wSecond; int /*<<< orphan*/  wMinute; int /*<<< orphan*/  wHour; int /*<<< orphan*/  wDay; int /*<<< orphan*/  wDayOfWeek; scalar_t__ wMonth; scalar_t__ wYear; } ;
typedef  TYPE_1__ SYSTEMTIME ;

/* Variables and functions */
 int /*<<< orphan*/  SetLocalTime (TYPE_1__*) ; 

unsigned int _setsystime(struct tm* tp, unsigned int ms)
{
    SYSTEMTIME Time;

    Time.wYear = tp->tm_year + 1900;
    Time.wMonth = tp->tm_mon + 1;
    Time.wDayOfWeek = tp->tm_wday;
    Time.wDay = tp->tm_mday;
    Time.wHour = tp->tm_hour;
    Time.wMinute = tp->tm_min;
    Time.wSecond = tp->tm_sec;
    Time.wMilliseconds = ms;

    if (!SetLocalTime(&Time))
        return -1;

    return 0;
}