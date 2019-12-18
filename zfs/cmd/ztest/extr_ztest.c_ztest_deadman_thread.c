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
struct TYPE_5__ {scalar_t__ zs_thread_stop; scalar_t__ zs_thread_start; scalar_t__ zs_proc_stop; scalar_t__ zs_proc_start; } ;
typedef  TYPE_1__ ztest_shared_t ;
struct TYPE_6__ {int /*<<< orphan*/ * spa_root_vdev; } ;
typedef  TYPE_2__ spa_t ;
typedef  scalar_t__ hrtime_t ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 scalar_t__ MSEC2NSEC (int) ; 
 scalar_t__ NANOSEC ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ gethrtime () ; 
 int /*<<< orphan*/  poll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 
 scalar_t__ spa_suspended (TYPE_2__*) ; 
 int /*<<< orphan*/  thread_exit () ; 
 int /*<<< orphan*/  vdev_deadman (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int zfs_deadman_checktime_ms ; 
 int zfs_deadman_synctime_ms ; 
 int /*<<< orphan*/  ztest_exiting ; 
 TYPE_2__* ztest_spa ; 

__attribute__((used)) static void
ztest_deadman_thread(void *arg)
{
	ztest_shared_t *zs = arg;
	spa_t *spa = ztest_spa;
	hrtime_t delay, overdue, last_run = gethrtime();

	delay = (zs->zs_thread_stop - zs->zs_thread_start) +
	    MSEC2NSEC(zfs_deadman_synctime_ms);

	while (!ztest_exiting) {
		/*
		 * Wait for the delay timer while checking occasionally
		 * if we should stop.
		 */
		if (gethrtime() < last_run + delay) {
			(void) poll(NULL, 0, 1000);
			continue;
		}

		/*
		 * If the pool is suspended then fail immediately. Otherwise,
		 * check to see if the pool is making any progress. If
		 * vdev_deadman() discovers that there hasn't been any recent
		 * I/Os then it will end up aborting the tests.
		 */
		if (spa_suspended(spa) || spa->spa_root_vdev == NULL) {
			fatal(0, "aborting test after %llu seconds because "
			    "pool has transitioned to a suspended state.",
			    zfs_deadman_synctime_ms / 1000);
		}
		vdev_deadman(spa->spa_root_vdev, FTAG);

		/*
		 * If the process doesn't complete within a grace period of
		 * zfs_deadman_synctime_ms over the expected finish time,
		 * then it may be hung and is terminated.
		 */
		overdue = zs->zs_proc_stop + MSEC2NSEC(zfs_deadman_synctime_ms);
		if (gethrtime() > overdue) {
			fatal(0, "aborting test after %llu seconds because "
			    "the process is overdue for termination.",
			    (gethrtime() - zs->zs_proc_start) / NANOSEC);
		}

		(void) printf("ztest has been running for %lld seconds\n",
		    (gethrtime() - zs->zs_proc_start) / NANOSEC);

		last_run = gethrtime();
		delay = MSEC2NSEC(zfs_deadman_checktime_ms);
	}

	thread_exit();
}