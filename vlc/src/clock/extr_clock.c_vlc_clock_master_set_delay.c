#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_4__ {scalar_t__ delay; TYPE_2__* owner; } ;
typedef  TYPE_1__ vlc_clock_t ;
struct TYPE_5__ {scalar_t__ delay; int /*<<< orphan*/  lock; int /*<<< orphan*/  cond; } ;
typedef  TYPE_2__ vlc_clock_main_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vlc_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static vlc_tick_t vlc_clock_master_set_delay(vlc_clock_t *clock, vlc_tick_t delay)
{
    vlc_clock_main_t *main_clock = clock->owner;
    vlc_mutex_lock(&main_clock->lock);

    vlc_tick_t delta = delay - clock->delay;

    if (delta > 0)
    {
        /* The master clock is delayed */
        main_clock->delay = 0;
        clock->delay = delay;
    }
    else
    {
        /* Delay all slaves clock instead of advancing the master one */
        main_clock->delay = delta;
    }

    assert(main_clock->delay <= 0);
    assert(clock->delay >= 0);

    vlc_cond_broadcast(&main_clock->cond);
    vlc_mutex_unlock(&main_clock->lock);
    return delta;
}