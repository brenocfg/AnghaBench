#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  decoder_t ;
struct TYPE_5__ {int i_buffer; scalar_t__* p_buffer; int /*<<< orphan*/  i_dts; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 int ParseBlock (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int VLCDEC_SUCCESS ; 
 int /*<<< orphan*/  block_Release (TYPE_1__*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int DecodeBlock( decoder_t *p_dec, block_t *p_block )
{
    if( p_block == NULL ) /* No Drain */
        return VLCDEC_SUCCESS;

    int ret = ParseBlock( p_dec, p_block );
#ifdef TTML_DEBUG
    if( p_block->i_buffer )
    {
        p_block->p_buffer[p_block->i_buffer - 1] = 0;
        msg_Dbg(p_dec,"time %ld %s", p_block->i_dts, p_block->p_buffer);
    }
#endif
    block_Release( p_block );
    return ret;
}