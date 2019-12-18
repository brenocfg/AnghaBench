#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  avl_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ddt_fini () ; 
 int /*<<< orphan*/  dmu_fini () ; 
 int /*<<< orphan*/  fm_fini () ; 
 int /*<<< orphan*/  l2arc_stop () ; 
 int /*<<< orphan*/  metaslab_stat_fini () ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qat_fini () ; 
 int /*<<< orphan*/  scan_fini () ; 
 int /*<<< orphan*/  spa_evict_all () ; 
 int /*<<< orphan*/  spa_import_progress_destroy () ; 
 int /*<<< orphan*/  spa_l2cache_avl ; 
 int /*<<< orphan*/  spa_l2cache_lock ; 
 int /*<<< orphan*/  spa_namespace_avl ; 
 int /*<<< orphan*/  spa_namespace_cv ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 int /*<<< orphan*/  spa_spare_avl ; 
 int /*<<< orphan*/  spa_spare_lock ; 
 int /*<<< orphan*/  unique_fini () ; 
 int /*<<< orphan*/  vdev_cache_stat_fini () ; 
 int /*<<< orphan*/  vdev_file_fini () ; 
 int /*<<< orphan*/  vdev_mirror_stat_fini () ; 
 int /*<<< orphan*/  vdev_raidz_math_fini () ; 
 int /*<<< orphan*/  zfs_btree_fini () ; 
 int /*<<< orphan*/  zfs_refcount_fini () ; 
 int /*<<< orphan*/  zil_fini () ; 
 int /*<<< orphan*/  zio_fini () ; 

void
spa_fini(void)
{
	l2arc_stop();

	spa_evict_all();

	vdev_file_fini();
	vdev_cache_stat_fini();
	vdev_mirror_stat_fini();
	vdev_raidz_math_fini();
	zil_fini();
	dmu_fini();
	zio_fini();
	ddt_fini();
	metaslab_stat_fini();
	zfs_btree_fini();
	unique_fini();
	zfs_refcount_fini();
	fm_fini();
	scan_fini();
	qat_fini();
	spa_import_progress_destroy();

	avl_destroy(&spa_namespace_avl);
	avl_destroy(&spa_spare_avl);
	avl_destroy(&spa_l2cache_avl);

	cv_destroy(&spa_namespace_cv);
	mutex_destroy(&spa_namespace_lock);
	mutex_destroy(&spa_spare_lock);
	mutex_destroy(&spa_l2cache_lock);
}