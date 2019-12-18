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
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  scalar_t__ uint64_t ;
typedef  size_t uint16_t ;
typedef  scalar_t__ stime_t ;
struct TYPE_11__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_12__ {int /*<<< orphan*/  p_root; } ;
typedef  TYPE_3__ demux_sys_t ;
struct TYPE_14__ {size_t i_reference_count; TYPE_1__* p_items; int /*<<< orphan*/  i_timescale; scalar_t__ i_first_offset; } ;
struct TYPE_13__ {scalar_t__ i_type; scalar_t__ i_size; scalar_t__ i_pos; struct TYPE_13__* p_next; } ;
struct TYPE_10__ {scalar_t__ b_reference_type; scalar_t__ i_subsegment_duration; scalar_t__ i_referenced_size; } ;
typedef  TYPE_4__ MP4_Box_t ;
typedef  TYPE_5__ MP4_Box_data_sidx_t ;

/* Variables and functions */
 scalar_t__ ATOM_sidx ; 
 TYPE_5__* BOXDATA (TYPE_4__ const*) ; 
 TYPE_4__* MP4_BoxGet (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MP4_rescale_mtime (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ MP4_rescale_qtime (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 

__attribute__((used)) static int FragGetMoofBySidxIndex( demux_t *p_demux, vlc_tick_t target_time,
                                   uint64_t *pi_moof_pos, vlc_tick_t *pi_sampletime )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    const MP4_Box_t *p_sidx = MP4_BoxGet( p_sys->p_root, "sidx" );
    for( ; p_sidx ; p_sidx = p_sidx->p_next )
    {
        if( p_sidx->i_type != ATOM_sidx )
            continue;

        const MP4_Box_data_sidx_t *p_data = BOXDATA(p_sidx);
        if( !p_data || !p_data->i_timescale )
            break;

        stime_t i_target_time = MP4_rescale_qtime( target_time, p_data->i_timescale );

        /* sidx refers to offsets from end of sidx pos in the file + first offset */
        uint64_t i_pos = p_data->i_first_offset + p_sidx->i_pos + p_sidx->i_size;
        stime_t i_time = 0;
        for( uint16_t i=0; i<p_data->i_reference_count; i++ )
        {
            if(p_data->p_items[i].b_reference_type != 0)
                continue;
            if( i_time + p_data->p_items[i].i_subsegment_duration > i_target_time )
            {
                *pi_sampletime = MP4_rescale_mtime( i_time, p_data->i_timescale );
                *pi_moof_pos = i_pos;
                return VLC_SUCCESS;
            }
            i_pos += p_data->p_items[i].i_referenced_size;
            i_time += p_data->p_items[i].i_subsegment_duration;
        }
    }
    return VLC_EGENERIC;
}