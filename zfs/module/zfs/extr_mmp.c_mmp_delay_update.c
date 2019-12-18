#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* mmp_last_write; int mmp_delay; int /*<<< orphan*/  mmp_io_lock; } ;
struct TYPE_6__ {TYPE_2__ spa_mmp; } ;
typedef  TYPE_1__ spa_t ;
typedef  TYPE_2__ mmp_thread_t ;
typedef  int hrtime_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ B_FALSE ; 
 int MAX (int,int) ; 
 int /*<<< orphan*/  MMP_INTERVAL_OK (int /*<<< orphan*/ ) ; 
 int MSEC2NSEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 void* gethrtime () ; 
 scalar_t__ spa_multihost (TYPE_1__*) ; 
 int vdev_count_leaves (TYPE_1__*) ; 
 int /*<<< orphan*/  zfs_multihost_interval ; 

__attribute__((used)) static void
mmp_delay_update(spa_t *spa, boolean_t write_completed)
{
	mmp_thread_t *mts = &spa->spa_mmp;
	hrtime_t delay = gethrtime() - mts->mmp_last_write;

	ASSERT(MUTEX_HELD(&mts->mmp_io_lock));

	if (spa_multihost(spa) == B_FALSE) {
		mts->mmp_delay = 0;
		return;
	}

	if (delay > mts->mmp_delay)
		mts->mmp_delay = delay;

	if (write_completed == B_FALSE)
		return;

	mts->mmp_last_write = gethrtime();

	/*
	 * strictly less than, in case delay was changed above.
	 */
	if (delay < mts->mmp_delay) {
		hrtime_t min_delay =
		    MSEC2NSEC(MMP_INTERVAL_OK(zfs_multihost_interval)) /
		    MAX(1, vdev_count_leaves(spa));
		mts->mmp_delay = MAX(((delay + mts->mmp_delay * 127) / 128),
		    min_delay);
	}
}