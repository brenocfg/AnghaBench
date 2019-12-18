#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
typedef  scalar_t__ stime_t ;
struct TYPE_12__ {int /*<<< orphan*/  i_timescale; } ;
typedef  TYPE_1__ mp4_track_t ;
struct TYPE_13__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_14__ {int /*<<< orphan*/  p_root; } ;
typedef  TYPE_3__ demux_sys_t ;
struct TYPE_16__ {unsigned int i_track_ID; int i_number_of_entries; int i_version; scalar_t__* p_time; scalar_t__* p_moof_offset; } ;
struct TYPE_15__ {scalar_t__ i_type; struct TYPE_15__* p_next; } ;
typedef  TYPE_4__ MP4_Box_t ;
typedef  TYPE_5__ MP4_Box_data_tfra_t ;

/* Variables and functions */
 scalar_t__ ATOM_tfra ; 
 TYPE_5__* BOXDATA (TYPE_4__*) ; 
 TYPE_4__* MP4_BoxGet (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* MP4_GetTrackByTrackID (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  MP4_rescale_mtime (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ MP4_rescale_qtime (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 

__attribute__((used)) static int FragGetMoofByTfraIndex( demux_t *p_demux, const vlc_tick_t i_target_time, unsigned i_track_ID,
                                   uint64_t *pi_moof_pos, vlc_tick_t *pi_sampletime )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    MP4_Box_t *p_tfra = MP4_BoxGet( p_sys->p_root, "mfra/tfra" );
    for( ; p_tfra; p_tfra = p_tfra->p_next )
    {
        if ( p_tfra->i_type == ATOM_tfra )
        {
            const MP4_Box_data_tfra_t *p_data = BOXDATA(p_tfra);
            if( !p_data || p_data->i_track_ID != i_track_ID )
                continue;

            uint64_t i_pos = 0;
            mp4_track_t *p_track = MP4_GetTrackByTrackID( p_demux, p_data->i_track_ID );
            if ( p_track )
            {
                stime_t i_track_target_time = MP4_rescale_qtime( i_target_time, p_track->i_timescale );
                for ( uint32_t i = 0; i<p_data->i_number_of_entries; i += ( p_data->i_version == 1 ) ? 2 : 1 )
                {
                    stime_t i_time;
                    uint64_t i_offset;
                    if ( p_data->i_version == 1 )
                    {
                        i_time = *((uint64_t *)(p_data->p_time + i));
                        i_offset = *((uint64_t *)(p_data->p_moof_offset + i));
                    }
                    else
                    {
                        i_time = p_data->p_time[i];
                        i_offset = p_data->p_moof_offset[i];
                    }

                    if ( i_time >= i_track_target_time )
                    {
                        if ( i_pos == 0 ) /* Not in this traf */
                            break;

                        *pi_moof_pos = i_pos;
                        *pi_sampletime = MP4_rescale_mtime( i_time, p_track->i_timescale );
                        return VLC_SUCCESS;
                    }
                    else
                        i_pos = i_offset;
                }
            }
        }
    }
    return VLC_EGENERIC;
}