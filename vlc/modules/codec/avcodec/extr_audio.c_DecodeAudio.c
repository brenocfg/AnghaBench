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
 int DecodeBlock (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int VLCDEC_SUCCESS ; 

__attribute__((used)) static int DecodeAudio( decoder_t *p_dec, block_t *p_block )
{
    block_t **pp_block = p_block ? &p_block : NULL;
    int i_ret;
    do
    {
        i_ret = DecodeBlock( p_dec, pp_block );
    }
    while( i_ret == VLCDEC_SUCCESS && pp_block && *pp_block );

    return i_ret;
}