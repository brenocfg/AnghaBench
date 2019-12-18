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
struct TYPE_6__ {int /*<<< orphan*/ * svr_thread; int /*<<< orphan*/  svr_vdev_id; } ;
typedef  TYPE_1__ spa_vdev_removal_t ;
struct TYPE_7__ {TYPE_1__* spa_vdev_removal; } ;
typedef  TYPE_2__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  TS_RUN ; 
 int /*<<< orphan*/  minclsyspri ; 
 int /*<<< orphan*/  p0 ; 
 int /*<<< orphan*/  spa_vdev_remove_thread ; 
 int /*<<< orphan*/  spa_writeable (TYPE_2__*) ; 
 int /*<<< orphan*/ * thread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_dbgmsg (char*,int /*<<< orphan*/ ) ; 

void
spa_restart_removal(spa_t *spa)
{
	spa_vdev_removal_t *svr = spa->spa_vdev_removal;

	if (svr == NULL)
		return;

	/*
	 * In general when this function is called there is no
	 * removal thread running. The only scenario where this
	 * is not true is during spa_import() where this function
	 * is called twice [once from spa_import_impl() and
	 * spa_async_resume()]. Thus, in the scenario where we
	 * import a pool that has an ongoing removal we don't
	 * want to spawn a second thread.
	 */
	if (svr->svr_thread != NULL)
		return;

	if (!spa_writeable(spa))
		return;

	zfs_dbgmsg("restarting removal of %llu", svr->svr_vdev_id);
	svr->svr_thread = thread_create(NULL, 0, spa_vdev_remove_thread, spa,
	    0, &p0, TS_RUN, minclsyspri);
}