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
typedef  int uint_t ;
typedef  int /*<<< orphan*/  taskq_thread_t ;
struct TYPE_8__ {int tq_nthreads; int tq_maxthreads; int tq_minalloc; int tq_maxalloc; int tq_flags; int /*<<< orphan*/  tq_taskqs; scalar_t__ tq_instance; scalar_t__ tq_nspawn; int /*<<< orphan*/  tq_wait_waitq; int /*<<< orphan*/  tq_lock; int /*<<< orphan*/  tq_lock_class; int /*<<< orphan*/  tq_work_waitq; int /*<<< orphan*/  tq_delay_list; int /*<<< orphan*/  tq_prio_list; int /*<<< orphan*/  tq_pend_list; int /*<<< orphan*/  tq_free_list; void* tq_lowest_id; void* tq_next_id; scalar_t__ tq_nalloc; int /*<<< orphan*/  tq_pri; scalar_t__ tq_nactive; int /*<<< orphan*/  tq_name; int /*<<< orphan*/  tq_active_list; int /*<<< orphan*/  tq_thread_list; } ;
typedef  TYPE_1__ taskq_t ;
typedef  int /*<<< orphan*/  pri_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int INT_MAX ; 
 int /*<<< orphan*/  KM_PUSHPAGE ; 
 int MAX (int,int) ; 
 int MIN (int,int) ; 
 void* TASKQID_INITIAL ; 
 int TASKQ_ACTIVE ; 
 int TASKQ_CPR_SAFE ; 
 int TASKQ_DYNAMIC ; 
 int TASKQ_PREPOPULATE ; 
 int TASKQ_THREADS_CPU_PCT ; 
 int /*<<< orphan*/  TQ_LOCK_GENERAL ; 
 int TQ_NEW ; 
 int TQ_PUSHPAGE ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 TYPE_1__* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_strdup (char const*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int num_online_cpus () ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave_nested (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ spl_taskq_thread_dynamic ; 
 int /*<<< orphan*/  task_alloc (TYPE_1__*,int,unsigned long*) ; 
 int /*<<< orphan*/  task_done (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskq_destroy (TYPE_1__*) ; 
 scalar_t__ taskq_find_by_name (char const*) ; 
 int /*<<< orphan*/ * taskq_thread_create (TYPE_1__*) ; 
 int /*<<< orphan*/  tq_list ; 
 int /*<<< orphan*/  tq_list_sem ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

taskq_t *
taskq_create(const char *name, int nthreads, pri_t pri,
    int minalloc, int maxalloc, uint_t flags)
{
	taskq_t *tq;
	taskq_thread_t *tqt;
	int count = 0, rc = 0, i;
	unsigned long irqflags;

	ASSERT(name != NULL);
	ASSERT(minalloc >= 0);
	ASSERT(maxalloc <= INT_MAX);
	ASSERT(!(flags & (TASKQ_CPR_SAFE))); /* Unsupported */

	/* Scale the number of threads using nthreads as a percentage */
	if (flags & TASKQ_THREADS_CPU_PCT) {
		ASSERT(nthreads <= 100);
		ASSERT(nthreads >= 0);
		nthreads = MIN(nthreads, 100);
		nthreads = MAX(nthreads, 0);
		nthreads = MAX((num_online_cpus() * nthreads) / 100, 1);
	}

	tq = kmem_alloc(sizeof (*tq), KM_PUSHPAGE);
	if (tq == NULL)
		return (NULL);

	spin_lock_init(&tq->tq_lock);
	INIT_LIST_HEAD(&tq->tq_thread_list);
	INIT_LIST_HEAD(&tq->tq_active_list);
	tq->tq_name = kmem_strdup(name);
	tq->tq_nactive = 0;
	tq->tq_nthreads = 0;
	tq->tq_nspawn = 0;
	tq->tq_maxthreads = nthreads;
	tq->tq_pri = pri;
	tq->tq_minalloc = minalloc;
	tq->tq_maxalloc = maxalloc;
	tq->tq_nalloc = 0;
	tq->tq_flags = (flags | TASKQ_ACTIVE);
	tq->tq_next_id = TASKQID_INITIAL;
	tq->tq_lowest_id = TASKQID_INITIAL;
	INIT_LIST_HEAD(&tq->tq_free_list);
	INIT_LIST_HEAD(&tq->tq_pend_list);
	INIT_LIST_HEAD(&tq->tq_prio_list);
	INIT_LIST_HEAD(&tq->tq_delay_list);
	init_waitqueue_head(&tq->tq_work_waitq);
	init_waitqueue_head(&tq->tq_wait_waitq);
	tq->tq_lock_class = TQ_LOCK_GENERAL;
	INIT_LIST_HEAD(&tq->tq_taskqs);

	if (flags & TASKQ_PREPOPULATE) {
		spin_lock_irqsave_nested(&tq->tq_lock, irqflags,
		    tq->tq_lock_class);

		for (i = 0; i < minalloc; i++)
			task_done(tq, task_alloc(tq, TQ_PUSHPAGE | TQ_NEW,
			    &irqflags));

		spin_unlock_irqrestore(&tq->tq_lock, irqflags);
	}

	if ((flags & TASKQ_DYNAMIC) && spl_taskq_thread_dynamic)
		nthreads = 1;

	for (i = 0; i < nthreads; i++) {
		tqt = taskq_thread_create(tq);
		if (tqt == NULL)
			rc = 1;
		else
			count++;
	}

	/* Wait for all threads to be started before potential destroy */
	wait_event(tq->tq_wait_waitq, tq->tq_nthreads == count);
	/*
	 * taskq_thread might have touched nspawn, but we don't want them to
	 * because they're not dynamically spawned. So we reset it to 0
	 */
	tq->tq_nspawn = 0;

	if (rc) {
		taskq_destroy(tq);
		tq = NULL;
	} else {
		down_write(&tq_list_sem);
		tq->tq_instance = taskq_find_by_name(name) + 1;
		list_add_tail(&tq->tq_taskqs, &tq_list);
		up_write(&tq_list_sem);
	}

	return (tq);
}