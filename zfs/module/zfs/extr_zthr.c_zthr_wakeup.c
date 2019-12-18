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
struct TYPE_3__ {int /*<<< orphan*/  zthr_state_lock; int /*<<< orphan*/  zthr_cv; } ;
typedef  TYPE_1__ zthr_t ;

/* Variables and functions */
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void
zthr_wakeup(zthr_t *t)
{
	mutex_enter(&t->zthr_state_lock);

	/*
	 * There are 5 states that we can find the zthr when issuing
	 * this broadcast:
	 *
	 * [1] The common case of the thread being asleep, at which
	 *     point the broadcast will wake it up.
	 * [2] The thread has been cancelled. Waking up a cancelled
	 *     thread is a no-op. Any work that is still left to be
	 *     done should be handled the next time the thread is
	 *     resumed.
	 * [3] The thread is doing work and is already up, so this
	 *     is basically a no-op.
	 * [4] The thread was just created/resumed, in which case the
	 *     behavior is similar to [3].
	 * [5] The thread is in the middle of being cancelled, which
	 *     will be a no-op.
	 */
	cv_broadcast(&t->zthr_cv);

	mutex_exit(&t->zthr_state_lock);
}