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
struct TYPE_8__ {int /*<<< orphan*/  mmp_thread_lock; scalar_t__ mmp_thread; } ;
struct TYPE_7__ {TYPE_2__ spa_mmp; } ;
typedef  TYPE_1__ spa_t ;
typedef  TYPE_2__ mmp_thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  TS_RUN ; 
 int /*<<< orphan*/  defclsyspri ; 
 int /*<<< orphan*/  gethrtime () ; 
 int /*<<< orphan*/  mmp_thread ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p0 ; 
 int /*<<< orphan*/  spa_name (TYPE_1__*) ; 
 scalar_t__ spa_writeable (TYPE_1__*) ; 
 scalar_t__ thread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_dbgmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
mmp_thread_start(spa_t *spa)
{
	mmp_thread_t *mmp = &spa->spa_mmp;

	if (spa_writeable(spa)) {
		mutex_enter(&mmp->mmp_thread_lock);
		if (!mmp->mmp_thread) {
			mmp->mmp_thread = thread_create(NULL, 0, mmp_thread,
			    spa, 0, &p0, TS_RUN, defclsyspri);
			zfs_dbgmsg("MMP thread started pool '%s' "
			    "gethrtime %llu", spa_name(spa), gethrtime());
		}
		mutex_exit(&mmp->mmp_thread_lock);
	}
}