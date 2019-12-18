#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_19__ {scalar_t__ i_state; scalar_t__ i_spu_size; TYPE_3__* p_spu; } ;
typedef  TYPE_2__ decoder_sys_t ;
struct TYPE_20__ {scalar_t__ i_buffer; scalar_t__ i_pts; int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  ParseHeader (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ParseMetaInfo (TYPE_1__*,TYPE_3__*) ; 
 scalar_t__ SPU_HEADER_LEN ; 
 scalar_t__ SUBTITLE_BLOCK_EMPTY ; 
 scalar_t__ SUBTITLE_BLOCK_PARTIAL ; 
 scalar_t__ VLC_TICK_INVALID ; 
 int /*<<< orphan*/  block_ChainAppend (TYPE_3__**,TYPE_3__*) ; 
 TYPE_3__* block_ChainGather (TYPE_3__*) ; 
 int /*<<< orphan*/  block_Release (TYPE_3__*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*,...) ; 

__attribute__((used)) static block_t *Reassemble( decoder_t *p_dec, block_t *p_block )
{
    decoder_sys_t *p_sys = p_dec->p_sys;

    if( p_block->i_buffer < SPU_HEADER_LEN )
    {
        msg_Dbg( p_dec, "invalid packet header (size %zu < %u)" ,
                 p_block->i_buffer, SPU_HEADER_LEN );
        block_Release( p_block );
        return NULL;
    }

    /* From the scant data on the format, there is only only way known
     * to detect the first packet in a subtitle.  The first packet
     * seems to have a valid PTS while later packets for the same
     * image don't. */
    if( p_sys->i_state == SUBTITLE_BLOCK_EMPTY && p_block->i_pts == VLC_TICK_INVALID )
    {
        msg_Warn( p_dec, "first packet expected but no PTS present");
        return NULL;
    }

    p_block->p_buffer += SPU_HEADER_LEN;
    p_block->i_buffer -= SPU_HEADER_LEN;

    /* First packet in the subtitle block */
    if( p_sys->i_state == SUBTITLE_BLOCK_EMPTY ) ParseHeader( p_dec, p_block );

    block_ChainAppend( &p_sys->p_spu, p_block );
    p_sys->p_spu = block_ChainGather( p_sys->p_spu );

    if( p_sys->p_spu->i_buffer >= p_sys->i_spu_size )
    {
        block_t *p_spu = p_sys->p_spu;

        if( p_spu->i_buffer != p_sys->i_spu_size )
        {
            msg_Warn( p_dec, "SPU packets size=%zu should be %zu",
                      p_spu->i_buffer, p_sys->i_spu_size );
        }

        msg_Dbg( p_dec, "subtitle packet complete, size=%zuu", p_spu->i_buffer);

        ParseMetaInfo( p_dec, p_spu );

        p_sys->i_state = SUBTITLE_BLOCK_EMPTY;
        p_sys->p_spu = 0;
        return p_spu;
    }
    else
    {
        /* Not last block in subtitle, so wait for another. */
        p_sys->i_state = SUBTITLE_BLOCK_PARTIAL;
    }

    return NULL;
}