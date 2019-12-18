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
typedef  int /*<<< orphan*/  vlc_stream_fifo_t ;
typedef  int ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 TYPE_1__* block_Alloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,size_t) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_stream_fifo_Queue (int /*<<< orphan*/ *,TYPE_1__*) ; 

ssize_t vlc_stream_fifo_Write(vlc_stream_fifo_t *writer,
                              const void *buf, size_t len)
{
    block_t *block = block_Alloc(len);
    if (unlikely(block == NULL))
        return -1;

    memcpy(block->p_buffer, buf, len);
    return vlc_stream_fifo_Queue(writer, block) ? -1 : (ssize_t)len;
}