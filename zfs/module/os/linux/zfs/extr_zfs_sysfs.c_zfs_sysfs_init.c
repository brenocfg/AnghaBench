#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct kobject {int dummy; } ;
struct TYPE_2__ {struct kobject kobj; } ;
struct module {TYPE_1__ mkobj; } ;

/* Variables and functions */
 scalar_t__ THIS_MODULE ; 
 int /*<<< orphan*/  ZFS_TYPE_FILESYSTEM ; 
 int /*<<< orphan*/  ZFS_TYPE_POOL ; 
 int /*<<< orphan*/  dataset_props_kobj ; 
 int /*<<< orphan*/  fs_kobj ; 
 int /*<<< orphan*/  kernel_features_kobj ; 
 struct kobject* kobject_create_and_add (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pool_features_kobj ; 
 int /*<<< orphan*/  pool_props_kobj ; 
 int zfs_kernel_features_init (int /*<<< orphan*/ *,struct kobject*) ; 
 int /*<<< orphan*/  zfs_kobj_fini (int /*<<< orphan*/ *) ; 
 int zfs_pool_features_init (int /*<<< orphan*/ *,struct kobject*) ; 
 int zfs_sysfs_properties_init (int /*<<< orphan*/ *,struct kobject*,int /*<<< orphan*/ ) ; 

void
zfs_sysfs_init(void)
{
	struct kobject *parent;
#if defined(CONFIG_ZFS) && !defined(CONFIG_ZFS_MODULE)
	parent = kobject_create_and_add("zfs", fs_kobj);
#else
	parent = &(((struct module *)(THIS_MODULE))->mkobj).kobj;
#endif
	int err;

	if (parent == NULL)
		return;

	err = zfs_kernel_features_init(&kernel_features_kobj, parent);
	if (err)
		return;

	err = zfs_pool_features_init(&pool_features_kobj, parent);
	if (err) {
		zfs_kobj_fini(&kernel_features_kobj);
		return;
	}

	err = zfs_sysfs_properties_init(&pool_props_kobj, parent,
	    ZFS_TYPE_POOL);
	if (err) {
		zfs_kobj_fini(&kernel_features_kobj);
		zfs_kobj_fini(&pool_features_kobj);
		return;
	}

	err = zfs_sysfs_properties_init(&dataset_props_kobj, parent,
	    ZFS_TYPE_FILESYSTEM);
	if (err) {
		zfs_kobj_fini(&kernel_features_kobj);
		zfs_kobj_fini(&pool_features_kobj);
		zfs_kobj_fini(&pool_props_kobj);
		return;
	}
}