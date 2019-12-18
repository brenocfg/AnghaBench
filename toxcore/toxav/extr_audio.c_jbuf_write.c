#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_2__ {int sequnum; } ;
struct RTPMessage {TYPE_1__ header; } ;
struct JitterBuffer {int size; int bottom; int capacity; int top; struct RTPMessage** queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOGGER_DEBUG (char*,struct JitterBuffer*) ; 
 int /*<<< orphan*/  jbuf_clear (struct JitterBuffer*) ; 

__attribute__((used)) static int jbuf_write(struct JitterBuffer *q, struct RTPMessage *m)
{
    uint16_t sequnum = m->header.sequnum;

    unsigned int num = sequnum % q->size;

    if ((uint32_t)(sequnum - q->bottom) > q->size) {
        LOGGER_DEBUG("Clearing filled jitter buffer: %p", q);

        jbuf_clear(q);
        q->bottom = sequnum - q->capacity;
        q->queue[num] = m;
        q->top = sequnum + 1;
        return 0;
    }

    if (q->queue[num])
        return -1;

    q->queue[num] = m;

    if ((sequnum - q->bottom) >= (q->top - q->bottom))
        q->top = sequnum + 1;

    return 0;
}