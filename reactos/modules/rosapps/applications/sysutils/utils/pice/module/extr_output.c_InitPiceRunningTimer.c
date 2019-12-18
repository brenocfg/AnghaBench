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
struct TYPE_3__ {long QuadPart; } ;
typedef  TYPE_1__ LARGE_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER_FUNC () ; 
 int /*<<< orphan*/  KeInitializeDpc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeInitializeTimer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeSetTimerEx (int /*<<< orphan*/ *,TYPE_1__,long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 int /*<<< orphan*/  PiceRunningTimer ; 
 int /*<<< orphan*/  PiceTimer ; 
 int /*<<< orphan*/  PiceTimerDPC ; 
 int /*<<< orphan*/  PiceTimerDpc ; 

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