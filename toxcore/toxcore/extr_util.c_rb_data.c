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
typedef  size_t uint16_t ;
struct TYPE_4__ {size_t start; size_t size; void** data; } ;
typedef  TYPE_1__ RingBuffer ;

/* Variables and functions */
 size_t rb_size (TYPE_1__ const*) ; 

uint16_t rb_data(const RingBuffer *b, void **dest)
{
    uint16_t i = 0;

    for (; i < rb_size(b); i++)
        dest[i] = b->data[(b->start + i) % b->size];

    return i;
}