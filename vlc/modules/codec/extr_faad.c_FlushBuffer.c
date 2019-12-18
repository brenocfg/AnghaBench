#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* p_block; } ;
typedef  TYPE_1__ decoder_sys_t ;
struct TYPE_6__ {size_t i_buffer; int* p_buffer; } ;
typedef  TYPE_2__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  block_Release (TYPE_2__*) ; 

__attribute__((used)) static void FlushBuffer( decoder_sys_t *p_sys, size_t i_used )
{
    block_t *p_block = p_sys->p_block;
    if( p_block )
    {
        if( i_used < p_block->i_buffer )
        {
            /* Drop padding */
            for( ; i_used < p_block->i_buffer; i_used++ )
                if( p_block->p_buffer[i_used] != 0x00 )
                    break;

            p_block->i_buffer -= i_used;
            p_block->p_buffer += i_used;
        }
        else p_block->i_buffer = 0;
        if( p_block->i_buffer == 0 )
        {
            block_Release( p_block );
            p_sys->p_block = NULL;
        }
    }
}