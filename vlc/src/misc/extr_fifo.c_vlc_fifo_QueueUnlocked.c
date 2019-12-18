#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* p_next; scalar_t__ i_buffer; } ;
typedef  TYPE_1__ block_t ;
struct TYPE_7__ {int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_depth; TYPE_1__** pp_last; int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ block_fifo_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_fifo_Signal (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_mutex_assert (int /*<<< orphan*/ *) ; 

void vlc_fifo_QueueUnlocked(block_fifo_t *fifo, block_t *block)
{
    vlc_mutex_assert(&fifo->lock);
    assert(*(fifo->pp_last) == NULL);

    *(fifo->pp_last) = block;

    while (block != NULL)
    {
        fifo->pp_last = &block->p_next;
        fifo->i_depth++;
        fifo->i_size += block->i_buffer;

        block = block->p_next;
    }

    vlc_fifo_Signal(fifo);
}