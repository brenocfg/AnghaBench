#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int eof; int /*<<< orphan*/ * fifo; } ;
typedef  TYPE_1__ vlc_stream_fifo_t ;
typedef  int /*<<< orphan*/  vlc_fifo_t ;

/* Variables and functions */
 int /*<<< orphan*/  block_FifoRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_fifo_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_fifo_Signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_fifo_Unlock (int /*<<< orphan*/ *) ; 

void vlc_stream_fifo_Close(vlc_stream_fifo_t *writer)
{
    vlc_fifo_t *fifo = writer->fifo;
    bool closed;

    vlc_fifo_Lock(fifo);
    closed = writer->eof;
    writer->eof = true;
    vlc_fifo_Signal(fifo);
    vlc_fifo_Unlock(fifo);

    if (closed) {
        /* Destroy shared state if read end is already closed */
        block_FifoRelease(fifo);
        free(writer);
    }
}