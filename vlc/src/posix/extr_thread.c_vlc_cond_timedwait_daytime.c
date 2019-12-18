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
typedef  int /*<<< orphan*/  vlc_mutex_t ;
typedef  int /*<<< orphan*/  vlc_cond_t ;
typedef  int /*<<< orphan*/  time_t ;
struct timespec {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  VLC_THREAD_ASSERT (char*) ; 
 int pthread_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec*) ; 

int vlc_cond_timedwait_daytime (vlc_cond_t *p_condvar, vlc_mutex_t *p_mutex,
                                time_t deadline)
{
    struct timespec ts = { deadline, 0 };
    int val = pthread_cond_timedwait (p_condvar, p_mutex, &ts);
    if (val != ETIMEDOUT)
        VLC_THREAD_ASSERT ("timed-waiting on condition");
    return val;
}