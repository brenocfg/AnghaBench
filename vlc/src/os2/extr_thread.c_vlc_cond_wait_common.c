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
typedef  int /*<<< orphan*/  vlc_mutex_t ;
struct TYPE_3__ {scalar_t__ hev; int /*<<< orphan*/  hevAck; int /*<<< orphan*/  waiters; int /*<<< orphan*/  signaled; } ;
typedef  TYPE_1__ vlc_cond_t ;
typedef  scalar_t__ ULONG ;

/* Variables and functions */
 int /*<<< orphan*/  DosPostEventSem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DosResetEventSem (scalar_t__,scalar_t__*) ; 
 scalar_t__ ERROR_INTERRUPT ; 
 int ETIMEDOUT ; 
 scalar_t__ NO_ERROR ; 
 scalar_t__ NULLHANDLE ; 
 scalar_t__ __atomic_cmpxchg32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __atomic_decrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __atomic_increment (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ vlc_WaitForSingleObject (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_testcancel () ; 

__attribute__((used)) static int vlc_cond_wait_common (vlc_cond_t *p_condvar, vlc_mutex_t *p_mutex,
                                 ULONG ulTimeout)
{
    ULONG ulPost;
    ULONG rc;

    assert(p_condvar->hev != NULLHANDLE);

    do
    {
        vlc_testcancel();

        __atomic_increment (&p_condvar->waiters);

        vlc_mutex_unlock (p_mutex);

        do
        {
            rc = vlc_WaitForSingleObject( p_condvar->hev, ulTimeout );
            if (rc == NO_ERROR)
                DosResetEventSem (p_condvar->hev, &ulPost);
        } while (rc == NO_ERROR &&
                 __atomic_cmpxchg32 (&p_condvar->signaled, 0, 1) == 0);

        __atomic_decrement (&p_condvar->waiters);

        DosPostEventSem (p_condvar->hevAck);

        vlc_mutex_lock (p_mutex);
    } while( rc == ERROR_INTERRUPT );

    return rc ? ETIMEDOUT : 0;
}