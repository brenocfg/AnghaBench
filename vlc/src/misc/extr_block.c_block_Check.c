#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned char* p_start; int i_size; unsigned char* p_buffer; int i_buffer; struct TYPE_3__* p_next; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void block_Check (block_t *block)
{
    while (block != NULL)
    {
        unsigned char *start = block->p_start;
        unsigned char *end = block->p_start + block->i_size;
        unsigned char *bufstart = block->p_buffer;
        unsigned char *bufend = block->p_buffer + block->i_buffer;

        assert (start <= end);
        assert (bufstart <= bufend);
        assert (bufstart >= start);
        assert (bufend <= end);

        block = block->p_next;
    }
}