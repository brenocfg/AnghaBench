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
struct TYPE_3__ {int /*<<< orphan*/  zthr_state_lock; scalar_t__ zthr_haswaiters; int /*<<< orphan*/  zthr_wait_cv; int /*<<< orphan*/ * zthr_thread; int /*<<< orphan*/  zthr_cv; } ;
typedef  TYPE_1__ zthr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void
zthr_wait_cycle_done(zthr_t *t)
{
	mutex_enter(&t->zthr_state_lock);

	/*
	 * Since we are holding the zthr_state_lock at this point
	 * we can find the state in one of the following 5 states:
	 *
	 * [1] The thread has already cancelled, therefore
	 *     there is nothing for us to do.
	 * [2] The thread is sleeping so we set the flag, broadcast
	 *     the CV and wait for it to exit.
	 * [3] The thread is doing work, in which case we just set
	 *     the flag and wait for it to finish.
	 * [4] The thread was just created/resumed, in which case
	 *     the behavior is similar to [3].
	 * [5] The thread is the middle of being cancelled, which is
	 *     similar to [3]. We'll wait for the cancel, which is
	 *     waiting for the zthr func.
	 *
	 * Since requests are serialized, by the time that we get
	 * control back we expect that the zthr has completed it's
	 * zthr_func.
	 */
	if (t->zthr_thread != NULL) {
		t->zthr_haswaiters = B_TRUE;

		/* broadcast in case the zthr is sleeping */
		cv_broadcast(&t->zthr_cv);

		while ((t->zthr_haswaiters) && (t->zthr_thread != NULL))
			cv_wait(&t->zthr_wait_cv, &t->zthr_state_lock);

		ASSERT(!t->zthr_haswaiters);
	}

	mutex_exit(&t->zthr_state_lock);
}