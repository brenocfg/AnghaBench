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
struct TYPE_3__ {int /*<<< orphan*/  eof; int /*<<< orphan*/ * fifo; } ;
typedef  TYPE_1__ vlc_stream_fifo_t ;
typedef  int /*<<< orphan*/  vlc_fifo_t ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/  EPIPE ; 
 int /*<<< orphan*/  block_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_fifo_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_fifo_QueueUnlocked (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_fifo_Unlock (int /*<<< orphan*/ *) ; 

int vlc_stream_fifo_Queue(vlc_stream_fifo_t *writer, block_t *block)
{
    vlc_fifo_t *fifo = writer->fifo;

    vlc_fifo_Lock(fifo);
    if (likely(!writer->eof))
    {
        vlc_fifo_QueueUnlocked(fifo, block);
        block = NULL;
    }
    vlc_fifo_Unlock(fifo);

    if (unlikely(block != NULL))
    {
        block_Release(block);
        errno = EPIPE;
        return -1;
    }
    return 0;
}