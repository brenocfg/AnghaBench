#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_12__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_25__ {int /*<<< orphan*/  out; int /*<<< orphan*/  s; TYPE_5__* p_sys; } ;
typedef  TYPE_4__ demux_t ;
struct TYPE_24__ {int i_bytes; int i_frames; int i_frame_samples; } ;
struct TYPE_22__ {scalar_t__ b_use_word; } ;
struct TYPE_26__ {int b_start; int b_initial_sync_failed; int i_bitrate_avg; int b_estimate_bitrate; TYPE_9__* p_packetizer; TYPE_3__ xing; scalar_t__ p_es; int /*<<< orphan*/  b_big_endian; TYPE_1__ codec; int /*<<< orphan*/  i_packet_size; } ;
typedef  TYPE_5__ demux_sys_t ;
struct TYPE_27__ {scalar_t__ i_buffer; struct TYPE_27__* p_next; int /*<<< orphan*/  i_dts; int /*<<< orphan*/  i_pts; int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_6__ block_t ;
struct TYPE_23__ {int i_rate; } ;
struct TYPE_21__ {int b_packetized; int i_bitrate; TYPE_2__ audio; } ;
struct TYPE_28__ {TYPE_12__ fmt_out; TYPE_6__* (* pf_packetize ) (TYPE_9__*,TYPE_6__**) ;} ;

/* Variables and functions */
 int INT64_C (int) ; 
 int /*<<< orphan*/  VLC_TICK_0 ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 TYPE_6__* block_Alloc (scalar_t__) ; 
 int /*<<< orphan*/  block_ChainLastAppend (TYPE_6__***,TYPE_6__*) ; 
 int /*<<< orphan*/  block_CopyProperties (TYPE_6__*,TYPE_6__*) ; 
 int /*<<< orphan*/  block_Release (TYPE_6__*) ; 
 scalar_t__ es_out_Add (int /*<<< orphan*/ ,TYPE_12__*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_4__*,char*) ; 
 TYPE_6__* stub1 (TYPE_9__*,TYPE_6__**) ; 
 int /*<<< orphan*/  swab (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_6__* vlc_stream_Block (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vlc_stream_Read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int vlc_stream_Tell (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool Parse( demux_t *p_demux, block_t **pp_output )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    block_t *p_block_in, *p_block_out;

    *pp_output = NULL;

    if( p_sys->codec.b_use_word )
    {
        /* Make sure we are word aligned */
        int64_t i_pos = vlc_stream_Tell( p_demux->s );
        if( (i_pos & 1) && vlc_stream_Read( p_demux->s, NULL, 1 ) != 1 )
            return true;
    }

    p_block_in = vlc_stream_Block( p_demux->s, p_sys->i_packet_size );
    bool b_eof = p_block_in == NULL;

    if( p_block_in )
    {
        if( p_sys->codec.b_use_word && !p_sys->b_big_endian && p_block_in->i_buffer > 0 )
        {
            /* Convert to big endian */
            block_t *old = p_block_in;
            p_block_in = block_Alloc( p_block_in->i_buffer );
            if( p_block_in )
            {
                block_CopyProperties( p_block_in, old );
                swab( old->p_buffer, p_block_in->p_buffer, old->i_buffer );
            }
            block_Release( old );
        }

        if( p_block_in )
        {
            p_block_in->i_pts =
            p_block_in->i_dts = (p_sys->b_start || p_sys->b_initial_sync_failed) ?
                                 VLC_TICK_0 : VLC_TICK_INVALID;
        }
    }
    p_sys->b_initial_sync_failed = p_sys->b_start; /* Only try to resync once */

    while( ( p_block_out = p_sys->p_packetizer->pf_packetize( p_sys->p_packetizer, p_block_in ? &p_block_in : NULL ) ) )
    {
        p_sys->b_initial_sync_failed = false;
        while( p_block_out )
        {
            if( !p_sys->p_es )
            {
                p_sys->p_packetizer->fmt_out.b_packetized = true;
                p_sys->p_es = es_out_Add( p_demux->out,
                                          &p_sys->p_packetizer->fmt_out);


                /* Try the xing header */
                if( p_sys->xing.i_bytes && p_sys->xing.i_frames &&
                    p_sys->xing.i_frame_samples )
                {
                    p_sys->i_bitrate_avg = p_sys->xing.i_bytes * INT64_C(8) *
                        p_sys->p_packetizer->fmt_out.audio.i_rate /
                        p_sys->xing.i_frames / p_sys->xing.i_frame_samples;

                    if( p_sys->i_bitrate_avg > 0 )
                        p_sys->b_estimate_bitrate = false;
                }
                /* Use the bitrate as initual value */
                if( p_sys->b_estimate_bitrate )
                    p_sys->i_bitrate_avg = p_sys->p_packetizer->fmt_out.i_bitrate;
            }

            block_t *p_next = p_block_out->p_next;
            p_block_out->p_next = NULL;

            block_ChainLastAppend( &pp_output, p_block_out );

            p_block_out = p_next;
        }
    }

    if( p_sys->b_initial_sync_failed )
        msg_Dbg( p_demux, "did not sync on first block" );
    p_sys->b_start = false;

    return b_eof;
}