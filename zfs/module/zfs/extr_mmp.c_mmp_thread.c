#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
struct TYPE_12__ {int mmp_last_write; int mmp_delay; int /*<<< orphan*/  mmp_thread; int /*<<< orphan*/ * mmp_zio_root; int /*<<< orphan*/  mmp_thread_lock; int /*<<< orphan*/  mmp_thread_cv; int /*<<< orphan*/  mmp_io_lock; int /*<<< orphan*/  mmp_thread_exiting; } ;
struct TYPE_11__ {TYPE_2__ spa_mmp; } ;
typedef  TYPE_1__ spa_t ;
typedef  TYPE_2__ mmp_thread_t ;
typedef  int hrtime_t ;
typedef  int /*<<< orphan*/  callb_cpr_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  CALLB_CPR_SAFE_BEGIN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CALLB_CPR_SAFE_END (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CALLOUT_FLAG_ABSOLUTE ; 
 int /*<<< orphan*/  CE_WARN ; 
 int MAX (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MMP_DEFAULT_INTERVAL ; 
 int MMP_FAIL_INTVS_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMP_INTERVAL_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMP_MIN_INTERVAL ; 
 int MSEC2NSEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NSEC2MSEC (int) ; 
 int /*<<< orphan*/  USEC2NSEC (int) ; 
 int /*<<< orphan*/  ZIO_SUSPEND_MMP ; 
 int /*<<< orphan*/  cmn_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cv_timedwait_sig_hires (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gethrtime () ; 
 int /*<<< orphan*/  mmp_thread_enter (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmp_thread_exit (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmp_write_uberblock (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int spa_multihost (TYPE_1__*) ; 
 int /*<<< orphan*/  spa_name (TYPE_1__*) ; 
 int spa_suspended (TYPE_1__*) ; 
 int /*<<< orphan*/  vdev_count_leaves (TYPE_1__*) ; 
 int /*<<< orphan*/  zfs_dbgmsg (char*,int /*<<< orphan*/ ,int,int,int,int,...) ; 
 int /*<<< orphan*/  zfs_multihost_fail_intervals ; 
 int /*<<< orphan*/  zfs_multihost_interval ; 
 int /*<<< orphan*/  zio_suspend (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mmp_thread(void *arg)
{
	spa_t *spa = (spa_t *)arg;
	mmp_thread_t *mmp = &spa->spa_mmp;
	boolean_t suspended = spa_suspended(spa);
	boolean_t multihost = spa_multihost(spa);
	uint64_t mmp_interval = MSEC2NSEC(MMP_INTERVAL_OK(
	    zfs_multihost_interval));
	uint32_t mmp_fail_intervals = MMP_FAIL_INTVS_OK(
	    zfs_multihost_fail_intervals);
	hrtime_t mmp_fail_ns = mmp_fail_intervals * mmp_interval;
	boolean_t last_spa_suspended = suspended;
	boolean_t last_spa_multihost = multihost;
	uint64_t last_mmp_interval = mmp_interval;
	uint32_t last_mmp_fail_intervals = mmp_fail_intervals;
	hrtime_t last_mmp_fail_ns = mmp_fail_ns;
	callb_cpr_t cpr;
	int skip_wait = 0;

	mmp_thread_enter(mmp, &cpr);

	while (!mmp->mmp_thread_exiting) {
		hrtime_t next_time = gethrtime() +
		    MSEC2NSEC(MMP_DEFAULT_INTERVAL);
		int leaves = MAX(vdev_count_leaves(spa), 1);

		/* Detect changes in tunables or state */

		last_spa_suspended = suspended;
		last_spa_multihost = multihost;
		suspended = spa_suspended(spa);
		multihost = spa_multihost(spa);

		last_mmp_interval = mmp_interval;
		last_mmp_fail_intervals = mmp_fail_intervals;
		last_mmp_fail_ns = mmp_fail_ns;
		mmp_interval = MSEC2NSEC(MMP_INTERVAL_OK(
		    zfs_multihost_interval));
		mmp_fail_intervals = MMP_FAIL_INTVS_OK(
		    zfs_multihost_fail_intervals);

		/* Smooth so pool is not suspended when reducing tunables */
		if (mmp_fail_intervals * mmp_interval < mmp_fail_ns) {
			mmp_fail_ns = (mmp_fail_ns * 31 +
			    mmp_fail_intervals * mmp_interval) / 32;
		} else {
			mmp_fail_ns = mmp_fail_intervals *
			    mmp_interval;
		}

		if (mmp_interval != last_mmp_interval ||
		    mmp_fail_intervals != last_mmp_fail_intervals) {
			/*
			 * We want other hosts to see new tunables as quickly as
			 * possible.  Write out at higher frequency than usual.
			 */
			skip_wait += leaves;
		}

		if (multihost)
			next_time = gethrtime() + mmp_interval / leaves;

		if (mmp_fail_ns != last_mmp_fail_ns) {
			zfs_dbgmsg("MMP interval change pool '%s' "
			    "gethrtime %llu last_mmp_interval %llu "
			    "mmp_interval %llu last_mmp_fail_intervals %u "
			    "mmp_fail_intervals %u mmp_fail_ns %llu "
			    "skip_wait %d leaves %d next_time %llu",
			    spa_name(spa), gethrtime(), last_mmp_interval,
			    mmp_interval, last_mmp_fail_intervals,
			    mmp_fail_intervals, mmp_fail_ns, skip_wait, leaves,
			    next_time);
		}

		/*
		 * MMP off => on, or suspended => !suspended:
		 * No writes occurred recently.  Update mmp_last_write to give
		 * us some time to try.
		 */
		if ((!last_spa_multihost && multihost) ||
		    (last_spa_suspended && !suspended)) {
			zfs_dbgmsg("MMP state change pool '%s': gethrtime %llu "
			    "last_spa_multihost %u multihost %u "
			    "last_spa_suspended %u suspended %u",
			    spa_name(spa), last_spa_multihost, multihost,
			    last_spa_suspended, suspended);
			mutex_enter(&mmp->mmp_io_lock);
			mmp->mmp_last_write = gethrtime();
			mmp->mmp_delay = mmp_interval;
			mutex_exit(&mmp->mmp_io_lock);
		}

		/*
		 * MMP on => off:
		 * mmp_delay == 0 tells importing node to skip activity check.
		 */
		if (last_spa_multihost && !multihost) {
			mutex_enter(&mmp->mmp_io_lock);
			mmp->mmp_delay = 0;
			mutex_exit(&mmp->mmp_io_lock);
		}

		/*
		 * Suspend the pool if no MMP write has succeeded in over
		 * mmp_interval * mmp_fail_intervals nanoseconds.
		 */
		if (multihost && !suspended && mmp_fail_intervals &&
		    (gethrtime() - mmp->mmp_last_write) > mmp_fail_ns) {
			zfs_dbgmsg("MMP suspending pool '%s': gethrtime %llu "
			    "mmp_last_write %llu mmp_interval %llu "
			    "mmp_fail_intervals %llu mmp_fail_ns %llu",
			    spa_name(spa), (u_longlong_t)gethrtime(),
			    (u_longlong_t)mmp->mmp_last_write,
			    (u_longlong_t)mmp_interval,
			    (u_longlong_t)mmp_fail_intervals,
			    (u_longlong_t)mmp_fail_ns);
			cmn_err(CE_WARN, "MMP writes to pool '%s' have not "
			    "succeeded in over %llu ms; suspending pool. "
			    "Hrtime %llu",
			    spa_name(spa),
			    NSEC2MSEC(gethrtime() - mmp->mmp_last_write),
			    gethrtime());
			zio_suspend(spa, NULL, ZIO_SUSPEND_MMP);
		}

		if (multihost && !suspended)
			mmp_write_uberblock(spa);

		if (skip_wait > 0) {
			next_time = gethrtime() + MSEC2NSEC(MMP_MIN_INTERVAL) /
			    leaves;
			skip_wait--;
		}

		CALLB_CPR_SAFE_BEGIN(&cpr);
		(void) cv_timedwait_sig_hires(&mmp->mmp_thread_cv,
		    &mmp->mmp_thread_lock, next_time, USEC2NSEC(100),
		    CALLOUT_FLAG_ABSOLUTE);
		CALLB_CPR_SAFE_END(&cpr, &mmp->mmp_thread_lock);
	}

	/* Outstanding writes are allowed to complete. */
	if (mmp->mmp_zio_root)
		zio_wait(mmp->mmp_zio_root);

	mmp->mmp_zio_root = NULL;
	mmp_thread_exit(mmp, &mmp->mmp_thread, &cpr);
}