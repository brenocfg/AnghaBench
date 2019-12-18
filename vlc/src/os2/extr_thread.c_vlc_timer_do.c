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
struct vlc_timer {int /*<<< orphan*/  htimer; scalar_t__ hev; scalar_t__ interval; int /*<<< orphan*/  data; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ) ;scalar_t__ quit; } ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  HSEM ;

/* Variables and functions */
 int /*<<< orphan*/  DosAsyncTimer (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DosResetEventSem (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DosWaitEventSem (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEM_INDEFINITE_WAIT ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vlc_timer_do (void *arg)
{
    struct vlc_timer *timer = arg;

    while (1)
    {
        ULONG count;

        DosWaitEventSem (timer->hev, SEM_INDEFINITE_WAIT);
        DosResetEventSem (timer->hev, &count);

        if (timer->quit)
            break;

        timer->func (timer->data);

        if (timer->interval)
            DosAsyncTimer (timer->interval, (HSEM)timer->hev, &timer->htimer);
    }
}