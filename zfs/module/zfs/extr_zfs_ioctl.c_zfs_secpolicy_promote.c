#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {char* zc_name; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
struct TYPE_13__ {int /*<<< orphan*/  dd_pool; } ;
typedef  TYPE_2__ dsl_dir_t ;
struct TYPE_14__ {TYPE_2__* ds_dir; } ;
typedef  TYPE_3__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  cred_t ;
struct TYPE_15__ {int /*<<< orphan*/  dd_origin_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  ZFS_DELEG_PERM_MOUNT ; 
 int /*<<< orphan*/  ZFS_DELEG_PERM_PROMOTE ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int dsl_dataset_hold (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_3__**) ; 
 int dsl_dataset_hold_obj (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__**) ; 
 int /*<<< orphan*/  dsl_dataset_name (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  dsl_dataset_rele (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_6__* dsl_dir_phys (TYPE_2__*) ; 
 int dsl_pool_hold (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_pool_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int zfs_secpolicy_write_perms (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int zfs_secpolicy_write_perms_ds (char*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_secpolicy_promote(zfs_cmd_t *zc, nvlist_t *innvl, cred_t *cr)
{
	dsl_pool_t *dp;
	dsl_dataset_t *clone;
	int error;

	error = zfs_secpolicy_write_perms(zc->zc_name,
	    ZFS_DELEG_PERM_PROMOTE, cr);
	if (error != 0)
		return (error);

	error = dsl_pool_hold(zc->zc_name, FTAG, &dp);
	if (error != 0)
		return (error);

	error = dsl_dataset_hold(dp, zc->zc_name, FTAG, &clone);

	if (error == 0) {
		char parentname[ZFS_MAX_DATASET_NAME_LEN];
		dsl_dataset_t *origin = NULL;
		dsl_dir_t *dd;
		dd = clone->ds_dir;

		error = dsl_dataset_hold_obj(dd->dd_pool,
		    dsl_dir_phys(dd)->dd_origin_obj, FTAG, &origin);
		if (error != 0) {
			dsl_dataset_rele(clone, FTAG);
			dsl_pool_rele(dp, FTAG);
			return (error);
		}

		error = zfs_secpolicy_write_perms_ds(zc->zc_name, clone,
		    ZFS_DELEG_PERM_MOUNT, cr);

		dsl_dataset_name(origin, parentname);
		if (error == 0) {
			error = zfs_secpolicy_write_perms_ds(parentname, origin,
			    ZFS_DELEG_PERM_PROMOTE, cr);
		}
		dsl_dataset_rele(clone, FTAG);
		dsl_dataset_rele(origin, FTAG);
	}
	dsl_pool_rele(dp, FTAG);
	return (error);
}