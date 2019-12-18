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
struct TYPE_4__ {int /*<<< orphan*/  z_os; } ;
typedef  TYPE_1__ zfsvfs_t ;
struct super_block {TYPE_1__* s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  dmu_objset_pool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_pool_iput_taskq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskq_wait_outstanding (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_unlinked_drain_stop_wait (TYPE_1__*) ; 
 int /*<<< orphan*/  zfsctl_destroy (TYPE_1__*) ; 

void
zfs_preumount(struct super_block *sb)
{
	zfsvfs_t *zfsvfs = sb->s_fs_info;

	/* zfsvfs is NULL when zfs_domount fails during mount */
	if (zfsvfs) {
		zfs_unlinked_drain_stop_wait(zfsvfs);
		zfsctl_destroy(sb->s_fs_info);
		/*
		 * Wait for iput_async before entering evict_inodes in
		 * generic_shutdown_super. The reason we must finish before
		 * evict_inodes is when lazytime is on, or when zfs_purgedir
		 * calls zfs_zget, iput would bump i_count from 0 to 1. This
		 * would race with the i_count check in evict_inodes. This means
		 * it could destroy the inode while we are still using it.
		 *
		 * We wait for two passes. xattr directories in the first pass
		 * may add xattr entries in zfs_purgedir, so in the second pass
		 * we wait for them. We don't use taskq_wait here because it is
		 * a pool wide taskq. Other mounted filesystems can constantly
		 * do iput_async and there's no guarantee when taskq will be
		 * empty.
		 */
		taskq_wait_outstanding(dsl_pool_iput_taskq(
		    dmu_objset_pool(zfsvfs->z_os)), 0);
		taskq_wait_outstanding(dsl_pool_iput_taskq(
		    dmu_objset_pool(zfsvfs->z_os)), 0);
	}
}