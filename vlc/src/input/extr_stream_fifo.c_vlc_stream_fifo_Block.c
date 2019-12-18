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
struct vlc_stream_fifo {scalar_t__ eof; int /*<<< orphan*/ * fifo; } ;
typedef  int /*<<< orphan*/  stream_t ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/ * vlc_fifo_DequeueUnlocked (int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_fifo_IsEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_fifo_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_fifo_Unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_fifo_Wait (int /*<<< orphan*/ *) ; 
 struct vlc_stream_fifo* vlc_stream_fifo_Writer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static block_t *vlc_stream_fifo_Block(stream_t *s, bool *restrict eof)
{
    struct vlc_stream_fifo *sys = vlc_stream_fifo_Writer(s);
    vlc_fifo_t *fifo = sys->fifo;
    block_t *block;

    vlc_fifo_Lock(fifo);
    while (vlc_fifo_IsEmpty(fifo))
    {
        if (sys->eof)
        {
            *eof = true;
            break;
        }
        vlc_fifo_Wait(fifo);
    }

    block = vlc_fifo_DequeueUnlocked(fifo);
    vlc_fifo_Unlock(fifo);
    return block;
}