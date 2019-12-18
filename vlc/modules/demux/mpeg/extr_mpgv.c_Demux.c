#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  out; int /*<<< orphan*/  s; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_11__ {int b_start; int /*<<< orphan*/  p_es; TYPE_6__* p_packetizer; } ;
typedef  TYPE_2__ demux_sys_t ;
struct TYPE_12__ {struct TYPE_12__* p_next; int /*<<< orphan*/  i_dts; int /*<<< orphan*/  i_pts; } ;
typedef  TYPE_3__ block_t ;
struct TYPE_13__ {TYPE_3__* (* pf_packetize ) (TYPE_6__*,TYPE_3__**) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MPGV_PACKET_SIZE ; 
 int VLC_DEMUXER_EOF ; 
 int VLC_DEMUXER_SUCCESS ; 
 int /*<<< orphan*/  VLC_TICK_0 ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  es_out_Send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  es_out_SetPCR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* stub1 (TYPE_6__*,TYPE_3__**) ; 
 TYPE_3__* vlc_stream_Block (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Demux( demux_t *p_demux )
{
    demux_sys_t  *p_sys = p_demux->p_sys;
    block_t *p_block_in, *p_block_out;
    bool b_eof = false;

    if( ( p_block_in = vlc_stream_Block( p_demux->s, MPGV_PACKET_SIZE ) ) == NULL )
    {
        b_eof = true;
    }

    if( p_block_in )
    {
        p_block_in->i_pts =
        p_block_in->i_dts = ( p_sys->b_start ) ? VLC_TICK_0 : VLC_TICK_INVALID;
    }

    while( (p_block_out = p_sys->p_packetizer->pf_packetize( p_sys->p_packetizer,
                                                             p_block_in ? &p_block_in : NULL )) )
    {
        p_sys->b_start = false;

        while( p_block_out )
        {
            block_t *p_next = p_block_out->p_next;

            es_out_SetPCR( p_demux->out, p_block_out->i_dts );

            p_block_out->p_next = NULL;
            es_out_Send( p_demux->out, p_sys->p_es, p_block_out );

            p_block_out = p_next;
        }
    }
    return (b_eof) ? VLC_DEMUXER_EOF : VLC_DEMUXER_SUCCESS;
}