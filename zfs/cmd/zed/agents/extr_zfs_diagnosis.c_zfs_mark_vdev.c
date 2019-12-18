#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ zc_pool_guid; scalar_t__ zc_vdev_guid; } ;
struct TYPE_7__ {int /*<<< orphan*/  zc_when; int /*<<< orphan*/  zc_present; TYPE_1__ zc_data; } ;
typedef  TYPE_2__ zfs_case_t ;
typedef  size_t uint_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  er_timeval_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_CHILDREN ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_GUID ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_L2CACHE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_SPARES ; 
 scalar_t__ nvlist_lookup_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ***,size_t*) ; 
 int /*<<< orphan*/  nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 TYPE_2__* uu_list_first (int /*<<< orphan*/ ) ; 
 TYPE_2__* uu_list_next (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  zfs_cases ; 

__attribute__((used)) static void
zfs_mark_vdev(uint64_t pool_guid, nvlist_t *vd, er_timeval_t *loaded)
{
	uint64_t vdev_guid = 0;
	uint_t c, children;
	nvlist_t **child;
	zfs_case_t *zcp;

	(void) nvlist_lookup_uint64(vd, ZPOOL_CONFIG_GUID, &vdev_guid);

	/*
	 * Mark any cases associated with this (pool, vdev) pair.
	 */
	for (zcp = uu_list_first(zfs_cases); zcp != NULL;
	    zcp = uu_list_next(zfs_cases, zcp)) {
		if (zcp->zc_data.zc_pool_guid == pool_guid &&
		    zcp->zc_data.zc_vdev_guid == vdev_guid) {
			zcp->zc_present = B_TRUE;
			zcp->zc_when = *loaded;
		}
	}

	/*
	 * Iterate over all children.
	 */
	if (nvlist_lookup_nvlist_array(vd, ZPOOL_CONFIG_CHILDREN, &child,
	    &children) == 0) {
		for (c = 0; c < children; c++)
			zfs_mark_vdev(pool_guid, child[c], loaded);
	}

	if (nvlist_lookup_nvlist_array(vd, ZPOOL_CONFIG_L2CACHE, &child,
	    &children) == 0) {
		for (c = 0; c < children; c++)
			zfs_mark_vdev(pool_guid, child[c], loaded);
	}

	if (nvlist_lookup_nvlist_array(vd, ZPOOL_CONFIG_SPARES, &child,
	    &children) == 0) {
		for (c = 0; c < children; c++)
			zfs_mark_vdev(pool_guid, child[c], loaded);
	}
}