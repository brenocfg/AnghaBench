#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  TYPE_1__* (* pf_annexb_nal_packetizer ) (int /*<<< orphan*/ *,int*,TYPE_1__*) ;
typedef  int /*<<< orphan*/  decoder_t ;
struct TYPE_14__ {int i_flags; int* p_buffer; size_t i_buffer; int /*<<< orphan*/  i_pts; int /*<<< orphan*/  i_dts; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 int BLOCK_FLAG_CORRUPTED ; 
 TYPE_1__* block_Alloc (int) ; 
 int /*<<< orphan*/  block_ChainAppend (TYPE_1__**,TYPE_1__*) ; 
 TYPE_1__* block_Realloc (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  block_Release (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,int) ; 

block_t *PacketizeXXC1( decoder_t *p_dec, uint8_t i_nal_length_size,
                        block_t **pp_block, pf_annexb_nal_packetizer pf_nal_parser )
{
    block_t       *p_block;
    block_t       *p_ret = NULL;
    uint8_t       *p;

    if( !pp_block || !*pp_block )
        return NULL;
    if( (*pp_block)->i_flags&(BLOCK_FLAG_CORRUPTED) )
    {
        block_Release( *pp_block );
        return NULL;
    }

    p_block = *pp_block;
    *pp_block = NULL;

    for( p = p_block->p_buffer; p < &p_block->p_buffer[p_block->i_buffer]; )
    {
        bool b_dummy;
        int i_size = 0;
        int i;

        if( &p_block->p_buffer[p_block->i_buffer] - p < i_nal_length_size )
            break;

        for( i = 0; i < i_nal_length_size; i++ )
        {
            i_size = (i_size << 8) | (*p++);
        }

        if( i_size <= 0 ||
            i_size > ( p_block->p_buffer + p_block->i_buffer - p ) )
        {
            msg_Err( p_dec, "Broken frame : size %d is too big", i_size );
            break;
        }

        /* Convert AVC to AnnexB */
        block_t *p_nal;
        /* If data exactly match remaining bytes (1 NAL only or trailing one) */
        if( i_size == p_block->p_buffer + p_block->i_buffer - p )
        {
            p_block->i_buffer = i_size;
            p_block->p_buffer = p;
            p_nal = block_Realloc( p_block, 4, i_size );
            if( p_nal )
                p_block = NULL;
        }
        else
        {
            p_nal = block_Alloc( 4 + i_size );
            if( p_nal )
            {
                p_nal->i_dts = p_block->i_dts;
                p_nal->i_pts = p_block->i_pts;
                /* Copy nalu */
                memcpy( &p_nal->p_buffer[4], p, i_size );
            }
            p += i_size;
        }

        if( !p_nal )
            break;

        /* Add start code */
        p_nal->p_buffer[0] = 0x00;
        p_nal->p_buffer[1] = 0x00;
        p_nal->p_buffer[2] = 0x00;
        p_nal->p_buffer[3] = 0x01;

        /* Parse the NAL */
        block_t *p_pic;
        if( ( p_pic = pf_nal_parser( p_dec, &b_dummy, p_nal ) ) )
        {
            block_ChainAppend( &p_ret, p_pic );
        }

        if( !p_block )
            break;
    }

    if( p_block )
        block_Release( p_block );

    return p_ret;
}