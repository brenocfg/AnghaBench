#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  float vlc_tick_t ;
typedef  size_t uint64_t ;
struct TYPE_13__ {int /*<<< orphan*/  out; int /*<<< orphan*/  s; TYPE_4__* p_sys; } ;
typedef  TYPE_3__ demux_t ;
struct TYPE_14__ {float i_length; scalar_t__ i_preroll_start; size_t i_data_begin; TYPE_2__* p_fp; int /*<<< orphan*/  p_root; } ;
typedef  TYPE_4__ demux_sys_t ;
struct TYPE_15__ {size_t i_index_entry_time_interval; size_t i_index_entry_count; TYPE_1__* index_entry; } ;
typedef  TYPE_5__ asf_object_index_t ;
struct TYPE_12__ {scalar_t__ i_preroll; size_t i_min_data_packet_size; } ;
struct TYPE_11__ {scalar_t__ i_packet_number; } ;

/* Variables and functions */
 TYPE_5__* ASF_FindObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ES_OUT_SET_NEXT_DISPLAY_TIME ; 
 size_t MSFTIME_FROM_VLC_TICK (scalar_t__) ; 
 scalar_t__ SEC_FROM_VLC_TICK (float) ; 
 int VLC_EGENERIC ; 
 scalar_t__ VLC_SUCCESS ; 
 scalar_t__ VLC_TICK_0 ; 
 int /*<<< orphan*/  WaitKeyframe (TYPE_3__*) ; 
 int /*<<< orphan*/  asf_object_simple_index_guid ; 
 int /*<<< orphan*/  es_out_Control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_3__*,char*,int,float) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_3__*,char*) ; 
 scalar_t__ vlc_stream_Seek (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int SeekIndex( demux_t *p_demux, vlc_tick_t i_date, float f_pos )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    asf_object_index_t *p_index;

    msg_Dbg( p_demux, "seek with index: %i seconds, position %f",
             i_date >= 0 ? (int)SEC_FROM_VLC_TICK(i_date) : -1, f_pos );

    if( i_date < 0 )
        i_date = p_sys->i_length * f_pos;

    p_sys->i_preroll_start = i_date - p_sys->p_fp->i_preroll;
    if ( p_sys->i_preroll_start < 0 ) p_sys->i_preroll_start = 0;

    p_index = ASF_FindObject( p_sys->p_root, &asf_object_simple_index_guid, 0 );

    uint64_t i_entry = MSFTIME_FROM_VLC_TICK(p_sys->i_preroll_start) / p_index->i_index_entry_time_interval;
    if( i_entry >= p_index->i_index_entry_count )
    {
        msg_Warn( p_demux, "Incomplete index" );
        return VLC_EGENERIC;
    }

    WaitKeyframe( p_demux );

    uint64_t i_offset = (uint64_t)p_index->index_entry[i_entry].i_packet_number *
                        p_sys->p_fp->i_min_data_packet_size;

    if ( vlc_stream_Seek( p_demux->s, i_offset + p_sys->i_data_begin ) == VLC_SUCCESS )
    {
        es_out_Control( p_demux->out, ES_OUT_SET_NEXT_DISPLAY_TIME, VLC_TICK_0 + i_date );
        return VLC_SUCCESS;
    }
    else return VLC_EGENERIC;
}