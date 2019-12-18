#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_6__ {scalar_t__ i_cat; scalar_t__ i_codec; } ;
struct TYPE_7__ {scalar_t__ i_pcr; scalar_t__ b_initializing; scalar_t__ b_finished; TYPE_1__ fmt; } ;
typedef  TYPE_2__ logical_stream_t ;
struct TYPE_8__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ demux_t ;
struct TYPE_9__ {int i_streams; TYPE_2__** pp_stream; } ;
typedef  TYPE_4__ demux_sys_t ;

/* Variables and functions */
 scalar_t__ SPU_ES ; 
 scalar_t__ VLC_CODEC_OGGSPOTS ; 
 scalar_t__ VLC_TICK_INVALID ; 

__attribute__((used)) static vlc_tick_t Ogg_GeneratePCR( demux_t * p_demux, bool b_drain )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    /* We will consider the lowest PCR among tracks, because the audio core badly
     * handles PCR rewind (mute)
     */
    vlc_tick_t i_pcr_candidate = VLC_TICK_INVALID;
    for( int i_stream = 0; i_stream < p_sys->i_streams; i_stream++ )
    {
        logical_stream_t *p_stream = p_sys->pp_stream[i_stream];
        if( p_stream->fmt.i_cat == SPU_ES )
            continue;
        if( p_stream->fmt.i_codec == VLC_CODEC_OGGSPOTS )
            continue;
        if( p_stream->i_pcr == VLC_TICK_INVALID )
            continue;
        if ( (!b_drain && p_stream->b_finished) || p_stream->b_initializing )
            continue;
        if( i_pcr_candidate == VLC_TICK_INVALID ||
            p_stream->i_pcr < i_pcr_candidate )
        {
            i_pcr_candidate = p_stream->i_pcr;
        }
    }

    return i_pcr_candidate;
}