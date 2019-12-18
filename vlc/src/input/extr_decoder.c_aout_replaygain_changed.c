#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__* pb_gain; scalar_t__* pb_peak; } ;
typedef  TYPE_1__ audio_replay_gain_t ;

/* Variables and functions */
 size_t AUDIO_REPLAY_GAIN_MAX ; 

__attribute__((used)) static bool aout_replaygain_changed( const audio_replay_gain_t *a,
                                     const audio_replay_gain_t *b )
{
    for( size_t i=0; i<AUDIO_REPLAY_GAIN_MAX; i++ )
    {
        if( a->pb_gain[i] != b->pb_gain[i] ||
            a->pb_peak[i] != b->pb_peak[i] ||
            a->pb_gain[i] != b->pb_gain[i] ||
            a->pb_peak[i] != b->pb_peak[i] )
            return true;
    }
    return false;
}