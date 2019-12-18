#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_3__ {int /*<<< orphan*/  ds_prev; int /*<<< orphan*/  ds_dir; } ;
typedef  TYPE_1__ dsl_dataset_t ;

/* Variables and functions */
 scalar_t__ DS_IS_DEFER_DESTROY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTAG ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 TYPE_1__* dmu_objset_ds (int /*<<< orphan*/ *) ; 
 int dmu_objset_hold (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dmu_objset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dataset_name (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ dsl_dir_is_clone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_unmount_snap (char*) ; 

void
zfs_destroy_unmount_origin(const char *fsname)
{
	int error;
	objset_t *os;
	dsl_dataset_t *ds;

	error = dmu_objset_hold(fsname, FTAG, &os);
	if (error != 0)
		return;
	ds = dmu_objset_ds(os);
	if (dsl_dir_is_clone(ds->ds_dir) && DS_IS_DEFER_DESTROY(ds->ds_prev)) {
		char originname[ZFS_MAX_DATASET_NAME_LEN];
		dsl_dataset_name(ds->ds_prev, originname);
		dmu_objset_rele(os, FTAG);
		zfs_unmount_snap(originname);
	} else {
		dmu_objset_rele(os, FTAG);
	}
}