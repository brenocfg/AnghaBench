#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * tqt_thread; int /*<<< orphan*/  tqt_id; TYPE_2__* tqt_tq; int /*<<< orphan*/  tqt_active_list; int /*<<< orphan*/  tqt_thread_list; } ;
typedef  TYPE_1__ taskq_thread_t ;
struct TYPE_9__ {int /*<<< orphan*/  tq_pri; int /*<<< orphan*/  tq_name; } ;
typedef  TYPE_2__ taskq_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KM_PUSHPAGE ; 
 int /*<<< orphan*/  PRIO_TO_NICE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASKQID_INVALID ; 
 TYPE_1__* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  kthread_bind (int /*<<< orphan*/ *,int) ; 
 int num_online_cpus () ; 
 int /*<<< orphan*/  set_user_nice (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * spl_kthread_create (int /*<<< orphan*/ ,TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ spl_taskq_thread_bind ; 
 scalar_t__ spl_taskq_thread_priority ; 
 int /*<<< orphan*/  taskq_thread ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ *) ; 

__attribute__((used)) static taskq_thread_t *
taskq_thread_create(taskq_t *tq)
{
	static int last_used_cpu = 0;
	taskq_thread_t *tqt;

	tqt = kmem_alloc(sizeof (*tqt), KM_PUSHPAGE);
	INIT_LIST_HEAD(&tqt->tqt_thread_list);
	INIT_LIST_HEAD(&tqt->tqt_active_list);
	tqt->tqt_tq = tq;
	tqt->tqt_id = TASKQID_INVALID;

	tqt->tqt_thread = spl_kthread_create(taskq_thread, tqt,
	    "%s", tq->tq_name);
	if (tqt->tqt_thread == NULL) {
		kmem_free(tqt, sizeof (taskq_thread_t));
		return (NULL);
	}

	if (spl_taskq_thread_bind) {
		last_used_cpu = (last_used_cpu + 1) % num_online_cpus();
		kthread_bind(tqt->tqt_thread, last_used_cpu);
	}

	if (spl_taskq_thread_priority)
		set_user_nice(tqt->tqt_thread, PRIO_TO_NICE(tq->tq_pri));

	wake_up_process(tqt->tqt_thread);

	return (tqt);
}