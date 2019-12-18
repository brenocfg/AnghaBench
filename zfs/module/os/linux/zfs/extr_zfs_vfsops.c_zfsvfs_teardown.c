#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {void* z_suspended; scalar_t__ z_sa_hdl; } ;
typedef  TYPE_2__ znode_t ;
struct TYPE_15__ {scalar_t__ z_nr_znodes; int /*<<< orphan*/ * z_os; int /*<<< orphan*/  z_teardown_lock; int /*<<< orphan*/  z_teardown_inactive_lock; void* z_unmounted; int /*<<< orphan*/  z_znodes_lock; int /*<<< orphan*/  z_all_znodes; int /*<<< orphan*/ * z_log; TYPE_1__* z_parent; } ;
typedef  TYPE_3__ zfsvfs_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  void* boolean_t ;
struct TYPE_13__ {int /*<<< orphan*/  z_sb; } ;

/* Variables and functions */
 void* B_FALSE ; 
 void* B_TRUE ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int TXG_SIZE ; 
 int /*<<< orphan*/  ZTOI (TYPE_2__*) ; 
 int /*<<< orphan*/  dmu_objset_evict_dbufs (int /*<<< orphan*/ *) ; 
 scalar_t__ dmu_objset_is_dirty (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dmu_objset_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_pool_iput_taskq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * igrab (int /*<<< orphan*/ ) ; 
 TYPE_2__* list_head (int /*<<< orphan*/ *) ; 
 TYPE_2__* list_next (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrm_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrm_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shrink_dcache_sb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskq_wait_outstanding (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txg_wait_synced (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_is_readonly (TYPE_3__*) ; 
 int /*<<< orphan*/  zfs_unlinked_drain_stop_wait (TYPE_3__*) ; 
 int /*<<< orphan*/  zfs_unregister_callbacks (TYPE_3__*) ; 
 int /*<<< orphan*/  zfs_znode_dmu_fini (TYPE_2__*) ; 
 int /*<<< orphan*/  zil_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfsvfs_teardown(zfsvfs_t *zfsvfs, boolean_t unmounting)
{
	znode_t	*zp;

	zfs_unlinked_drain_stop_wait(zfsvfs);

	/*
	 * If someone has not already unmounted this file system,
	 * drain the iput_taskq to ensure all active references to the
	 * zfsvfs_t have been handled only then can it be safely destroyed.
	 */
	if (zfsvfs->z_os) {
		/*
		 * If we're unmounting we have to wait for the list to
		 * drain completely.
		 *
		 * If we're not unmounting there's no guarantee the list
		 * will drain completely, but iputs run from the taskq
		 * may add the parents of dir-based xattrs to the taskq
		 * so we want to wait for these.
		 *
		 * We can safely read z_nr_znodes without locking because the
		 * VFS has already blocked operations which add to the
		 * z_all_znodes list and thus increment z_nr_znodes.
		 */
		int round = 0;
		while (zfsvfs->z_nr_znodes > 0) {
			taskq_wait_outstanding(dsl_pool_iput_taskq(
			    dmu_objset_pool(zfsvfs->z_os)), 0);
			if (++round > 1 && !unmounting)
				break;
		}
	}

	rrm_enter(&zfsvfs->z_teardown_lock, RW_WRITER, FTAG);

	if (!unmounting) {
		/*
		 * We purge the parent filesystem's super block as the
		 * parent filesystem and all of its snapshots have their
		 * inode's super block set to the parent's filesystem's
		 * super block.  Note,  'z_parent' is self referential
		 * for non-snapshots.
		 */
		shrink_dcache_sb(zfsvfs->z_parent->z_sb);
	}

	/*
	 * Close the zil. NB: Can't close the zil while zfs_inactive
	 * threads are blocked as zil_close can call zfs_inactive.
	 */
	if (zfsvfs->z_log) {
		zil_close(zfsvfs->z_log);
		zfsvfs->z_log = NULL;
	}

	rw_enter(&zfsvfs->z_teardown_inactive_lock, RW_WRITER);

	/*
	 * If we are not unmounting (ie: online recv) and someone already
	 * unmounted this file system while we were doing the switcheroo,
	 * or a reopen of z_os failed then just bail out now.
	 */
	if (!unmounting && (zfsvfs->z_unmounted || zfsvfs->z_os == NULL)) {
		rw_exit(&zfsvfs->z_teardown_inactive_lock);
		rrm_exit(&zfsvfs->z_teardown_lock, FTAG);
		return (SET_ERROR(EIO));
	}

	/*
	 * At this point there are no VFS ops active, and any new VFS ops
	 * will fail with EIO since we have z_teardown_lock for writer (only
	 * relevant for forced unmount).
	 *
	 * Release all holds on dbufs. We also grab an extra reference to all
	 * the remaining inodes so that the kernel does not attempt to free
	 * any inodes of a suspended fs. This can cause deadlocks since the
	 * zfs_resume_fs() process may involve starting threads, which might
	 * attempt to free unreferenced inodes to free up memory for the new
	 * thread.
	 */
	if (!unmounting) {
		mutex_enter(&zfsvfs->z_znodes_lock);
		for (zp = list_head(&zfsvfs->z_all_znodes); zp != NULL;
		    zp = list_next(&zfsvfs->z_all_znodes, zp)) {
			if (zp->z_sa_hdl)
				zfs_znode_dmu_fini(zp);
			if (igrab(ZTOI(zp)) != NULL)
				zp->z_suspended = B_TRUE;

		}
		mutex_exit(&zfsvfs->z_znodes_lock);
	}

	/*
	 * If we are unmounting, set the unmounted flag and let new VFS ops
	 * unblock.  zfs_inactive will have the unmounted behavior, and all
	 * other VFS ops will fail with EIO.
	 */
	if (unmounting) {
		zfsvfs->z_unmounted = B_TRUE;
		rw_exit(&zfsvfs->z_teardown_inactive_lock);
		rrm_exit(&zfsvfs->z_teardown_lock, FTAG);
	}

	/*
	 * z_os will be NULL if there was an error in attempting to reopen
	 * zfsvfs, so just return as the properties had already been
	 *
	 * unregistered and cached data had been evicted before.
	 */
	if (zfsvfs->z_os == NULL)
		return (0);

	/*
	 * Unregister properties.
	 */
	zfs_unregister_callbacks(zfsvfs);

	/*
	 * Evict cached data. We must write out any dirty data before
	 * disowning the dataset.
	 */
	objset_t *os = zfsvfs->z_os;
	boolean_t os_dirty = B_FALSE;
	for (int t = 0; t < TXG_SIZE; t++) {
		if (dmu_objset_is_dirty(os, t)) {
			os_dirty = B_TRUE;
			break;
		}
	}
	if (!zfs_is_readonly(zfsvfs) && os_dirty) {
		txg_wait_synced(dmu_objset_pool(zfsvfs->z_os), 0);
	}
	dmu_objset_evict_dbufs(zfsvfs->z_os);

	return (0);
}