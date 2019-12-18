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
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  int /*<<< orphan*/  vlc_mutex_t ;
typedef  int /*<<< orphan*/  vlc_cond_t ;
struct timespec {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  VLC_THREAD_ASSERT (char*) ; 
 int pthread_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec*) ; 
 struct timespec timespec_from_vlc_tick (int /*<<< orphan*/ ) ; 

int vlc_cond_timedwait (vlc_cond_t *p_condvar, vlc_mutex_t *p_mutex,
                        vlc_tick_t deadline)
{
    struct timespec ts = timespec_from_vlc_tick (deadline);
    int val = pthread_cond_timedwait (p_condvar, p_mutex, &ts);
    if (val != ETIMEDOUT)
        VLC_THREAD_ASSERT ("timed-waiting on condition");
    return val;
}