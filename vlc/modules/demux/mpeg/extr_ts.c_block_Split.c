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
struct TYPE_5__ {size_t i_buffer; int /*<<< orphan*/ * p_buffer; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 TYPE_1__* block_Alloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static bool block_Split( block_t **pp_block, block_t **pp_remain, size_t i_offset )
{
    block_t *p_block = *pp_block;
    block_t *p_split = NULL;
    *pp_remain = NULL;

    size_t i_tocopy = p_block->i_buffer - i_offset;
    if( i_tocopy > i_offset ) /* make new block for head */
    {
        if( i_offset > 0 )
        {
            p_split = block_Alloc( i_offset );
            if( p_split == NULL )
                return false;
            memcpy( p_split->p_buffer, p_block->p_buffer, i_offset );
            p_block->p_buffer += i_offset;
            p_block->i_buffer -= i_offset;
        }
        *pp_remain = p_block;
        *pp_block = p_split;
    }
    else /* other gets the tail of our split */
    {
        if( i_tocopy > 0 )
        {
            p_split = block_Alloc( i_tocopy );
            if( p_split == NULL )
                return false;
            memcpy( p_split->p_buffer, &p_block->p_buffer[i_offset], i_tocopy );
            p_block->i_buffer -= i_tocopy;
        }
        *pp_remain = p_split;
    }
    return true;
}