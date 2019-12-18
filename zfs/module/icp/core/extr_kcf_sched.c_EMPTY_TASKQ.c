#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* tqent_next; } ;
struct TYPE_5__ {scalar_t__ tq_lowest_id; scalar_t__ tq_next_id; scalar_t__ tq_active; TYPE_1__ tq_task; } ;
typedef  TYPE_2__ taskq_t ;

/* Variables and functions */

__attribute__((used)) static inline int EMPTY_TASKQ(taskq_t *tq)
{
#ifdef _KERNEL
	return (tq->tq_lowest_id == tq->tq_next_id);
#else
	return (tq->tq_task.tqent_next == &tq->tq_task || tq->tq_active == 0);
#endif
}