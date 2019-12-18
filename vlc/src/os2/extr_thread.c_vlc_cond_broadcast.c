#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ hev; int /*<<< orphan*/  waiters; } ;
typedef  TYPE_1__ vlc_cond_t ;

/* Variables and functions */
 scalar_t__ NULLHANDLE ; 
 int /*<<< orphan*/  __atomic_cmpxchg32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_cond_signal (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_static_cond_init (TYPE_1__*) ; 

void vlc_cond_broadcast (vlc_cond_t *p_condvar)
{
    if (p_condvar->hev == NULLHANDLE)
        vlc_static_cond_init (p_condvar);

    while (!__atomic_cmpxchg32 (&p_condvar->waiters, 0, 0))
        vlc_cond_signal (p_condvar);
}