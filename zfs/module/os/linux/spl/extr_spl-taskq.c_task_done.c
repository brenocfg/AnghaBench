#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ tq_nalloc; scalar_t__ tq_minalloc; int /*<<< orphan*/  tq_free_list; int /*<<< orphan*/  tqent_list; scalar_t__ tqent_flags; int /*<<< orphan*/ * tqent_arg; int /*<<< orphan*/ * tqent_func; int /*<<< orphan*/  tqent_id; int /*<<< orphan*/  tqent_waitq; } ;
typedef  TYPE_1__ taskq_t ;
typedef  TYPE_1__ taskq_ent_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_1__*) ; 
 int /*<<< orphan*/  TASKQID_INVALID ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_free (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
task_done(taskq_t *tq, taskq_ent_t *t)
{
	ASSERT(tq);
	ASSERT(t);

	/* Wake tasks blocked in taskq_wait_id() */
	wake_up_all(&t->tqent_waitq);

	list_del_init(&t->tqent_list);

	if (tq->tq_nalloc <= tq->tq_minalloc) {
		t->tqent_id = TASKQID_INVALID;
		t->tqent_func = NULL;
		t->tqent_arg = NULL;
		t->tqent_flags = 0;

		list_add_tail(&t->tqent_list, &tq->tq_free_list);
	} else {
		task_free(tq, t);
	}
}