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
struct TYPE_5__ {TYPE_2__* p_head; TYPE_2__* p_tail; } ;
typedef  TYPE_1__ queue_t ;
struct TYPE_6__ {struct TYPE_6__* p_next; } ;
typedef  TYPE_2__ command_t ;

/* Variables and functions */

command_t *QueueDequeue( queue_t *p_queue )
{
    if( p_queue->p_head == NULL )
    {
        return NULL;
    }
    else
    {
        command_t *p_ret = p_queue->p_head;
        if( p_queue->p_head == p_queue->p_tail )
        {
            p_queue->p_head = p_queue->p_tail = NULL;
        }
        else
        {
            p_queue->p_head = p_queue->p_head->p_next;
        }
        return p_ret;
    }
}