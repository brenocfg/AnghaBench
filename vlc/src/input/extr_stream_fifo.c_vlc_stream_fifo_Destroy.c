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
typedef  int /*<<< orphan*/  vlc_fifo_t ;
struct vlc_stream_fifo {int eof; int /*<<< orphan*/ * fifo; } ;
typedef  int /*<<< orphan*/  stream_t ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/  block_ChainRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  block_FifoRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct vlc_stream_fifo*) ; 
 int /*<<< orphan*/ * vlc_fifo_DequeueAllUnlocked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_fifo_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_fifo_Unlock (int /*<<< orphan*/ *) ; 
 struct vlc_stream_fifo* vlc_stream_fifo_Writer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vlc_stream_fifo_Destroy(stream_t *s)
{
    struct vlc_stream_fifo *writer = vlc_stream_fifo_Writer(s);
    vlc_fifo_t *fifo = writer->fifo;
    block_t *block;
    bool closed;

    vlc_fifo_Lock(fifo);
    block = vlc_fifo_DequeueAllUnlocked(fifo);
    closed = writer->eof;
    writer->eof = true;
    vlc_fifo_Unlock(fifo);

    block_ChainRelease(block);

    if (closed) {
        /* Destroy shared state if write end is already closed */
        block_FifoRelease(fifo);
        free(writer);
    }
}