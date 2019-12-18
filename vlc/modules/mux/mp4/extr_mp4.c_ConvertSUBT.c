#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int i_buffer; char* p_buffer; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 TYPE_1__* block_Realloc (TYPE_1__*,int,int) ; 

__attribute__((used)) static block_t *ConvertSUBT(block_t *p_block)
{
    p_block = block_Realloc(p_block, 2, p_block->i_buffer);
    if( !p_block )
        return NULL;
    /* No trailling '\0' */
    if (p_block->i_buffer > 2 && p_block->p_buffer[p_block->i_buffer-1] == '\0')
        p_block->i_buffer--;

    p_block->p_buffer[0] = ((p_block->i_buffer - 2) >> 8)&0xff;
    p_block->p_buffer[1] = ((p_block->i_buffer - 2)     )&0xff;

    return p_block;
}