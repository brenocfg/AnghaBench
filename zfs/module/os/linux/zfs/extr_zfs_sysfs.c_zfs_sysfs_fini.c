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
 int /*<<< orphan*/  dataset_props_kobj ; 
 int /*<<< orphan*/  kernel_features_kobj ; 
 int /*<<< orphan*/  pool_features_kobj ; 
 int /*<<< orphan*/  pool_props_kobj ; 
 int /*<<< orphan*/  zfs_kobj_fini (int /*<<< orphan*/ *) ; 

void
zfs_sysfs_fini(void)
{
	/*
	 * Remove top-level kobjects; each will remove any children kobjects
	 */
	zfs_kobj_fini(&kernel_features_kobj);
	zfs_kobj_fini(&pool_features_kobj);
	zfs_kobj_fini(&dataset_props_kobj);
	zfs_kobj_fini(&pool_props_kobj);
}