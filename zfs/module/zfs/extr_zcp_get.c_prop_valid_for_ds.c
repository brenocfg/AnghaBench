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
typedef  int /*<<< orphan*/  zfs_type_t ;
typedef  scalar_t__ zfs_prop_t ;
struct TYPE_4__ {int /*<<< orphan*/  ds_dir; } ;
typedef  TYPE_1__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 scalar_t__ ZFS_PROP_ISCSIOPTIONS ; 
 scalar_t__ ZFS_PROP_MOUNTED ; 
 scalar_t__ ZFS_PROP_ORIGIN ; 
 int /*<<< orphan*/  dsl_dir_is_clone (int /*<<< orphan*/ ) ; 
 int get_objset_type (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_prop_valid_for_type (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

boolean_t
prop_valid_for_ds(dsl_dataset_t *ds, zfs_prop_t zfs_prop)
{
	int error;
	zfs_type_t zfs_type;

	/* properties not supported */
	if ((zfs_prop == ZFS_PROP_ISCSIOPTIONS) ||
	    (zfs_prop == ZFS_PROP_MOUNTED))
		return (B_FALSE);

	/* if we want the origin prop, ds must be a clone */
	if ((zfs_prop == ZFS_PROP_ORIGIN) && (!dsl_dir_is_clone(ds->ds_dir)))
		return (B_FALSE);

	error = get_objset_type(ds, &zfs_type);
	if (error != 0)
		return (B_FALSE);
	return (zfs_prop_valid_for_type(zfs_prop, zfs_type, B_FALSE));
}