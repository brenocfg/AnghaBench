#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vlc_timer_t ;
struct TYPE_4__ {scalar_t__ htimer; int quit; int /*<<< orphan*/  hev; int /*<<< orphan*/  tid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCWW_WAIT ; 
 int /*<<< orphan*/  DosCloseEventSem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DosPostEventSem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DosStopTimer (scalar_t__) ; 
 int /*<<< orphan*/  DosWaitThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ NULLHANDLE ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void vlc_timer_destroy (vlc_timer_t timer)
{
    if (timer->htimer != NULLHANDLE)
        DosStopTimer (timer->htimer);

    timer->quit = true;
    DosPostEventSem (timer->hev);
    DosWaitThread (&timer->tid, DCWW_WAIT);
    DosCloseEventSem (timer->hev);

    free (timer);
}