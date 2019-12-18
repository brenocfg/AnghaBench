#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* p_tail; int /*<<< orphan*/ * p_head; } ;
typedef  TYPE_2__ queue_t ;
struct TYPE_5__ {int /*<<< orphan*/ * p_next; } ;

/* Variables and functions */
 int VLC_SUCCESS ; 

int QueueTransfer( queue_t *p_sink, queue_t *p_source )
{
    if( p_source->p_head == NULL ) {
        return VLC_SUCCESS;
    }

    if( p_sink->p_head == NULL ) {
        p_sink->p_head = p_source->p_head;
        p_sink->p_tail = p_source->p_tail;
    } else {
        p_sink->p_tail->p_next = p_source->p_head;
        p_sink->p_tail = p_source->p_tail;
    }
    p_source->p_head = p_source->p_tail = NULL;

    return VLC_SUCCESS;
}