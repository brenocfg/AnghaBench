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
typedef  int uint32_t ;
struct RTPMessage {int dummy; } ;
struct JitterBuffer {unsigned int size; int capacity; void* queue; } ;

/* Variables and functions */
 void* calloc (int,unsigned int) ; 
 int /*<<< orphan*/  free (struct JitterBuffer*) ; 

__attribute__((used)) static struct JitterBuffer *jbuf_new(uint32_t capacity)
{
    unsigned int size = 1;

    while (size <= (capacity * 4)) {
        size *= 2;
    }

    struct JitterBuffer *q;

    if (!(q = calloc(sizeof(struct JitterBuffer), 1))) return NULL;

    if (!(q->queue = calloc(sizeof(struct RTPMessage *), size))) {
        free(q);
        return NULL;
    }

    q->size = size;
    q->capacity = capacity;
    return q;
}