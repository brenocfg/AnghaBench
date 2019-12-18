#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  subpicture_t ;
typedef  int /*<<< orphan*/  decoder_t ;
struct TYPE_7__ {int i_flags; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 int BLOCK_FLAG_CORRUPTED ; 
 int /*<<< orphan*/ * DecodePacket (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* Reassemble (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int VLCDEC_SUCCESS ; 
 int /*<<< orphan*/  block_Release (TYPE_1__*) ; 
 int /*<<< orphan*/  decoder_QueueSub (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int Decode( decoder_t *p_dec, block_t *p_block )
{
    block_t *p_data;

    if( p_block == NULL ) /* No Drain */
        return VLCDEC_SUCCESS;

    if( p_block->i_flags & BLOCK_FLAG_CORRUPTED )
    {
        block_Release( p_block );
        return VLCDEC_SUCCESS;
    }

    if( !(p_data = Reassemble( p_dec, p_block )) )
        return VLCDEC_SUCCESS;

    /* Parse and decode */
    subpicture_t *p_spu = DecodePacket( p_dec, p_data );
    block_Release( p_data );
    if( p_spu != NULL )
        decoder_QueueSub( p_dec, p_spu );
    return VLCDEC_SUCCESS;
}