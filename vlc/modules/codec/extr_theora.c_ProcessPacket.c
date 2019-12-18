#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ogg_packet ;
struct TYPE_11__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ decoder_t ;
struct TYPE_10__ {int /*<<< orphan*/  fps_numerator; int /*<<< orphan*/  fps_denominator; } ;
struct TYPE_12__ {scalar_t__ i_pts; TYPE_1__ ti; scalar_t__ b_packetizer; } ;
typedef  TYPE_3__ decoder_sys_t ;
struct TYPE_13__ {int i_flags; scalar_t__ i_pts; scalar_t__ i_dts; scalar_t__ i_length; } ;
typedef  TYPE_4__ block_t ;

/* Variables and functions */
 int BLOCK_FLAG_CORRUPTED ; 
 int BLOCK_FLAG_DISCONTINUITY ; 
 void* DecodePacket (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Flush (TYPE_2__*) ; 
 scalar_t__ VLC_TICK_INVALID ; 
 int /*<<< orphan*/  block_Release (TYPE_4__*) ; 
 scalar_t__ vlc_tick_from_samples (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *ProcessPacket( decoder_t *p_dec, ogg_packet *p_oggpacket,
                            block_t *p_block )
{
    decoder_sys_t *p_sys = p_dec->p_sys;
    void *p_buf;

    if( p_block->i_flags & (BLOCK_FLAG_DISCONTINUITY|BLOCK_FLAG_CORRUPTED) )
    {
        Flush( p_dec );
        if( p_block->i_flags & BLOCK_FLAG_CORRUPTED )
        {
            /* Don't send the a corrupted packet to
             * theora_decode, otherwise we get purple/green display artifacts
             * appearing in the video output */
            block_Release(p_block);
            return NULL;
        }
    }

    /* Date management */
    if( p_block->i_pts != VLC_TICK_INVALID && p_block->i_pts != p_sys->i_pts )
    {
        p_sys->i_pts = p_block->i_pts;
    }

    if( p_sys->b_packetizer )
    {
        /* Date management */
        p_block->i_dts = p_block->i_pts = p_sys->i_pts;

        p_block->i_length = p_sys->i_pts - p_block->i_pts;

        p_buf = p_block;
    }
    else
    {
        p_buf = DecodePacket( p_dec, p_oggpacket );
        block_Release( p_block );
    }

    /* Date management */
    p_sys->i_pts += vlc_tick_from_samples( p_sys->ti.fps_denominator,
                      p_sys->ti.fps_numerator ); /* 1 frame per packet */

    return p_buf;
}