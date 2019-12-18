#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* vlc_tick_t ;
struct TYPE_8__ {scalar_t__ system; } ;
struct TYPE_7__ {scalar_t__ system; } ;
struct TYPE_6__ {int /*<<< orphan*/  system; } ;
struct TYPE_9__ {scalar_t__ pause_date; scalar_t__ offset; int /*<<< orphan*/  lock; int /*<<< orphan*/  cond; TYPE_3__ wait_sync_ref; TYPE_2__ first_pcr; TYPE_1__ last; } ;
typedef  TYPE_4__ vlc_clock_main_t ;

/* Variables and functions */
 scalar_t__ VLC_TICK_INVALID ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vlc_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void vlc_clock_main_ChangePause(vlc_clock_main_t *main_clock, vlc_tick_t now,
                                bool paused)
{
    vlc_mutex_lock(&main_clock->lock);
    assert(paused == (main_clock->pause_date == VLC_TICK_INVALID));

    if (paused)
        main_clock->pause_date = now;
    else
    {
        /**
         * Only apply a delay if the clock has a reference point to avoid
         * messing up the timings if the stream was paused then seeked
         */
        const vlc_tick_t delay = now - main_clock->pause_date;
        if (main_clock->offset != VLC_TICK_INVALID)
        {
            main_clock->last.system += delay;
            main_clock->offset += delay;
        }
        if (main_clock->first_pcr.system != VLC_TICK_INVALID)
            main_clock->first_pcr.system += delay;
        if (main_clock->wait_sync_ref.system != VLC_TICK_INVALID)
            main_clock->wait_sync_ref.system += delay;
        main_clock->pause_date = VLC_TICK_INVALID;
        vlc_cond_broadcast(&main_clock->cond);
    }
    vlc_mutex_unlock(&main_clock->lock);
}