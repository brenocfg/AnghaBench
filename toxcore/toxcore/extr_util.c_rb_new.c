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
struct TYPE_4__ {int size; void* data; } ;
typedef  TYPE_1__ RingBuffer ;

/* Variables and functions */
 void* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

RingBuffer *rb_new(int size)
{
    RingBuffer *buf = calloc(sizeof(RingBuffer), 1);

    if (!buf) return NULL;

    buf->size = size + 1; /* include empty elem */

    if (!(buf->data = calloc(buf->size, sizeof(void *)))) {
        free(buf);
        return NULL;
    }

    return buf;
}