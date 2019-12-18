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
struct TYPE_5__ {scalar_t__ tq_active; int /*<<< orphan*/  tq_lock; int /*<<< orphan*/  tq_wait_cv; TYPE_1__ tq_task; } ;
typedef  TYPE_2__ taskq_t ;

/* Variables and functions */
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void
taskq_wait(taskq_t *tq)
{
	mutex_enter(&tq->tq_lock);
	while (tq->tq_task.tqent_next != &tq->tq_task || tq->tq_active != 0)
		cv_wait(&tq->tq_wait_cv, &tq->tq_lock);
	mutex_exit(&tq->tq_lock);
}