#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ zo_mmp_test; } ;
typedef  TYPE_1__ ztest_shared_opts_t ;
typedef  int /*<<< orphan*/  ztest_ds_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_13__ {int /*<<< orphan*/  spa_props_lock; int /*<<< orphan*/  spa_multihost; } ;
typedef  TYPE_2__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  SCL_CONFIG ; 
 int /*<<< orphan*/  mmp_signal_all_threads () ; 
 int /*<<< orphan*/  mmp_thread_start (TYPE_2__*) ; 
 int /*<<< orphan*/  mmp_thread_stop (TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_config_enter (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_get_dsl (TYPE_2__*) ; 
 scalar_t__ spa_multihost (TYPE_2__*) ; 
 scalar_t__ spa_suspended (TYPE_2__*) ; 
 int /*<<< orphan*/  txg_wait_synced (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_multihost_fail_intervals ; 
 TYPE_1__ ztest_opts ; 
 TYPE_2__* ztest_spa ; 

void
ztest_mmp_enable_disable(ztest_ds_t *zd, uint64_t id)
{
	ztest_shared_opts_t *zo = &ztest_opts;
	spa_t *spa = ztest_spa;

	if (zo->zo_mmp_test)
		return;

	/*
	 * Since enabling MMP involves setting a property, it could not be done
	 * while the pool is suspended.
	 */
	if (spa_suspended(spa))
		return;

	spa_config_enter(spa, SCL_CONFIG, FTAG, RW_READER);
	mutex_enter(&spa->spa_props_lock);

	zfs_multihost_fail_intervals = 0;

	if (!spa_multihost(spa)) {
		spa->spa_multihost = B_TRUE;
		mmp_thread_start(spa);
	}

	mutex_exit(&spa->spa_props_lock);
	spa_config_exit(spa, SCL_CONFIG, FTAG);

	txg_wait_synced(spa_get_dsl(spa), 0);
	mmp_signal_all_threads();
	txg_wait_synced(spa_get_dsl(spa), 0);

	spa_config_enter(spa, SCL_CONFIG, FTAG, RW_READER);
	mutex_enter(&spa->spa_props_lock);

	if (spa_multihost(spa)) {
		mmp_thread_stop(spa);
		spa->spa_multihost = B_FALSE;
	}

	mutex_exit(&spa->spa_props_lock);
	spa_config_exit(spa, SCL_CONFIG, FTAG);
}