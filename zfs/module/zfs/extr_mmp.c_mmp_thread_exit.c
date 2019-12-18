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
struct TYPE_3__ {int /*<<< orphan*/  mmp_thread_cv; } ;
typedef  TYPE_1__ mmp_thread_t ;
typedef  int /*<<< orphan*/  kthread_t ;
typedef  int /*<<< orphan*/  callb_cpr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CALLB_CPR_EXIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_exit () ; 

__attribute__((used)) static void
mmp_thread_exit(mmp_thread_t *mmp, kthread_t **mpp, callb_cpr_t *cpr)
{
	ASSERT(*mpp != NULL);
	*mpp = NULL;
	cv_broadcast(&mmp->mmp_thread_cv);
	CALLB_CPR_EXIT(cpr);		/* drops &mmp->mmp_thread_lock */
	thread_exit();
}