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
struct TYPE_3__ {int /*<<< orphan*/ * tqent_taskq; scalar_t__ tqent_flags; int /*<<< orphan*/ * tqent_arg; int /*<<< orphan*/ * tqent_func; scalar_t__ tqent_id; int /*<<< orphan*/  tqent_list; int /*<<< orphan*/  tqent_timer; int /*<<< orphan*/  tqent_waitq; int /*<<< orphan*/  tqent_lock; } ;
typedef  TYPE_1__ taskq_ent_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
taskq_init_ent(taskq_ent_t *t)
{
	spin_lock_init(&t->tqent_lock);
	init_waitqueue_head(&t->tqent_waitq);
	timer_setup(&t->tqent_timer, NULL, 0);
	INIT_LIST_HEAD(&t->tqent_list);
	t->tqent_id = 0;
	t->tqent_func = NULL;
	t->tqent_arg = NULL;
	t->tqent_flags = 0;
	t->tqent_taskq = NULL;
}