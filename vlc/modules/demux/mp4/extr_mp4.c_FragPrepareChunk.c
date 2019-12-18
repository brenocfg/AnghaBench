#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stime_t ;
struct TYPE_9__ {TYPE_4__* p_array; scalar_t__ i_count; } ;
struct TYPE_10__ {int b_resync_time_offset; scalar_t__ i_trun_sample; int /*<<< orphan*/  i_trun_sample_pos; TYPE_1__ runs; } ;
struct TYPE_11__ {int /*<<< orphan*/  i_time; TYPE_2__ context; } ;
typedef  TYPE_3__ mp4_track_t ;
struct TYPE_12__ {int /*<<< orphan*/  i_first_dts; int /*<<< orphan*/  i_offset; } ;
typedef  TYPE_4__ mp4_run_t ;
struct TYPE_13__ {TYPE_6__* p_sys; } ;
typedef  TYPE_5__ demux_t ;
struct TYPE_14__ {unsigned int i_tracks; TYPE_3__* track; } ;
typedef  TYPE_6__ demux_sys_t ;
typedef  int /*<<< orphan*/  MP4_Box_t ;

/* Variables and functions */
 scalar_t__ FragCreateTrunIndex (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int VLC_EGENERIC ; 
 scalar_t__ VLC_SUCCESS ; 

__attribute__((used)) static int FragPrepareChunk( demux_t *p_demux, MP4_Box_t *p_moof,
                             MP4_Box_t *p_sidx, stime_t i_moof_time, bool b_discontinuity )
{
    demux_sys_t *p_sys = p_demux->p_sys;

    if( b_discontinuity )
    {
        for( unsigned i=0; i<p_sys->i_tracks; i++ )
            p_sys->track[i].context.b_resync_time_offset = true;
    }

    if( FragCreateTrunIndex( p_demux, p_moof, p_sidx, i_moof_time ) == VLC_SUCCESS )
    {
        for( unsigned i=0; i<p_sys->i_tracks; i++ )
        {
            mp4_track_t *p_track = &p_sys->track[i];
            if( p_track->context.runs.i_count )
            {
                const mp4_run_t *p_run = &p_track->context.runs.p_array[0];
                p_track->context.i_trun_sample_pos = p_run->i_offset;
                p_track->context.i_trun_sample = 0;
                p_track->i_time = p_run->i_first_dts;
            }
        }
        return VLC_SUCCESS;
    }

    return VLC_EGENERIC;
}