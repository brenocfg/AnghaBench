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
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  FILETIME ;

/* Variables and functions */
 scalar_t__ FileTimeToUnixTime (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetSystemTimeAsFileTime (int /*<<< orphan*/ *) ; 

time_t _time(time_t* ptime)
{
    FILETIME SystemTime;
    time_t time = 0;

    GetSystemTimeAsFileTime(&SystemTime);
    time = (time_t)FileTimeToUnixTime(&SystemTime, NULL);

    if (ptime)
    {
        *ptime = time;
    }
    return time;
}