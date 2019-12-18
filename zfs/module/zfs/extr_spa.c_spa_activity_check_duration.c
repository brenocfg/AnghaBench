#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_8__ {int ub_mmp_delay; } ;
typedef  TYPE_1__ uberblock_t ;
typedef  int /*<<< orphan*/  spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int MAX (int,int) ; 
 int MMP_FAIL_INT (TYPE_1__*) ; 
 scalar_t__ MMP_FAIL_INT_VALID (TYPE_1__*) ; 
 int MMP_IMPORT_SAFETY_FACTOR ; 
 int /*<<< orphan*/  MMP_INTERVAL (TYPE_1__*) ; 
 int /*<<< orphan*/  MMP_INTERVAL_OK (int /*<<< orphan*/ ) ; 
 scalar_t__ MMP_INTERVAL_VALID (TYPE_1__*) ; 
 scalar_t__ MMP_VALID (TYPE_1__*) ; 
 int MSEC2NSEC (int /*<<< orphan*/ ) ; 
 int NANOSEC ; 
 int /*<<< orphan*/  vdev_count_leaves (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_dbgmsg (char*,int,int,int,...) ; 
 int zfs_multihost_import_intervals ; 
 int /*<<< orphan*/  zfs_multihost_interval ; 

__attribute__((used)) static uint64_t
spa_activity_check_duration(spa_t *spa, uberblock_t *ub)
{
	uint64_t import_intervals = MAX(zfs_multihost_import_intervals, 1);
	uint64_t multihost_interval = MSEC2NSEC(
	    MMP_INTERVAL_OK(zfs_multihost_interval));
	uint64_t import_delay = MAX(NANOSEC, import_intervals *
	    multihost_interval);

	/*
	 * Local tunables determine a minimum duration except for the case
	 * where we know when the remote host will suspend the pool if MMP
	 * writes do not land.
	 *
	 * See Big Theory comment at the top of mmp.c for the reasoning behind
	 * these cases and times.
	 */

	ASSERT(MMP_IMPORT_SAFETY_FACTOR >= 100);

	if (MMP_INTERVAL_VALID(ub) && MMP_FAIL_INT_VALID(ub) &&
	    MMP_FAIL_INT(ub) > 0) {

		/* MMP on remote host will suspend pool after failed writes */
		import_delay = MMP_FAIL_INT(ub) * MSEC2NSEC(MMP_INTERVAL(ub)) *
		    MMP_IMPORT_SAFETY_FACTOR / 100;

		zfs_dbgmsg("fail_intvals>0 import_delay=%llu ub_mmp "
		    "mmp_fails=%llu ub_mmp mmp_interval=%llu "
		    "import_intervals=%u", import_delay, MMP_FAIL_INT(ub),
		    MMP_INTERVAL(ub), import_intervals);

	} else if (MMP_INTERVAL_VALID(ub) && MMP_FAIL_INT_VALID(ub) &&
	    MMP_FAIL_INT(ub) == 0) {

		/* MMP on remote host will never suspend pool */
		import_delay = MAX(import_delay, (MSEC2NSEC(MMP_INTERVAL(ub)) +
		    ub->ub_mmp_delay) * import_intervals);

		zfs_dbgmsg("fail_intvals=0 import_delay=%llu ub_mmp "
		    "mmp_interval=%llu ub_mmp_delay=%llu "
		    "import_intervals=%u", import_delay, MMP_INTERVAL(ub),
		    ub->ub_mmp_delay, import_intervals);

	} else if (MMP_VALID(ub)) {
		/*
		 * zfs-0.7 compatibility case
		 */

		import_delay = MAX(import_delay, (multihost_interval +
		    ub->ub_mmp_delay) * import_intervals);

		zfs_dbgmsg("import_delay=%llu ub_mmp_delay=%llu "
		    "import_intervals=%u leaves=%u", import_delay,
		    ub->ub_mmp_delay, import_intervals,
		    vdev_count_leaves(spa));
	} else {
		/* Using local tunings is the only reasonable option */
		zfs_dbgmsg("pool last imported on non-MMP aware "
		    "host using import_delay=%llu multihost_interval=%llu "
		    "import_intervals=%u", import_delay, multihost_interval,
		    import_intervals);
	}

	return (import_delay);
}