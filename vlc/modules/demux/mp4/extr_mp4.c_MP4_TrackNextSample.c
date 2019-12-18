#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_20__ {scalar_t__ i_sample; scalar_t__ i_sample_count; size_t i_chunk; size_t i_elst; scalar_t__ i_elst_time; TYPE_5__* (* BOXDATA ) (int /*<<< orphan*/ ) ;scalar_t__ p_elst; int /*<<< orphan*/  i_track_ID; TYPE_1__* chunk; } ;
typedef  TYPE_2__ mp4_track_t ;
struct TYPE_21__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ demux_t ;
struct TYPE_22__ {int /*<<< orphan*/  i_timescale; } ;
typedef  TYPE_4__ demux_sys_t ;
struct TYPE_23__ {scalar_t__ i_entry_count; scalar_t__* i_segment_duration; } ;
struct TYPE_19__ {scalar_t__ i_sample_first; scalar_t__ i_sample_count; } ;
typedef  TYPE_5__ MP4_Box_data_elst_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP4_TrackGetDTS (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  MP4_TrackSelect (TYPE_3__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  MP4_TrackSetELST (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ MP4_rescale_qtime (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TrackGotoChunkSample (TYPE_3__*,TYPE_2__*,int,scalar_t__) ; 
 scalar_t__ UINT32_MAX ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  msg_Warn (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_elst ; 
 TYPE_5__* stub1 (int /*<<< orphan*/ ) ; 
 TYPE_5__* stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int MP4_TrackNextSample( demux_t *p_demux, mp4_track_t *p_track, uint32_t i_samples )
{
    if ( UINT32_MAX - p_track->i_sample < i_samples )
    {
        p_track->i_sample = UINT32_MAX;
        return VLC_EGENERIC;
    }

    p_track->i_sample += i_samples;

    if( p_track->i_sample >= p_track->i_sample_count )
        return VLC_EGENERIC;

    /* Have we changed chunk ? */
    if( p_track->i_sample >=
            p_track->chunk[p_track->i_chunk].i_sample_first +
            p_track->chunk[p_track->i_chunk].i_sample_count )
    {
        if( TrackGotoChunkSample( p_demux, p_track, p_track->i_chunk + 1,
                                  p_track->i_sample ) )
        {
            msg_Warn( p_demux, "track[0x%x] will be disabled "
                      "(cannot restart decoder)", p_track->i_track_ID );
            MP4_TrackSelect( p_demux, p_track, false );
            return VLC_EGENERIC;
        }
    }

    /* Have we changed elst */
    if( p_track->p_elst && p_track->BOXDATA(p_elst)->i_entry_count > 0 )
    {
        demux_sys_t *p_sys = p_demux->p_sys;
        MP4_Box_data_elst_t *elst = p_track->BOXDATA(p_elst);
        uint64_t i_mvt = MP4_rescale_qtime( MP4_TrackGetDTS( p_demux, p_track ),
                                            p_sys->i_timescale );
        if( (unsigned int)p_track->i_elst < elst->i_entry_count &&
            i_mvt >= p_track->i_elst_time +
                     elst->i_segment_duration[p_track->i_elst] )
        {
            MP4_TrackSetELST( p_demux, p_track,
                              MP4_TrackGetDTS( p_demux, p_track ) );
        }
    }

    return VLC_SUCCESS;
}