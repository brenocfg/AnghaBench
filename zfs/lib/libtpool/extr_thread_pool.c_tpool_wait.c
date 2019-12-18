#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int tp_flags; int /*<<< orphan*/  tp_mutex; int /*<<< orphan*/  tp_waitcv; int /*<<< orphan*/ * tp_active; int /*<<< orphan*/ * tp_head; } ;
typedef  TYPE_1__ tpool_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int TP_ABANDON ; 
 int TP_DESTROY ; 
 int TP_WAIT ; 
 int /*<<< orphan*/  pthread_cleanup_pop (int) ; 
 int /*<<< orphan*/  pthread_cleanup_push (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tpool_cleanup ; 
 int /*<<< orphan*/  tpool_member (TYPE_1__*) ; 

void
tpool_wait(tpool_t *tpool)
{
	ASSERT(!tpool_member(tpool));
	ASSERT(!(tpool->tp_flags & (TP_DESTROY | TP_ABANDON)));

	pthread_mutex_lock(&tpool->tp_mutex);
	pthread_cleanup_push(tpool_cleanup, tpool);
	while (tpool->tp_head != NULL || tpool->tp_active != NULL) {
		tpool->tp_flags |= TP_WAIT;
		(void) pthread_cond_wait(&tpool->tp_waitcv, &tpool->tp_mutex);
		ASSERT(!(tpool->tp_flags & (TP_DESTROY | TP_ABANDON)));
	}
	pthread_cleanup_pop(1);	/* pthread_mutex_unlock(&tpool->tp_mutex); */
}