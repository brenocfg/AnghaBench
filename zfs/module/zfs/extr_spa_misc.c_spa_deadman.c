#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int spa_sync_starttime; int /*<<< orphan*/  spa_deadman_tqid; int /*<<< orphan*/  spa_root_vdev; int /*<<< orphan*/  spa_deadman_calls; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 scalar_t__ MSEC_TO_TICK (int /*<<< orphan*/ ) ; 
 int NANOSEC ; 
 int /*<<< orphan*/  TQ_SLEEP ; 
 scalar_t__ ddi_get_lbolt () ; 
 int gethrtime () ; 
 scalar_t__ spa_suspended (TYPE_1__*) ; 
 int /*<<< orphan*/  system_delay_taskq ; 
 int /*<<< orphan*/  taskq_dispatch_delay (int /*<<< orphan*/ ,void (*) (void*),TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vdev_deadman (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_dbgmsg (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_deadman_checktime_ms ; 
 scalar_t__ zfs_deadman_enabled ; 

void
spa_deadman(void *arg)
{
	spa_t *spa = arg;

	/* Disable the deadman if the pool is suspended. */
	if (spa_suspended(spa))
		return;

	zfs_dbgmsg("slow spa_sync: started %llu seconds ago, calls %llu",
	    (gethrtime() - spa->spa_sync_starttime) / NANOSEC,
	    ++spa->spa_deadman_calls);
	if (zfs_deadman_enabled)
		vdev_deadman(spa->spa_root_vdev, FTAG);

	spa->spa_deadman_tqid = taskq_dispatch_delay(system_delay_taskq,
	    spa_deadman, spa, TQ_SLEEP, ddi_get_lbolt() +
	    MSEC_TO_TICK(zfs_deadman_checktime_ms));
}