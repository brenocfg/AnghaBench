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
 int /*<<< orphan*/  vlc_cleanup_pop () ; 
 int /*<<< orphan*/  vlc_fifo_CleanupPush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_fifo_DequeueUnlocked (int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_fifo_IsEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_fifo_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_fifo_Unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_fifo_Wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_testcancel () ; 

block_t *block_FifoGet(block_fifo_t *fifo)
{
    block_t *block;

    vlc_testcancel();

    vlc_fifo_Lock(fifo);
    while (vlc_fifo_IsEmpty(fifo))
    {
        vlc_fifo_CleanupPush(fifo);
        vlc_fifo_Wait(fifo);
        vlc_cleanup_pop();
    }
    block = vlc_fifo_DequeueUnlocked(fifo);
    vlc_fifo_Unlock(fifo);

    return block;
}