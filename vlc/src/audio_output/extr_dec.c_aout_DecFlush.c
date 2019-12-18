#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  (* flush ) (TYPE_3__*) ;} ;
typedef  TYPE_3__ audio_output_t ;
struct TYPE_10__ {scalar_t__ delay; scalar_t__ request_delay; int discontinuity; int /*<<< orphan*/  clock; } ;
struct TYPE_9__ {scalar_t__ i_format; } ;
struct TYPE_12__ {int /*<<< orphan*/  original_pts; TYPE_2__ sync; int /*<<< orphan*/  filters; TYPE_1__ mixer_format; } ;
typedef  TYPE_4__ aout_owner_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  aout_FiltersFlush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aout_FiltersResetClock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aout_FiltersSetClockDelay (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* aout_owner (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  vlc_clock_Reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_clock_SetDelay (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void aout_DecFlush(audio_output_t *aout)
{
    aout_owner_t *owner = aout_owner (aout);

    if (owner->mixer_format.i_format)
    {
        aout_FiltersFlush (owner->filters);

        aout->flush(aout);
        vlc_clock_Reset(owner->sync.clock);
        aout_FiltersResetClock(owner->filters);

        if (owner->sync.delay > 0)
        {
            /* Also reset the delay in case of a positive delay. This will
             * trigger a silence playback before the next play. Consequently,
             * the first play date won't be (delay + dejitter) but only
             * dejitter. This will allow the aout to update the master clock
             * sooner.
             */
            vlc_clock_SetDelay(owner->sync.clock, 0);
            aout_FiltersSetClockDelay(owner->filters, 0);
            owner->sync.request_delay = owner->sync.delay;
            owner->sync.delay = 0;
        }
    }
    owner->sync.discontinuity = true;
    owner->original_pts = VLC_TICK_INVALID;
}