#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ aout_stream_t ;
struct TYPE_5__ {int /*<<< orphan*/ * hTimer; } ;
typedef  TYPE_2__ aout_stream_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteTimerQueueTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INVALID_HANDLE_VALUE ; 

__attribute__((used)) static void ResetTimer(aout_stream_t *s)
{
    aout_stream_sys_t *sys = s->sys;
    if (sys->hTimer != NULL)
    {
        DeleteTimerQueueTimer(NULL, sys->hTimer, INVALID_HANDLE_VALUE);
        sys->hTimer = NULL;
    }
}