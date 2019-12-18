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
typedef  int /*<<< orphan*/  taskqid_t ;
struct TYPE_4__ {int /*<<< orphan*/  tq_lock; int /*<<< orphan*/  tq_lock_class; } ;
typedef  TYPE_1__ taskq_t ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave_nested (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * taskq_find (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
taskq_wait_id_check(taskq_t *tq, taskqid_t id)
{
	int rc;
	unsigned long flags;

	spin_lock_irqsave_nested(&tq->tq_lock, flags, tq->tq_lock_class);
	rc = (taskq_find(tq, id) == NULL);
	spin_unlock_irqrestore(&tq->tq_lock, flags);

	return (rc);
}