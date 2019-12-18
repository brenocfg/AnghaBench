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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  stime_t ;
struct TYPE_3__ {size_t i_entries; scalar_t__* pi_pos; size_t i_tracks; int /*<<< orphan*/ * p_times; } ;
typedef  TYPE_1__ mp4_fragments_index_t ;

/* Variables and functions */

stime_t MP4_Fragment_Index_GetTrackStartTime( mp4_fragments_index_t *p_index,
                                              unsigned i_track_index, uint64_t i_moof_pos )
{
    for( size_t i=0; i<p_index->i_entries; i++ )
    {
        if( p_index->pi_pos[i] >= i_moof_pos )
            return p_index->p_times[i * p_index->i_tracks + i_track_index];
    }
    return 0;
}