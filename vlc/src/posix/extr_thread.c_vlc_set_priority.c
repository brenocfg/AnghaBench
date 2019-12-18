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
struct TYPE_3__ {int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ vlc_thread_t ;
struct sched_param {scalar_t__ sched_priority; } ;

/* Variables and functions */
 int SCHED_OTHER ; 
 int SCHED_RR ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 scalar_t__ pthread_setschedparam (int /*<<< orphan*/ ,int,struct sched_param*) ; 
 int /*<<< orphan*/  rt_offset ; 
 scalar_t__ rt_priorities ; 
 scalar_t__ sched_get_priority_max (int) ; 
 scalar_t__ sched_get_priority_min (int) ; 

int vlc_set_priority (vlc_thread_t th, int priority)
{
#if defined (_POSIX_PRIORITY_SCHEDULING) && (_POSIX_PRIORITY_SCHEDULING >= 0) \
 && defined (_POSIX_THREAD_PRIORITY_SCHEDULING) \
 && (_POSIX_THREAD_PRIORITY_SCHEDULING >= 0)
    if (rt_priorities)
    {
        struct sched_param sp = { .sched_priority = priority + rt_offset, };
        int policy;

        if (sp.sched_priority <= 0)
            sp.sched_priority += sched_get_priority_max (policy = SCHED_OTHER);
        else
            sp.sched_priority += sched_get_priority_min (policy = SCHED_RR);

        if (pthread_setschedparam(th.handle, policy, &sp))
            return VLC_EGENERIC;
    }
#else
    (void) th; (void) priority;
#endif
    return VLC_SUCCESS;
}