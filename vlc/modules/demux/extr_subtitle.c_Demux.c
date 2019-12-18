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
typedef  int vlc_tick_t ;
struct TYPE_11__ {int i_start; int i_stop; } ;
typedef  TYPE_2__ subtitle_t ;
struct TYPE_12__ {int /*<<< orphan*/  out; TYPE_4__* p_sys; } ;
typedef  TYPE_3__ demux_t ;
struct TYPE_10__ {size_t i_current; size_t i_count; TYPE_2__* p_array; } ;
struct TYPE_13__ {int i_next_demux_date; int f_rate; int b_first_time; TYPE_1__ subtitles; int /*<<< orphan*/  b_slave; int /*<<< orphan*/  es; TYPE_5__* (* pf_convert ) (TYPE_2__ const*) ;} ;
typedef  TYPE_4__ demux_sys_t ;
struct TYPE_14__ {int i_length; scalar_t__ i_pts; scalar_t__ i_dts; } ;
typedef  TYPE_5__ block_t ;

/* Variables and functions */
 int VLC_DEMUXER_EOF ; 
 int VLC_DEMUXER_SUCCESS ; 
 scalar_t__ VLC_TICK_0 ; 
 scalar_t__ VLC_TICK_FROM_MS (int) ; 
 int /*<<< orphan*/  es_out_Send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  es_out_SetPCR (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_5__* stub1 (TYPE_2__ const*) ; 

__attribute__((used)) static int Demux( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;

    vlc_tick_t i_barrier = p_sys->i_next_demux_date;

    while( p_sys->subtitles.i_current < p_sys->subtitles.i_count &&
           ( p_sys->subtitles.p_array[p_sys->subtitles.i_current].i_start *
             p_sys->f_rate ) <= i_barrier )
    {
        const subtitle_t *p_subtitle = &p_sys->subtitles.p_array[p_sys->subtitles.i_current];

        if ( !p_sys->b_slave && p_sys->b_first_time )
        {
            es_out_SetPCR( p_demux->out, VLC_TICK_0 + i_barrier );
            p_sys->b_first_time = false;
        }

        if( p_subtitle->i_start >= 0 )
        {
            block_t *p_block = p_sys->pf_convert( p_subtitle );
            if( p_block )
            {
                p_block->i_dts =
                p_block->i_pts = VLC_TICK_0 + p_subtitle->i_start * p_sys->f_rate;
                if( p_subtitle->i_stop >= 0 && p_subtitle->i_stop >= p_subtitle->i_start )
                    p_block->i_length = (p_subtitle->i_stop - p_subtitle->i_start) * p_sys->f_rate;

                es_out_Send( p_demux->out, p_sys->es, p_block );
            }
        }

        p_sys->subtitles.i_current++;
    }

    if ( !p_sys->b_slave )
    {
        es_out_SetPCR( p_demux->out, VLC_TICK_0 + i_barrier );
        p_sys->i_next_demux_date += VLC_TICK_FROM_MS(125);
    }

    if( p_sys->subtitles.i_current >= p_sys->subtitles.i_count )
        return VLC_DEMUXER_EOF;

    return VLC_DEMUXER_SUCCESS;
}