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
typedef  int /*<<< orphan*/  time_t ;
struct tm {scalar_t__ tm_year; scalar_t__ tm_mon; int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_sec; } ;
struct TYPE_3__ {scalar_t__ year; scalar_t__ month; int /*<<< orphan*/  day; int /*<<< orphan*/  hour; int /*<<< orphan*/  minute; int /*<<< orphan*/  second; } ;
typedef  TYPE_1__* PDATE_AND_TIME ;

/* Variables and functions */
 struct tm* gmtime (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void convert_date_and_time(PDATE_AND_TIME dt, time_t *time)
{
    struct tm *timedef;
    timedef = gmtime(time);

    dt->second = timedef->tm_sec;
    dt->minute = timedef->tm_min;
    dt->hour = timedef->tm_hour;
    dt->day = timedef->tm_mday;
    dt->month = timedef->tm_mon + 1;
    dt->year = timedef->tm_year + 1900;
}