#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  subpicture_t ;
typedef  int /*<<< orphan*/  decoder_t ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/ * DecodePacket (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Reassemble (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int VLCDEC_SUCCESS ; 
 int /*<<< orphan*/  decoder_QueueSub (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int Decode( decoder_t *p_dec, block_t *p_block )
{
#ifndef NDEBUG
    msg_Dbg( p_dec, "Decode" );
#endif

    if( p_block == NULL ) /* No Drain */
        return VLCDEC_SUCCESS;

    if( !(p_block = Reassemble( p_dec, p_block )) )
        return VLCDEC_SUCCESS;

    /* Parse and decode */
    subpicture_t *p_spu = DecodePacket( p_dec, p_block );
    if( p_spu != NULL )
        decoder_QueueSub( p_dec, p_spu );
    return VLCDEC_SUCCESS;
}