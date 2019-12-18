#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int tp_flags; scalar_t__ tp_current; scalar_t__ tp_minimum; scalar_t__ tp_linger; int /*<<< orphan*/  tp_mutex; TYPE_3__* tp_active; int /*<<< orphan*/  tp_njobs; TYPE_2__* tp_tail; TYPE_2__* tp_head; int /*<<< orphan*/  tp_workcv; int /*<<< orphan*/  tp_idle; } ;
typedef  TYPE_1__ tpool_t ;
struct TYPE_8__ {void (* tpj_func ) (void*) ;struct TYPE_8__* tpj_next; void* tpj_arg; } ;
typedef  TYPE_2__ tpool_job_t ;
struct TYPE_9__ {struct TYPE_9__* tpa_next; int /*<<< orphan*/  tpa_tid; } ;
typedef  TYPE_3__ tpool_active_t ;
struct timespec {int /*<<< orphan*/  tv_sec; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  PTHREAD_CANCEL_DEFERRED ; 
 int /*<<< orphan*/  PTHREAD_CANCEL_ENABLE ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int TP_ABANDON ; 
 int TP_DESTROY ; 
 int TP_SUSPEND ; 
 int TP_WAIT ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  job_cleanup ; 
 int /*<<< orphan*/  notify_waiters (TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_cleanup_pop (int) ; 
 int /*<<< orphan*/  pthread_cleanup_push (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec*) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int /*<<< orphan*/  pthread_setcancelstate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_setcanceltype (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_sigmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  worker_cleanup ; 

__attribute__((used)) static void *
tpool_worker(void *arg)
{
	tpool_t *tpool = (tpool_t *)arg;
	int elapsed;
	tpool_job_t *job;
	void (*func)(void *);
	tpool_active_t active;

	pthread_mutex_lock(&tpool->tp_mutex);
	pthread_cleanup_push(worker_cleanup, tpool);

	/*
	 * This is the worker's main loop.
	 * It will only be left if a timeout or an error has occurred.
	 */
	active.tpa_tid = pthread_self();
	for (;;) {
		elapsed = 0;
		tpool->tp_idle++;
		if (tpool->tp_flags & TP_WAIT)
			notify_waiters(tpool);
		while ((tpool->tp_head == NULL ||
		    (tpool->tp_flags & TP_SUSPEND)) &&
		    !(tpool->tp_flags & (TP_DESTROY | TP_ABANDON))) {
			if (tpool->tp_current <= tpool->tp_minimum ||
			    tpool->tp_linger == 0) {
				(void) pthread_cond_wait(&tpool->tp_workcv,
				    &tpool->tp_mutex);
			} else {
				struct timespec ts;

				clock_gettime(CLOCK_REALTIME, &ts);
				ts.tv_sec += tpool->tp_linger;

				if (pthread_cond_timedwait(&tpool->tp_workcv,
				    &tpool->tp_mutex, &ts) != 0) {
					elapsed = 1;
					break;
				}
			}
		}
		tpool->tp_idle--;
		if (tpool->tp_flags & TP_DESTROY)
			break;
		if (tpool->tp_flags & TP_ABANDON) {
			/* can't abandon a suspended pool */
			if (tpool->tp_flags & TP_SUSPEND) {
				tpool->tp_flags &= ~TP_SUSPEND;
				(void) pthread_cond_broadcast(
				    &tpool->tp_workcv);
			}
			if (tpool->tp_head == NULL)
				break;
		}
		if ((job = tpool->tp_head) != NULL &&
		    !(tpool->tp_flags & TP_SUSPEND)) {
			elapsed = 0;
			func = job->tpj_func;
			arg = job->tpj_arg;
			tpool->tp_head = job->tpj_next;
			if (job == tpool->tp_tail)
				tpool->tp_tail = NULL;
			tpool->tp_njobs--;
			active.tpa_next = tpool->tp_active;
			tpool->tp_active = &active;
			pthread_mutex_unlock(&tpool->tp_mutex);
			pthread_cleanup_push(job_cleanup, tpool);
			free(job);

			sigset_t maskset;
			(void) pthread_sigmask(SIG_SETMASK, NULL, &maskset);

			/*
			 * Call the specified function.
			 */
			func(arg);
			/*
			 * We don't know what this thread has been doing,
			 * so we reset its signal mask and cancellation
			 * state back to the values prior to calling func().
			 */
			(void) pthread_sigmask(SIG_SETMASK, &maskset, NULL);
			(void) pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,
			    NULL);
			(void) pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,
			    NULL);
			pthread_cleanup_pop(1);
		}
		if (elapsed && tpool->tp_current > tpool->tp_minimum) {
			/*
			 * We timed out and there is no work to be done
			 * and the number of workers exceeds the minimum.
			 * Exit now to reduce the size of the pool.
			 */
			break;
		}
	}
	pthread_cleanup_pop(1);
	return (arg);
}