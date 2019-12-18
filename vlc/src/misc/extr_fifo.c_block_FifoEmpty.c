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
typedef  int /*<<< orphan*/  block_t ;
typedef  int /*<<< orphan*/  block_fifo_t ;

/* Variables and functions */
 int /*<<< orphan*/  block_ChainRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_fifo_DequeueAllUnlocked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_fifo_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_fifo_Unlock (int /*<<< orphan*/ *) ; 

void block_FifoEmpty(block_fifo_t *fifo)
{
    block_t *block;

    vlc_fifo_Lock(fifo);
    block = vlc_fifo_DequeueAllUnlocked(fifo);
    vlc_fifo_Unlock(fifo);
    block_ChainRelease(block);
}