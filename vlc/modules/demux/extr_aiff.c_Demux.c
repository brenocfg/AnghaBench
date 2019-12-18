#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_11__ {int /*<<< orphan*/  out; int /*<<< orphan*/  s; TYPE_4__* p_sys; } ;
typedef  TYPE_3__ demux_t ;
struct TYPE_9__ {int i_rate; } ;
struct TYPE_10__ {TYPE_1__ audio; } ;
struct TYPE_12__ {scalar_t__ i_ssnd_end; int i_ssnd_fsize; int /*<<< orphan*/  es; TYPE_2__ fmt; scalar_t__ i_time; } ;
typedef  TYPE_4__ demux_sys_t ;
struct TYPE_13__ {int /*<<< orphan*/  i_buffer; scalar_t__ i_pts; scalar_t__ i_dts; } ;
typedef  TYPE_5__ block_t ;

/* Variables and functions */
 int VLC_DEMUXER_EOF ; 
 int VLC_DEMUXER_SUCCESS ; 
 scalar_t__ VLC_TICK_0 ; 
 int /*<<< orphan*/  es_out_Send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  es_out_SetPCR (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_5__* vlc_stream_Block (int /*<<< orphan*/ ,int) ; 
 scalar_t__ vlc_stream_Tell (int /*<<< orphan*/ ) ; 
 int vlc_tick_from_samples (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int Demux( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    int64_t     i_tell = vlc_stream_Tell( p_demux->s );

    block_t     *p_block;
    int         i_read;

    if( p_sys->i_ssnd_end > 0 && i_tell >= p_sys->i_ssnd_end )
    {
        /* EOF */
        return VLC_DEMUXER_EOF;
    }

    /* Set PCR */
    es_out_SetPCR( p_demux->out, VLC_TICK_0 + p_sys->i_time);

    /* we will read 100ms at once */
    i_read = p_sys->i_ssnd_fsize * ( p_sys->fmt.audio.i_rate / 10 );
    if( p_sys->i_ssnd_end > 0 && p_sys->i_ssnd_end - i_tell < i_read )
    {
        i_read = p_sys->i_ssnd_end - i_tell;
    }
    if( ( p_block = vlc_stream_Block( p_demux->s, i_read ) ) == NULL )
    {
        return VLC_DEMUXER_EOF;
    }

    p_block->i_dts =
    p_block->i_pts = VLC_TICK_0 + p_sys->i_time;

    p_sys->i_time += vlc_tick_from_samples(p_block->i_buffer,
                                           p_sys->i_ssnd_fsize) /
                     p_sys->fmt.audio.i_rate;

    /* */
    es_out_Send( p_demux->out, p_sys->es, p_block );
    return VLC_DEMUXER_SUCCESS;
}