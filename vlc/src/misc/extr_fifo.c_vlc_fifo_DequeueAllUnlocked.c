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
typedef  int /*<<< orphan*/  block_t ;
struct TYPE_3__ {scalar_t__ i_size; scalar_t__ i_depth; int /*<<< orphan*/ * p_first; int /*<<< orphan*/ ** pp_last; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ block_fifo_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_mutex_assert (int /*<<< orphan*/ *) ; 

block_t *vlc_fifo_DequeueAllUnlocked(block_fifo_t *fifo)
{
    vlc_mutex_assert(&fifo->lock);

    block_t *block = fifo->p_first;

    fifo->p_first = NULL;
    fifo->pp_last = &fifo->p_first;
    fifo->i_depth = 0;
    fifo->i_size = 0;

    return block;
}