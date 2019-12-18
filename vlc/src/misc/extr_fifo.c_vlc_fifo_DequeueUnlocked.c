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
struct TYPE_5__ {scalar_t__ i_buffer; struct TYPE_5__* p_next; } ;
typedef  TYPE_1__ block_t ;
struct TYPE_6__ {scalar_t__ i_depth; scalar_t__ i_size; TYPE_1__* p_first; TYPE_1__** pp_last; int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ block_fifo_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vlc_mutex_assert (int /*<<< orphan*/ *) ; 

block_t *vlc_fifo_DequeueUnlocked(block_fifo_t *fifo)
{
    vlc_mutex_assert(&fifo->lock);

    block_t *block = fifo->p_first;

    if (block == NULL)
        return NULL; /* Nothing to do */

    fifo->p_first = block->p_next;
    if (block->p_next == NULL)
        fifo->pp_last = &fifo->p_first;
    block->p_next = NULL;

    assert(fifo->i_depth > 0);
    fifo->i_depth--;
    assert(fifo->i_size >= block->i_buffer);
    fifo->i_size -= block->i_buffer;

    return block;
}