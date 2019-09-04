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
struct memory_buffer {scalar_t__ size; scalar_t__ pos; void* buffer; } ;
typedef  scalar_t__ INT ;

/* Variables and functions */

__attribute__((used)) static inline const void *buffer_read(struct memory_buffer *mbuf, INT size)
{
    if (mbuf->size - mbuf->pos >= size)
    {
        const void *data = mbuf->buffer + mbuf->pos;
        mbuf->pos += size;
        return data;
    }
    return NULL;
}