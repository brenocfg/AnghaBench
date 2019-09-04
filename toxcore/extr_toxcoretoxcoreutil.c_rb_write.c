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
struct TYPE_3__ {int end; int size; int start; void** data; } ;
typedef  TYPE_1__ RingBuffer ;

/* Variables and functions */

void *rb_write(RingBuffer *b, void *p)
{
    void *rc = NULL;

    if ((b->end + 1) % b->size == b->start) /* full */
        rc = b->data[b->start];

    b->data[b->end] = p;
    b->end = (b->end + 1) % b->size;

    if (b->end == b->start)
        b->start = (b->start + 1) % b->size;

    return rc;
}