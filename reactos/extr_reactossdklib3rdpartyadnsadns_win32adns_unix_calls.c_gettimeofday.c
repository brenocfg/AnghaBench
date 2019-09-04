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
struct timezone {int dummy; } ;
struct timeval {long tv_sec; long tv_usec; } ;
typedef  int __int64 ;
struct TYPE_3__ {int member_0; int member_1; int member_3; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_2; } ;
typedef  TYPE_1__ SYSTEMTIME ;
typedef  int /*<<< orphan*/  LPFILETIME ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  GetSystemTimeAsFileTime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SystemTimeToFileTime (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 

int gettimeofday(struct timeval *tv, struct timezone *tz)
{
    static __int64 Adjustment;
	__int64 now = 0;

    if (!Adjustment)
    {
		SYSTEMTIME st = {1970,1,0,1,0,0,0};
		SystemTimeToFileTime(&st, (LPFILETIME)&Adjustment);
    }

    if (tz)
    {
		errno = EINVAL;
	return -1;
    }

	GetSystemTimeAsFileTime((LPFILETIME)&now);
	now -= Adjustment;

	tv->tv_sec = (long)(now / 10000000);
	tv->tv_usec = (long)((now % 10000000) / 10); 

    return 0;
}