#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_6__ {scalar_t__ delay; TYPE_2__* owner; } ;
typedef  TYPE_1__ vlc_clock_t ;
struct TYPE_7__ {scalar_t__ delay; int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ vlc_clock_main_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vlc_clock_main_reset (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_clock_on_update (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vlc_clock_master_reset(vlc_clock_t *clock)
{
    vlc_clock_main_t *main_clock = clock->owner;

    vlc_mutex_lock(&main_clock->lock);
    vlc_clock_main_reset(main_clock);

    assert(main_clock->delay <= 0);
    assert(clock->delay >= 0);
    /* Move the delay from the slaves to the master */
    if (clock->delay != 0 && main_clock->delay != 0)
    {
        vlc_tick_t delta = clock->delay + main_clock->delay;
        if (delta > 0)
        {
            clock->delay = delta;
            main_clock->delay = 0;
        }
        else
        {
            clock->delay = 0;
            main_clock->delay = delta;
        }
    }

    vlc_mutex_unlock(&main_clock->lock);

    vlc_clock_on_update(clock, VLC_TICK_INVALID, VLC_TICK_INVALID, 1.f, 0, 0);
}