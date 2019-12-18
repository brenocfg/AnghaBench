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
typedef  int vlc_tick_t ;
typedef  int /*<<< orphan*/  vlc_mutex_t ;
typedef  int /*<<< orphan*/  vlc_cond_t ;
typedef  int time_t ;
struct timeval {int dummy; } ;
typedef  int ULONG ;

/* Variables and functions */
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int vlc_cond_wait_common (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int vlc_tick_from_timeval (struct timeval*) ; 

int vlc_cond_timedwait_daytime (vlc_cond_t *p_condvar, vlc_mutex_t *p_mutex,
                                time_t deadline)
{
    ULONG ulTimeout;
    vlc_tick_t total;
    struct timeval tv;

    gettimeofday (&tv, NULL);

    total = vlc_tick_from_timeval( &tv );
    total = (deadline - total) / 1000;
    if( total < 0 )
        total = 0;

    ulTimeout = ( total > 0x7fffffff ) ? 0x7fffffff : total;

    return vlc_cond_wait_common (p_condvar, p_mutex, ulTimeout);
}