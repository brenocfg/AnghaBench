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
typedef  int /*<<< orphan*/  decoder_t ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/ * Packetize (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int VLCDEC_SUCCESS ; 
 int /*<<< orphan*/  decoder_QueueAudio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int DecodeFrame( decoder_t *p_dec, block_t *p_block )
{
    block_t *p_out = Packetize( p_dec, &p_block );
    if( p_out != NULL )
        decoder_QueueAudio( p_dec, p_out );
    return VLCDEC_SUCCESS;
}