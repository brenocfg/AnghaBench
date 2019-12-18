#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int mmp_thread_exiting; int /*<<< orphan*/ * mmp_thread; int /*<<< orphan*/  mmp_thread_lock; int /*<<< orphan*/  mmp_thread_cv; } ;
struct TYPE_5__ {TYPE_2__ spa_mmp; } ;
typedef  TYPE_1__ spa_t ;
typedef  TYPE_2__ mmp_thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gethrtime () ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_name (TYPE_1__*) ; 
 int /*<<< orphan*/  zfs_dbgmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
mmp_thread_stop(spa_t *spa)
{
	mmp_thread_t *mmp = &spa->spa_mmp;

	mutex_enter(&mmp->mmp_thread_lock);
	mmp->mmp_thread_exiting = 1;
	cv_broadcast(&mmp->mmp_thread_cv);

	while (mmp->mmp_thread) {
		cv_wait(&mmp->mmp_thread_cv, &mmp->mmp_thread_lock);
	}
	mutex_exit(&mmp->mmp_thread_lock);
	zfs_dbgmsg("MMP thread stopped pool '%s' gethrtime %llu",
	    spa_name(spa), gethrtime());

	ASSERT(mmp->mmp_thread == NULL);
	mmp->mmp_thread_exiting = 0;
}