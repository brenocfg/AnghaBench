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
 int /*<<< orphan*/ * ParseText (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int VLCDEC_SUCCESS ; 
 int /*<<< orphan*/  block_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decoder_QueueSub (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int DecodeBlock( decoder_t *p_dec, block_t *p_block )
{
    subpicture_t *p_spu;

    if( p_block == NULL ) /* No Drain */
        return VLCDEC_SUCCESS;

    p_spu = ParseText( p_dec, p_block );

    block_Release( p_block );
    if( p_spu != NULL )
        decoder_QueueSub( p_dec, p_spu );
    return VLCDEC_SUCCESS;
}