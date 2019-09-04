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
typedef  int /*<<< orphan*/  LARGE_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER_FUNC () ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 

void InitPiceRunningTimer(void)
{
	LARGE_INTEGER   Interval;

	ENTER_FUNC();
#if 0  //won't work. we have to intercept timer interrupt so dpc will never fire while we are in pice
	KeInitializeTimer( &PiceTimer );
	KeInitializeDpc( &PiceTimerDPC, PiceRunningTimer, NULL );

	Interval.QuadPart=-1000000L;  // 100 millisec. (unit is 100 nanosec.)

    KeSetTimerEx(&PiceTimer,
                        Interval, 1000000L,
                        &PiceTimerDpc);
#endif
    LEAVE_FUNC();
}