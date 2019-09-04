#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct tm {int tm_sec; int /*<<< orphan*/  tm_year; int /*<<< orphan*/  tm_mon; int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_min; } ;
struct FatTime {int whole; } ;
struct TYPE_2__ {int member_0; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
typedef  int DWORD ;

/* Variables and functions */
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

DWORD get_fattime(void)
{
    /* 31-25: Year(0-127 org.1980), 24-21: Month(1-12), 20-16: Day(1-31) */
    /* 15-11: Hour(0-23), 10-5: Minute(0-59), 4-0: Second(0-29 *2) */

    time_t rawtime;
    struct tm * timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    {
    union FatTime {
        struct {
            DWORD Second : 5; // div 2
            DWORD Minute : 6;
            DWORD Hour   : 5;
            DWORD Day    : 5;
            DWORD Month  : 4;
            DWORD Year   : 7; // year-1980
        };
        DWORD whole;
    } myTime = {
        {
            timeinfo->tm_sec / 2,
            timeinfo->tm_min,
            timeinfo->tm_hour,
            timeinfo->tm_mday,
            timeinfo->tm_mon  +  1,
            timeinfo->tm_year - 80,
        }
    };

    return myTime.whole;
    }
}