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
typedef  int /*<<< orphan*/  vlc_tick_t ;
struct aout_sys {scalar_t__ first_play_date; int /*<<< orphan*/  length; } ;
struct TYPE_6__ {scalar_t__ i_length; } ;
typedef  TYPE_1__ block_t ;
struct TYPE_7__ {struct aout_sys* sys; } ;
typedef  TYPE_2__ audio_output_t ;

/* Variables and functions */
 scalar_t__ VLC_TICK_INVALID ; 
 int /*<<< orphan*/  block_Release (TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ vlc_tick_now () ; 

__attribute__((used)) static void Play(audio_output_t *aout, block_t *block, vlc_tick_t date)
{
    struct aout_sys *sys = aout->sys;

    if (unlikely(sys->first_play_date == VLC_TICK_INVALID))
        sys->first_play_date = vlc_tick_now();
    sys->length += block->i_length;

    block_Release( block );
    (void) date;
}