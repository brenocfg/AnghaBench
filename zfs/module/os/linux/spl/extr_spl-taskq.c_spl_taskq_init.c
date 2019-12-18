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
struct TYPE_2__ {int /*<<< orphan*/  tq_lock_class; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 int MAX (int /*<<< orphan*/ ,int) ; 
 int TASKQ_DYNAMIC ; 
 int TASKQ_PREPOPULATE ; 
 int /*<<< orphan*/  TQ_LOCK_DYNAMIC ; 
 int /*<<< orphan*/  boot_ncpus ; 
 TYPE_1__* dynamic_taskq ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  maxclsyspri ; 
 int /*<<< orphan*/ * system_delay_taskq ; 
 int /*<<< orphan*/ * system_taskq ; 
 void* taskq_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  taskq_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskq_tsd ; 
 int /*<<< orphan*/  tq_list_sem ; 
 int /*<<< orphan*/  tsd_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
spl_taskq_init(void)
{
	init_rwsem(&tq_list_sem);
	tsd_create(&taskq_tsd, NULL);

	system_taskq = taskq_create("spl_system_taskq", MAX(boot_ncpus, 64),
	    maxclsyspri, boot_ncpus, INT_MAX, TASKQ_PREPOPULATE|TASKQ_DYNAMIC);
	if (system_taskq == NULL)
		return (1);

	system_delay_taskq = taskq_create("spl_delay_taskq", MAX(boot_ncpus, 4),
	    maxclsyspri, boot_ncpus, INT_MAX, TASKQ_PREPOPULATE|TASKQ_DYNAMIC);
	if (system_delay_taskq == NULL) {
		taskq_destroy(system_taskq);
		return (1);
	}

	dynamic_taskq = taskq_create("spl_dynamic_taskq", 1,
	    maxclsyspri, boot_ncpus, INT_MAX, TASKQ_PREPOPULATE);
	if (dynamic_taskq == NULL) {
		taskq_destroy(system_taskq);
		taskq_destroy(system_delay_taskq);
		return (1);
	}

	/*
	 * This is used to annotate tq_lock, so
	 *   taskq_dispatch -> taskq_thread_spawn -> taskq_dispatch
	 * does not trigger a lockdep warning re: possible recursive locking
	 */
	dynamic_taskq->tq_lock_class = TQ_LOCK_DYNAMIC;

	return (0);
}