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
struct TYPE_5__ {int /*<<< orphan*/  i_depth; TYPE_2__** pp_last; } ;
typedef  TYPE_1__ fifo_t ;
struct TYPE_6__ {struct TYPE_6__* p_next; } ;
typedef  TYPE_2__ fifo_item_t ;

/* Variables and functions */

__attribute__((used)) static inline void fifo_Put(fifo_t *fifo, fifo_item_t *p_item)
{
    *(fifo->pp_last) = p_item;

    while (p_item != NULL)
    {
        fifo->pp_last = &p_item->p_next;
        fifo->i_depth++;

        p_item = p_item->p_next;
    }
}