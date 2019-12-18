#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int* p_buffer; int /*<<< orphan*/  i_buffer; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 TYPE_1__* AV1_Unpack_Sample_ExpandSize (TYPE_1__*) ; 
 TYPE_1__* block_Realloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline block_t * AV1_Unpack_Sample(block_t *p_block)
{
    /* Restore last size field if missing */
    p_block = AV1_Unpack_Sample_ExpandSize(p_block);
    /* Reinsert removed TU: See av1-isobmff 2.4 */
    if(p_block &&
       (p_block->p_buffer[0] & 0x81) == 0 && /* reserved flags */
       (p_block->p_buffer[0] & 0x7A) != 0x12) /* no TEMPORAL_DELIMITER */
    {
        p_block = block_Realloc(p_block, 2, p_block->i_buffer);
        if(p_block)
        {
            p_block->p_buffer[0] = 0x12;
            p_block->p_buffer[1] = 0x00;
        }
    }
    return p_block;
}