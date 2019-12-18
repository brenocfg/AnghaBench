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
typedef  TYPE_1__* vlc_timer_t ;
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  reschedule; scalar_t__ interval; scalar_t__ value; } ;

/* Variables and functions */
 scalar_t__ VLC_TIMER_DISARM ; 
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_tick_now () ; 

void vlc_timer_schedule (vlc_timer_t timer, bool absolute,
                         vlc_tick_t value, vlc_tick_t interval)
{
    if (value == VLC_TIMER_DISARM)
        interval = 0;
    else
    if (!absolute)
        value += vlc_tick_now();

    vlc_mutex_lock (&timer->lock);
    timer->value = value;
    timer->interval = interval;
    vlc_cond_signal (&timer->reschedule);
    vlc_mutex_unlock (&timer->lock);
}