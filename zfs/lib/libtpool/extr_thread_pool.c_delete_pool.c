#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ tp_current; int /*<<< orphan*/  tp_attr; struct TYPE_8__* tpj_next; struct TYPE_8__* tp_head; TYPE_1__* tp_back; struct TYPE_8__* tp_forw; int /*<<< orphan*/ * tp_active; } ;
typedef  TYPE_2__ tpool_t ;
typedef  TYPE_2__ tpool_job_t ;
struct TYPE_7__ {TYPE_2__* tp_forw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  pthread_attr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_pool_lock ; 
 TYPE_2__* thread_pools ; 

__attribute__((used)) static void
delete_pool(tpool_t *tpool)
{
	tpool_job_t *job;

	ASSERT(tpool->tp_current == 0 && tpool->tp_active == NULL);

	/*
	 * Unlink the pool from the global list of all pools.
	 */
	(void) pthread_mutex_lock(&thread_pool_lock);
	if (thread_pools == tpool)
		thread_pools = tpool->tp_forw;
	if (thread_pools == tpool)
		thread_pools = NULL;
	else {
		tpool->tp_back->tp_forw = tpool->tp_forw;
		tpool->tp_forw->tp_back = tpool->tp_back;
	}
	pthread_mutex_unlock(&thread_pool_lock);

	/*
	 * There should be no pending jobs, but just in case...
	 */
	for (job = tpool->tp_head; job != NULL; job = tpool->tp_head) {
		tpool->tp_head = job->tpj_next;
		free(job);
	}
	(void) pthread_attr_destroy(&tpool->tp_attr);
	free(tpool);
}