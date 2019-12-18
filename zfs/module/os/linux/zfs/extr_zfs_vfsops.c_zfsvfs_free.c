#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int z_hold_size; int /*<<< orphan*/  z_kstat; int /*<<< orphan*/  z_vfs; int /*<<< orphan*/ * z_hold_locks; int /*<<< orphan*/ * z_hold_trees; int /*<<< orphan*/  z_fuid_lock; int /*<<< orphan*/  z_teardown_inactive_lock; int /*<<< orphan*/  z_teardown_lock; int /*<<< orphan*/  z_all_znodes; int /*<<< orphan*/  z_lock; int /*<<< orphan*/  z_znodes_lock; } ;
typedef  TYPE_1__ zfsvfs_t ;
typedef  int /*<<< orphan*/  kmutex_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  avl_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dataset_kstats_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  list_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrm_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmem_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfs_fuid_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  zfsvfs_vfs_free (int /*<<< orphan*/ ) ; 

void
zfsvfs_free(zfsvfs_t *zfsvfs)
{
	int i, size = zfsvfs->z_hold_size;

	zfs_fuid_destroy(zfsvfs);

	mutex_destroy(&zfsvfs->z_znodes_lock);
	mutex_destroy(&zfsvfs->z_lock);
	list_destroy(&zfsvfs->z_all_znodes);
	rrm_destroy(&zfsvfs->z_teardown_lock);
	rw_destroy(&zfsvfs->z_teardown_inactive_lock);
	rw_destroy(&zfsvfs->z_fuid_lock);
	for (i = 0; i != size; i++) {
		avl_destroy(&zfsvfs->z_hold_trees[i]);
		mutex_destroy(&zfsvfs->z_hold_locks[i]);
	}
	vmem_free(zfsvfs->z_hold_trees, sizeof (avl_tree_t) * size);
	vmem_free(zfsvfs->z_hold_locks, sizeof (kmutex_t) * size);
	zfsvfs_vfs_free(zfsvfs->z_vfs);
	dataset_kstats_destroy(&zfsvfs->z_kstat);
	kmem_free(zfsvfs, sizeof (zfsvfs_t));
}