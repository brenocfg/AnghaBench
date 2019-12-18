#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ zfs_type_t ;
struct TYPE_7__ {int /*<<< orphan*/  zko_kobj; } ;
typedef  TYPE_1__ zfs_mod_kobj_t ;
struct kobject {int dummy; } ;
struct TYPE_8__ {void* p2k_show_func; TYPE_1__* p2k_parent; int /*<<< orphan*/  p2k_attr_count; int /*<<< orphan*/  p2k_table; } ;
typedef  TYPE_2__ prop_to_kobj_arg_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  ZFS_NUM_PROPS ; 
 int /*<<< orphan*/  ZFS_PROP_ATTR_COUNT ; 
 char* ZFS_SYSFS_DATASET_PROPERTIES ; 
 char* ZFS_SYSFS_POOL_PROPERTIES ; 
 scalar_t__ ZFS_TYPE_POOL ; 
 int /*<<< orphan*/  ZPOOL_NUM_PROPS ; 
 int /*<<< orphan*/  ZPOOL_PROP_ATTR_COUNT ; 
 void* dataset_property_show ; 
 void* pool_property_show ; 
 int zfs_kobj_add (TYPE_1__*,struct kobject*,char const*) ; 
 int zfs_kobj_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  zfs_kobj_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_prop_get_table () ; 
 int /*<<< orphan*/  zpool_prop_get_table () ; 
 int /*<<< orphan*/  zprop_iter_common (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  zprop_to_kobj ; 

__attribute__((used)) static int
zfs_sysfs_properties_init(zfs_mod_kobj_t *zfs_kobj, struct kobject *parent,
    zfs_type_t type)
{
	prop_to_kobj_arg_t context;
	const char *name;
	int err;

	/*
	 * Create a parent kobject to host properties.
	 *
	 * '/sys/module/zfs/properties.<type>'
	 */
	if (type == ZFS_TYPE_POOL) {
		name = ZFS_SYSFS_POOL_PROPERTIES;
		context.p2k_table = zpool_prop_get_table();
		context.p2k_attr_count = ZPOOL_PROP_ATTR_COUNT;
		context.p2k_parent = zfs_kobj;
		context.p2k_show_func = pool_property_show;
		err = zfs_kobj_init(zfs_kobj, 0, ZPOOL_NUM_PROPS,
		    pool_property_show);
	} else {
		name = ZFS_SYSFS_DATASET_PROPERTIES;
		context.p2k_table = zfs_prop_get_table();
		context.p2k_attr_count = ZFS_PROP_ATTR_COUNT;
		context.p2k_parent = zfs_kobj;
		context.p2k_show_func = dataset_property_show;
		err = zfs_kobj_init(zfs_kobj, 0, ZFS_NUM_PROPS,
		    dataset_property_show);
	}

	if (err)
		return (err);

	err = zfs_kobj_add(zfs_kobj, parent, name);
	if (err) {
		zfs_kobj_release(&zfs_kobj->zko_kobj);
		return (err);
	}

	/*
	 * Create a kobject for each property.
	 *
	 * '/sys/module/zfs/properties.<type>/<property>'
	 */
	(void) zprop_iter_common(zprop_to_kobj, &context, B_TRUE,
	    B_FALSE, type);

	return (err);
}