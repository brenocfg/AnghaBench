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
struct TYPE_3__ {int /*<<< orphan*/  zthr_request_lock; int /*<<< orphan*/  zthr_state_lock; int /*<<< orphan*/  zthr_cancel; int /*<<< orphan*/  zthr_cv; int /*<<< orphan*/ * zthr_thread; } ;
typedef  TYPE_1__ zthr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void
zthr_cancel(zthr_t *t)
{
	mutex_enter(&t->zthr_request_lock);
	mutex_enter(&t->zthr_state_lock);

	/*
	 * Since we are holding the zthr_state_lock at this point
	 * we can find the state in one of the following 4 states:
	 *
	 * [1] The thread has already been cancelled, therefore
	 *     there is nothing for us to do.
	 * [2] The thread is sleeping so we set the flag, broadcast
	 *     the CV and wait for it to exit.
	 * [3] The thread is doing work, in which case we just set
	 *     the flag and wait for it to finish.
	 * [4] The thread was just created/resumed, in which case
	 *     the behavior is similar to [3].
	 *
	 * Since requests are serialized, by the time that we get
	 * control back we expect that the zthr is cancelled and
	 * not running anymore.
	 */
	if (t->zthr_thread != NULL) {
		t->zthr_cancel = B_TRUE;

		/* broadcast in case the zthr is sleeping */
		cv_broadcast(&t->zthr_cv);

		while (t->zthr_thread != NULL)
			cv_wait(&t->zthr_cv, &t->zthr_state_lock);

		ASSERT(!t->zthr_cancel);
	}

	mutex_exit(&t->zthr_state_lock);
	mutex_exit(&t->zthr_request_lock);
}