#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_10__ {size_t i_chunk; unsigned int i_sample; size_t i_elst; unsigned int i_elst_time; int /*<<< orphan*/  i_timescale; TYPE_5__* (* BOXDATA ) (int /*<<< orphan*/ ) ;scalar_t__ p_elst; TYPE_2__* chunk; } ;
typedef  TYPE_1__ mp4_track_t ;
struct TYPE_11__ {unsigned int i_sample_first; unsigned int i_first_dts; unsigned int i_entries_dts; unsigned int* p_sample_count_dts; unsigned int* p_sample_delta_dts; } ;
typedef  TYPE_2__ mp4_chunk_t ;
typedef  unsigned int int64_t ;
struct TYPE_12__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ demux_t ;
struct TYPE_13__ {int /*<<< orphan*/  i_timescale; } ;
typedef  TYPE_4__ demux_sys_t ;
struct TYPE_14__ {scalar_t__* i_media_rate_integer; scalar_t__* i_media_rate_fraction; scalar_t__* i_media_time; scalar_t__ i_entry_count; } ;
typedef  TYPE_5__ MP4_Box_data_elst_t ;

/* Variables and functions */
 scalar_t__ MP4_rescale_mtime (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_elst ; 
 TYPE_5__* stub1 (int /*<<< orphan*/ ) ; 
 TYPE_5__* stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline vlc_tick_t MP4_TrackGetDTS( demux_t *p_demux, mp4_track_t *p_track )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    const mp4_chunk_t *p_chunk = &p_track->chunk[p_track->i_chunk];

    unsigned int i_index = 0;
    unsigned int i_sample = p_track->i_sample - p_chunk->i_sample_first;
    int64_t sdts = p_chunk->i_first_dts;

    while( i_sample > 0 && i_index < p_chunk->i_entries_dts )
    {
        if( i_sample > p_chunk->p_sample_count_dts[i_index] )
        {
            sdts += p_chunk->p_sample_count_dts[i_index] *
                p_chunk->p_sample_delta_dts[i_index];
            i_sample -= p_chunk->p_sample_count_dts[i_index];
            i_index++;
        }
        else
        {
            sdts += i_sample * p_chunk->p_sample_delta_dts[i_index];
            break;
        }
    }

    vlc_tick_t i_dts = MP4_rescale_mtime( sdts, p_track->i_timescale );

    /* now handle elst */
    if( p_track->p_elst && p_track->BOXDATA(p_elst)->i_entry_count )
    {
        MP4_Box_data_elst_t *elst = p_track->BOXDATA(p_elst);

        /* convert to offset */
        if( ( elst->i_media_rate_integer[p_track->i_elst] > 0 ||
              elst->i_media_rate_fraction[p_track->i_elst] > 0 ) &&
            elst->i_media_time[p_track->i_elst] > 0 )
        {
            i_dts -= MP4_rescale_mtime( elst->i_media_time[p_track->i_elst], p_track->i_timescale );
        }

        /* add i_elst_time */
        i_dts += MP4_rescale_mtime( p_track->i_elst_time, p_sys->i_timescale );

        if( i_dts < 0 ) i_dts = 0;
    }

    return i_dts;
}