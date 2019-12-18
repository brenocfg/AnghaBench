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
struct TYPE_4__ {scalar_t__ hev; int /*<<< orphan*/  hevAck; int /*<<< orphan*/  signaled; int /*<<< orphan*/  waiters; } ;
typedef  TYPE_1__ vlc_cond_t ;
typedef  int /*<<< orphan*/  ULONG ;

/* Variables and functions */
 int /*<<< orphan*/  DosPostEventSem (scalar_t__) ; 
 int /*<<< orphan*/  DosResetEventSem (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DosWaitEventSem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NULLHANDLE ; 
 int /*<<< orphan*/  SEM_INDEFINITE_WAIT ; 
 int /*<<< orphan*/  __atomic_cmpxchg32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __atomic_xchg (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_static_cond_init (TYPE_1__*) ; 

void vlc_cond_signal (vlc_cond_t *p_condvar)
{
    if (p_condvar->hev == NULLHANDLE)
        vlc_static_cond_init (p_condvar);

    if (!__atomic_cmpxchg32 (&p_condvar->waiters, 0, 0))
    {
        ULONG ulPost;

        __atomic_xchg (&p_condvar->signaled, 1);
        DosPostEventSem (p_condvar->hev);

        DosWaitEventSem (p_condvar->hevAck, SEM_INDEFINITE_WAIT);
        DosResetEventSem (p_condvar->hevAck, &ulPost);
    }
}