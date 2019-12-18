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
struct TYPE_6__ {int /*<<< orphan*/ * z_log; int /*<<< orphan*/  z_os; } ;
typedef  TYPE_1__ zfsvfs_t ;
struct super_block {TYPE_1__* s_fs_info; } ;
struct TYPE_7__ {int /*<<< orphan*/  dp_spa; } ;
typedef  TYPE_2__ dsl_pool_t ;
typedef  int /*<<< orphan*/  cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_ENTER (TYPE_1__*) ; 
 int /*<<< orphan*/  ZFS_EXIT (TYPE_1__*) ; 
 TYPE_2__* dmu_objset_pool (int /*<<< orphan*/ ) ; 
 scalar_t__ spa_suspended (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_sync_allpools () ; 
 int /*<<< orphan*/  zil_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
zfs_sync(struct super_block *sb, int wait, cred_t *cr)
{
	zfsvfs_t *zfsvfs = sb->s_fs_info;

	/*
	 * Semantically, the only requirement is that the sync be initiated.
	 * The DMU syncs out txgs frequently, so there's nothing to do.
	 */
	if (!wait)
		return (0);

	if (zfsvfs != NULL) {
		/*
		 * Sync a specific filesystem.
		 */
		dsl_pool_t *dp;

		ZFS_ENTER(zfsvfs);
		dp = dmu_objset_pool(zfsvfs->z_os);

		/*
		 * If the system is shutting down, then skip any
		 * filesystems which may exist on a suspended pool.
		 */
		if (spa_suspended(dp->dp_spa)) {
			ZFS_EXIT(zfsvfs);
			return (0);
		}

		if (zfsvfs->z_log != NULL)
			zil_commit(zfsvfs->z_log, 0);

		ZFS_EXIT(zfsvfs);
	} else {
		/*
		 * Sync all ZFS filesystems.  This is what happens when you
		 * run sync(1M).  Unlike other filesystems, ZFS honors the
		 * request by waiting for all pools to commit all dirty data.
		 */
		spa_sync_allpools();
	}

	return (0);
}