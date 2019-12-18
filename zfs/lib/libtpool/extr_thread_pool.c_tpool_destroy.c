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
struct TYPE_7__ {int tp_flags; scalar_t__ tp_current; int /*<<< orphan*/  tp_mutex; int /*<<< orphan*/  tp_busycv; int /*<<< orphan*/  tp_waitcv; TYPE_2__* tp_active; int /*<<< orphan*/  tp_workcv; } ;
typedef  TYPE_1__ tpool_t ;
struct TYPE_8__ {int /*<<< orphan*/  tpa_tid; struct TYPE_8__* tpa_next; } ;
typedef  TYPE_2__ tpool_active_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int TP_ABANDON ; 
 int TP_DESTROY ; 
 int TP_SUSPEND ; 
 int TP_WAIT ; 
 int /*<<< orphan*/  delete_pool (TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cleanup_pop (int) ; 
 int /*<<< orphan*/  pthread_cleanup_push (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tpool_cleanup ; 
 int /*<<< orphan*/  tpool_member (TYPE_1__*) ; 

void
tpool_destroy(tpool_t *tpool)
{
	tpool_active_t *activep;

	ASSERT(!tpool_member(tpool));
	ASSERT(!(tpool->tp_flags & (TP_DESTROY | TP_ABANDON)));

	pthread_mutex_lock(&tpool->tp_mutex);
	pthread_cleanup_push(tpool_cleanup, tpool);

	/* mark the pool as being destroyed; wakeup idle workers */
	tpool->tp_flags |= TP_DESTROY;
	tpool->tp_flags &= ~TP_SUSPEND;
	(void) pthread_cond_broadcast(&tpool->tp_workcv);

	/* cancel all active workers */
	for (activep = tpool->tp_active; activep; activep = activep->tpa_next)
		(void) pthread_cancel(activep->tpa_tid);

	/* wait for all active workers to finish */
	while (tpool->tp_active != NULL) {
		tpool->tp_flags |= TP_WAIT;
		(void) pthread_cond_wait(&tpool->tp_waitcv, &tpool->tp_mutex);
	}

	/* the last worker to terminate will wake us up */
	while (tpool->tp_current != 0)
		(void) pthread_cond_wait(&tpool->tp_busycv, &tpool->tp_mutex);

	pthread_cleanup_pop(1);	/* pthread_mutex_unlock(&tpool->tp_mutex); */
	delete_pool(tpool);
}