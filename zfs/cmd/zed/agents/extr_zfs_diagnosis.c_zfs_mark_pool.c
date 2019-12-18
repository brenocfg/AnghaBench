#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zpool_handle_t ;
struct TYPE_10__ {scalar_t__ ertv_nsec; scalar_t__ ertv_sec; int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {scalar_t__ zc_pool_guid; scalar_t__ zc_vdev_guid; } ;
struct TYPE_9__ {TYPE_3__ zc_when; TYPE_1__ zc_data; int /*<<< orphan*/  zc_present; } ;
typedef  TYPE_2__ zfs_case_t ;
typedef  int uint_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  TYPE_3__ er_timeval_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_LOADED_TIME ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_TREE ; 
 int /*<<< orphan*/  ZPOOL_PROP_GUID ; 
 int nvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nvlist_lookup_uint64_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__**,int*) ; 
 TYPE_2__* uu_list_first (int /*<<< orphan*/ ) ; 
 TYPE_2__* uu_list_next (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  zfs_cases ; 
 int /*<<< orphan*/  zfs_mark_vdev (scalar_t__,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  zpool_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zpool_get_config (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ zpool_get_prop_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_mark_pool(zpool_handle_t *zhp, void *unused)
{
	zfs_case_t *zcp;
	uint64_t pool_guid;
	uint64_t *tod;
	er_timeval_t loaded = { 0 };
	nvlist_t *config, *vd;
	uint_t nelem = 0;
	int ret;

	pool_guid = zpool_get_prop_int(zhp, ZPOOL_PROP_GUID, NULL);
	/*
	 * Mark any cases associated with just this pool.
	 */
	for (zcp = uu_list_first(zfs_cases); zcp != NULL;
	    zcp = uu_list_next(zfs_cases, zcp)) {
		if (zcp->zc_data.zc_pool_guid == pool_guid &&
		    zcp->zc_data.zc_vdev_guid == 0)
			zcp->zc_present = B_TRUE;
	}

	if ((config = zpool_get_config(zhp, NULL)) == NULL) {
		zpool_close(zhp);
		return (-1);
	}

	(void) nvlist_lookup_uint64_array(config, ZPOOL_CONFIG_LOADED_TIME,
	    &tod, &nelem);
	if (nelem == 2) {
		loaded.ertv_sec = tod[0];
		loaded.ertv_nsec = tod[1];
		for (zcp = uu_list_first(zfs_cases); zcp != NULL;
		    zcp = uu_list_next(zfs_cases, zcp)) {
			if (zcp->zc_data.zc_pool_guid == pool_guid &&
			    zcp->zc_data.zc_vdev_guid == 0) {
				zcp->zc_when = loaded;
			}
		}
	}

	ret = nvlist_lookup_nvlist(config, ZPOOL_CONFIG_VDEV_TREE, &vd);
	if (ret) {
		zpool_close(zhp);
		return (-1);
	}

	zfs_mark_vdev(pool_guid, vd, &loaded);

	zpool_close(zhp);

	return (0);
}