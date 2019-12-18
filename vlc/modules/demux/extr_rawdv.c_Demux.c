#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  out; int /*<<< orphan*/  s; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_10__ {int /*<<< orphan*/  f_rate; scalar_t__ i_pcr; scalar_t__ b_hurry_up; scalar_t__ p_es_video; scalar_t__ p_es_audio; int /*<<< orphan*/  frame_size; scalar_t__ i_dsf; } ;
typedef  TYPE_2__ demux_sys_t ;
struct TYPE_11__ {scalar_t__ i_pts; scalar_t__ i_dts; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  ES_OUT_GET_ES_STATE ; 
 int VLC_DEMUXER_EOF ; 
 int VLC_DEMUXER_SUCCESS ; 
 scalar_t__ VLC_TICK_0 ; 
 scalar_t__ VLC_TICK_FROM_MS (int) ; 
 TYPE_3__* dv_extract_audio (TYPE_3__*) ; 
 int /*<<< orphan*/  es_out_Control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int /*<<< orphan*/  es_out_Send (int /*<<< orphan*/ ,scalar_t__,TYPE_3__*) ; 
 int /*<<< orphan*/  es_out_SetPCR (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_3__* vlc_stream_Block (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_tick_now () ; 
 scalar_t__ vlc_tick_rate_duration (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Demux( demux_t *p_demux )
{
    demux_sys_t *p_sys  = p_demux->p_sys;
    block_t     *p_block;
    bool  b_audio = false;

    if( p_sys->b_hurry_up )
    {
         /* 3 frames */
        p_sys->i_pcr = vlc_tick_now() + (p_sys->i_dsf ? VLC_TICK_FROM_MS(120) : VLC_TICK_FROM_MS(90));
    }

    /* Call the pace control */
    es_out_SetPCR( p_demux->out, VLC_TICK_0 + p_sys->i_pcr );
    p_block = vlc_stream_Block( p_demux->s, p_sys->frame_size );
    if( p_block == NULL )
        return VLC_DEMUXER_EOF;

    if( p_sys->p_es_audio )
    {
        es_out_Control( p_demux->out, ES_OUT_GET_ES_STATE,
                        p_sys->p_es_audio, &b_audio );
    }

    p_block->i_dts =
    p_block->i_pts = VLC_TICK_0 + p_sys->i_pcr;

    if( b_audio )
    {
        block_t *p_audio_block = dv_extract_audio( p_block );
        if( p_audio_block )
            es_out_Send( p_demux->out, p_sys->p_es_audio, p_audio_block );
    }

    es_out_Send( p_demux->out, p_sys->p_es_video, p_block );

    if( !p_sys->b_hurry_up )
    {
        p_sys->i_pcr += vlc_tick_rate_duration( p_sys->f_rate );
    }

    return VLC_DEMUXER_SUCCESS;
}