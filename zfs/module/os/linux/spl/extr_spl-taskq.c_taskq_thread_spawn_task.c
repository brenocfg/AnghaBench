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
struct TYPE_3__ {int /*<<< orphan*/  tq_lock; int /*<<< orphan*/  tq_nspawn; int /*<<< orphan*/  tq_lock_class; } ;
typedef  TYPE_1__ taskq_t ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave_nested (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * taskq_thread_create (TYPE_1__*) ; 

__attribute__((used)) static void
taskq_thread_spawn_task(void *arg)
{
	taskq_t *tq = (taskq_t *)arg;
	unsigned long flags;

	if (taskq_thread_create(tq) == NULL) {
		/* restore spawning count if failed */
		spin_lock_irqsave_nested(&tq->tq_lock, flags,
		    tq->tq_lock_class);
		tq->tq_nspawn--;
		spin_unlock_irqrestore(&tq->tq_lock, flags);
	}
}