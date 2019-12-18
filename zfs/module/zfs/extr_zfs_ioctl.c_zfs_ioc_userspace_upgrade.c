#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  z_sb; int /*<<< orphan*/ * z_os; } ;
typedef  TYPE_1__ zfsvfs_t ;
struct TYPE_9__ {int /*<<< orphan*/  zc_name; } ;
typedef  TYPE_2__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  deactivate_super (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dmu_objset_ds (int /*<<< orphan*/ *) ; 
 int dmu_objset_hold_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dmu_objset_refresh_ownership (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  dmu_objset_rele_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dmu_objset_userspace_upgrade (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_objset_userused_enabled (int /*<<< orphan*/ *) ; 
 scalar_t__ getzfsvfs (int /*<<< orphan*/ ,TYPE_1__**) ; 
 int zfs_resume_fs (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int zfs_suspend_fs (TYPE_1__*) ; 

__attribute__((used)) static int
zfs_ioc_userspace_upgrade(zfs_cmd_t *zc)
{
	objset_t *os;
	int error = 0;
	zfsvfs_t *zfsvfs;

	if (getzfsvfs(zc->zc_name, &zfsvfs) == 0) {
		if (!dmu_objset_userused_enabled(zfsvfs->z_os)) {
			/*
			 * If userused is not enabled, it may be because the
			 * objset needs to be closed & reopened (to grow the
			 * objset_phys_t).  Suspend/resume the fs will do that.
			 */
			dsl_dataset_t *ds, *newds;

			ds = dmu_objset_ds(zfsvfs->z_os);
			error = zfs_suspend_fs(zfsvfs);
			if (error == 0) {
				dmu_objset_refresh_ownership(ds, &newds,
				    B_TRUE, zfsvfs);
				error = zfs_resume_fs(zfsvfs, newds);
			}
		}
		if (error == 0)
			error = dmu_objset_userspace_upgrade(zfsvfs->z_os);
		deactivate_super(zfsvfs->z_sb);
	} else {
		/* XXX kind of reading contents without owning */
		error = dmu_objset_hold_flags(zc->zc_name, B_TRUE, FTAG, &os);
		if (error != 0)
			return (error);

		error = dmu_objset_userspace_upgrade(os);
		dmu_objset_rele_flags(os, B_TRUE, FTAG);
	}

	return (error);
}