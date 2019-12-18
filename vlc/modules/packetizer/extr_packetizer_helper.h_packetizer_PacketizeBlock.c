#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {TYPE_2__* p_block; int /*<<< orphan*/  p_chain; } ;
struct TYPE_21__ {int i_state; int i_offset; size_t i_au_prepend; size_t i_au_min_size; TYPE_9__ bytestream; int /*<<< orphan*/  p_private; int /*<<< orphan*/  (* pf_validate ) (int /*<<< orphan*/ ,TYPE_2__*) ;TYPE_2__* (* pf_parse ) (int /*<<< orphan*/ ,int*,TYPE_2__*) ;int /*<<< orphan*/  p_au_prepend; int /*<<< orphan*/  i_startcode; int /*<<< orphan*/  pf_startcode_helper; int /*<<< orphan*/  p_startcode; int /*<<< orphan*/  (* pf_reset ) (int /*<<< orphan*/ ,int) ;} ;
typedef  TYPE_1__ packetizer_t ;
struct TYPE_22__ {int i_flags; size_t i_buffer; void* i_pts; void* i_dts; int /*<<< orphan*/ * p_buffer; } ;
typedef  TYPE_2__ block_t ;

/* Variables and functions */
 int BLOCK_FLAG_AU_END ; 
 int BLOCK_FLAG_CORRUPTED ; 
 int BLOCK_FLAG_DISCONTINUITY ; 
#define  STATE_NEXT_SYNC 129 
#define  STATE_NOSYNC 128 
 void* VLC_TICK_INVALID ; 
 TYPE_2__* block_Alloc (size_t) ; 
 int /*<<< orphan*/  block_BytestreamEmpty (TYPE_9__*) ; 
 int /*<<< orphan*/  block_BytestreamFlush (TYPE_9__*) ; 
 TYPE_2__* block_BytestreamPop (TYPE_9__*) ; 
 int /*<<< orphan*/  block_BytestreamPush (TYPE_9__*,TYPE_2__*) ; 
 int block_BytestreamRemaining (TYPE_9__*) ; 
 int /*<<< orphan*/  block_FindStartcodeFromOffset (TYPE_9__*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  block_GetBytes (TYPE_9__*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  block_Release (TYPE_2__*) ; 
 int /*<<< orphan*/  block_SkipBytes (TYPE_9__*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 TYPE_2__* stub2 (int /*<<< orphan*/ ,int*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static block_t *packetizer_PacketizeBlock( packetizer_t *p_pack, block_t **pp_block )
{
    block_t *p_block = ( pp_block ) ? *pp_block : NULL;

    if( p_block == NULL && p_pack->bytestream.p_block == NULL )
        return NULL;

    if( p_block && unlikely( p_block->i_flags&(BLOCK_FLAG_DISCONTINUITY|BLOCK_FLAG_CORRUPTED) ) )
    {
        block_t *p_drained = packetizer_PacketizeBlock( p_pack, NULL );
        if( p_drained )
            return p_drained;

        p_pack->i_state = STATE_NOSYNC;
        block_BytestreamEmpty( &p_pack->bytestream );
        p_pack->i_offset = 0;
        p_pack->pf_reset( p_pack->p_private, false );
    }

    if( p_block )
        block_BytestreamPush( &p_pack->bytestream, p_block );

    for( ;; )
    {
        bool b_used_ts;
        block_t *p_pic;

        switch( p_pack->i_state )
        {
        case STATE_NOSYNC:
            /* Find a startcode */
            if( !block_FindStartcodeFromOffset( &p_pack->bytestream, &p_pack->i_offset,
                                                p_pack->p_startcode, p_pack->i_startcode,
                                                p_pack->pf_startcode_helper, NULL ) )
                p_pack->i_state = STATE_NEXT_SYNC;

            if( p_pack->i_offset )
            {
                block_SkipBytes( &p_pack->bytestream, p_pack->i_offset );
                p_pack->i_offset = 0;
                block_BytestreamFlush( &p_pack->bytestream );
            }

            if( p_pack->i_state != STATE_NEXT_SYNC )
                return NULL; /* Need more data */

            p_pack->i_offset = 1; /* To find next startcode */
            /* fallthrough */

        case STATE_NEXT_SYNC:
            /* Find the next startcode */
            if( block_FindStartcodeFromOffset( &p_pack->bytestream, &p_pack->i_offset,
                                               p_pack->p_startcode, p_pack->i_startcode,
                                               p_pack->pf_startcode_helper, NULL ) )
            {
                if( pp_block /* not flushing */ || !p_pack->bytestream.p_chain )
                    return NULL; /* Need more data */

                /* When flusing and we don't find a startcode, suppose that
                 * the data extend up to the end */
                p_pack->i_offset = block_BytestreamRemaining(&p_pack->bytestream);
                if( p_pack->i_offset == 0 )
                    return NULL;

                if( p_pack->i_offset <= (size_t)p_pack->i_startcode &&
                    (p_pack->bytestream.p_block->i_flags & BLOCK_FLAG_AU_END) == 0 )
                    return NULL;
            }

            block_BytestreamFlush( &p_pack->bytestream );

            /* Get the new fragment and set the pts/dts */
            block_t *p_block_bytestream = p_pack->bytestream.p_block;

            p_pic = block_Alloc( p_pack->i_offset + p_pack->i_au_prepend );
            p_pic->i_pts = p_block_bytestream->i_pts;
            p_pic->i_dts = p_block_bytestream->i_dts;

            /* Do not wait for next sync code if notified block ends AU */
            if( (p_block_bytestream->i_flags & BLOCK_FLAG_AU_END) &&
                 p_block_bytestream->i_buffer == p_pack->i_offset )
            {
                p_pic->i_flags |= BLOCK_FLAG_AU_END;
            }

            block_GetBytes( &p_pack->bytestream, &p_pic->p_buffer[p_pack->i_au_prepend],
                            p_pic->i_buffer - p_pack->i_au_prepend );
            if( p_pack->i_au_prepend > 0 )
                memcpy( p_pic->p_buffer, p_pack->p_au_prepend, p_pack->i_au_prepend );

            p_pack->i_offset = 0;

            /* Parse the NAL */
            if( p_pic->i_buffer < p_pack->i_au_min_size )
            {
                block_Release( p_pic );
                p_pic = NULL;
            }
            else
            {
                p_pic = p_pack->pf_parse( p_pack->p_private, &b_used_ts, p_pic );
                if( b_used_ts )
                {
                    p_block_bytestream->i_dts = VLC_TICK_INVALID;
                    p_block_bytestream->i_pts = VLC_TICK_INVALID;
                }
            }

            if( !p_pic )
            {
                p_pack->i_state = STATE_NOSYNC;
                break;
            }
            if( p_pack->pf_validate( p_pack->p_private, p_pic ) )
            {
                p_pack->i_state = STATE_NOSYNC;
                block_Release( p_pic );
                break;
            }

            /* So p_block doesn't get re-added several times */
            if( pp_block )
                *pp_block = block_BytestreamPop( &p_pack->bytestream );

            p_pack->i_state = STATE_NOSYNC;

            return p_pic;
        }
    }
}