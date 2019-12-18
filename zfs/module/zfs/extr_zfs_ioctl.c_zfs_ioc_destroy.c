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
struct TYPE_3__ {char* zc_name; int /*<<< orphan*/  zc_defer_destroy; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  namebuf ;
typedef  scalar_t__ dmu_objset_type_t ;

/* Variables and functions */
 scalar_t__ DMU_OST_ZFS ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  FTAG ; 
 int SET_ERROR (int) ; 
 int /*<<< orphan*/  ZFS_MAX_DATASET_NAME_LEN ; 
 int dmu_objset_hold (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dmu_objset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dmu_objset_type (int /*<<< orphan*/ *) ; 
 int dsl_destroy_head (char*) ; 
 int dsl_destroy_snapshot (char*,int /*<<< orphan*/ ) ; 
 char* recv_clone_name ; 
 int snprintf (char*,int,char*,char*,char*) ; 
 scalar_t__ strchr (char*,char) ; 
 int /*<<< orphan*/  zfs_unmount_snap (char*) ; 

__attribute__((used)) static int
zfs_ioc_destroy(zfs_cmd_t *zc)
{
	objset_t *os;
	dmu_objset_type_t ost;
	int err;

	err = dmu_objset_hold(zc->zc_name, FTAG, &os);
	if (err != 0)
		return (err);
	ost = dmu_objset_type(os);
	dmu_objset_rele(os, FTAG);

	if (ost == DMU_OST_ZFS)
		zfs_unmount_snap(zc->zc_name);

	if (strchr(zc->zc_name, '@')) {
		err = dsl_destroy_snapshot(zc->zc_name, zc->zc_defer_destroy);
	} else {
		err = dsl_destroy_head(zc->zc_name);
		if (err == EEXIST) {
			/*
			 * It is possible that the given DS may have
			 * hidden child (%recv) datasets - "leftovers"
			 * resulting from the previously interrupted
			 * 'zfs receive'.
			 *
			 * 6 extra bytes for /%recv
			 */
			char namebuf[ZFS_MAX_DATASET_NAME_LEN + 6];

			if (snprintf(namebuf, sizeof (namebuf), "%s/%s",
			    zc->zc_name, recv_clone_name) >=
			    sizeof (namebuf))
				return (SET_ERROR(EINVAL));

			/*
			 * Try to remove the hidden child (%recv) and after
			 * that try to remove the target dataset.
			 * If the hidden child (%recv) does not exist
			 * the original error (EEXIST) will be returned
			 */
			err = dsl_destroy_head(namebuf);
			if (err == 0)
				err = dsl_destroy_head(zc->zc_name);
			else if (err == ENOENT)
				err = SET_ERROR(EEXIST);
		}
	}

	return (err);
}