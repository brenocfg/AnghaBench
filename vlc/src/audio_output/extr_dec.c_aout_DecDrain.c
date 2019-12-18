#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  block_t ;
struct TYPE_12__ {int /*<<< orphan*/  (* play ) (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ audio_output_t ;
struct TYPE_11__ {int discontinuity; int /*<<< orphan*/  clock; } ;
struct TYPE_10__ {int /*<<< orphan*/  i_format; } ;
struct TYPE_13__ {int /*<<< orphan*/  original_pts; TYPE_2__ sync; int /*<<< orphan*/  filters; TYPE_1__ mixer_format; } ;
typedef  TYPE_4__ aout_owner_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  aout_Drain (TYPE_3__*) ; 
 int /*<<< orphan*/ * aout_FiltersDrain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aout_FiltersResetClock (int /*<<< orphan*/ ) ; 
 TYPE_4__* aout_owner (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_clock_Reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_tick_now () ; 

void aout_DecDrain(audio_output_t *aout)
{
    aout_owner_t *owner = aout_owner (aout);

    if (!owner->mixer_format.i_format)
        return;

    block_t *block = aout_FiltersDrain (owner->filters);
    if (block)
        aout->play(aout, block, vlc_tick_now());

    aout_Drain(aout);

    vlc_clock_Reset(owner->sync.clock);
    aout_FiltersResetClock(owner->filters);

    owner->sync.discontinuity = true;
    owner->original_pts = VLC_TICK_INVALID;
}