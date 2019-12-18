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
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  unsigned int stime_t ;
struct TYPE_4__ {size_t i_chunk; unsigned int i_sample; int /*<<< orphan*/  i_timescale; TYPE_2__* chunk; } ;
typedef  TYPE_1__ mp4_track_t ;
struct TYPE_5__ {unsigned int i_sample_first; unsigned int i_entries_dts; unsigned int* p_sample_count_dts; unsigned int* p_sample_delta_dts; } ;
typedef  TYPE_2__ mp4_chunk_t ;
typedef  unsigned int int64_t ;
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP4_rescale_mtime (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline vlc_tick_t MP4_GetSamplesDuration( demux_t *p_demux, mp4_track_t *p_track,
                                              unsigned i_nb_samples )
{
    VLC_UNUSED( p_demux );

    const mp4_chunk_t *p_chunk = &p_track->chunk[p_track->i_chunk];
    stime_t i_duration = 0;

    /* Forward to right index, and set remaining count in that index */
    unsigned i_index = 0;
    unsigned i_remain = 0;
    for( unsigned i = p_chunk->i_sample_first;
         i<p_track->i_sample && i_index < p_chunk->i_entries_dts; )
    {
        if( p_track->i_sample - i >= p_chunk->p_sample_count_dts[i_index] )
        {
            i += p_chunk->p_sample_count_dts[i_index];
            i_index++;
        }
        else
        {
            i_remain = p_track->i_sample - i;
            break;
        }
    }

    /* Compute total duration from all samples from index */
    while( i_nb_samples > 0 && i_index < p_chunk->i_entries_dts )
    {
        if( i_nb_samples >= p_chunk->p_sample_count_dts[i_index] - i_remain )
        {
            i_duration += (p_chunk->p_sample_count_dts[i_index] - i_remain) *
                          (int64_t) p_chunk->p_sample_delta_dts[i_index];
            i_nb_samples -= (p_chunk->p_sample_count_dts[i_index] - i_remain);
            i_index++;
            i_remain = 0;
        }
        else
        {
            i_duration += i_nb_samples * p_chunk->p_sample_delta_dts[i_index];
            break;
        }
    }

    return MP4_rescale_mtime( i_duration, p_track->i_timescale );
}