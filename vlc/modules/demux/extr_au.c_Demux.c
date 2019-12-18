#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  out; int /*<<< orphan*/  s; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_9__ {scalar_t__ i_frame_length; scalar_t__ i_time; int /*<<< orphan*/  es; int /*<<< orphan*/  i_frame_size; } ;
typedef  TYPE_2__ demux_sys_t ;
struct TYPE_10__ {scalar_t__ i_pts; scalar_t__ i_dts; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 int VLC_DEMUXER_EOF ; 
 int VLC_DEMUXER_SUCCESS ; 
 scalar_t__ VLC_TICK_0 ; 
 int /*<<< orphan*/  es_out_Send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  es_out_SetPCR (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*) ; 
 TYPE_3__* vlc_stream_Block (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Demux( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    block_t     *p_block;

    /* set PCR */
    es_out_SetPCR( p_demux->out, VLC_TICK_0 + p_sys->i_time );

    p_block = vlc_stream_Block( p_demux->s, p_sys->i_frame_size );
    if( p_block == NULL )
    {
        msg_Warn( p_demux, "cannot read data" );
        return VLC_DEMUXER_EOF;
    }

    p_block->i_dts =
    p_block->i_pts = VLC_TICK_0 + p_sys->i_time;
    es_out_Send( p_demux->out, p_sys->es, p_block );

    p_sys->i_time += p_sys->i_frame_length;

    return VLC_DEMUXER_SUCCESS;
}