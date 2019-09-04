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
struct TYPE_3__ {scalar_t__ timeSpent_ns; scalar_t__ timeBudget_ns; } ;
typedef  TYPE_1__ BMK_timedFnState_t ;

/* Variables and functions */

int BMK_isCompleted_TimedFn(const BMK_timedFnState_t* timedFnState)
{
    return (timedFnState->timeSpent_ns >= timedFnState->timeBudget_ns);
}