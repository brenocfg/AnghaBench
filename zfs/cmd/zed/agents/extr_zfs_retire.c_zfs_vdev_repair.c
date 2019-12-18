#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ zrr_pool; scalar_t__ zrr_vdev; struct TYPE_5__* zrr_next; } ;
typedef  TYPE_1__ zfs_retire_repaired_t ;
struct TYPE_6__ {TYPE_1__* zrd_repaired; } ;
typedef  TYPE_2__ zfs_retire_data_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  fmd_hdl_t ;

/* Variables and functions */
 int /*<<< orphan*/  FMD_SLEEP ; 
 int /*<<< orphan*/  FM_EREPORT_PAYLOAD_ZFS_POOL_GUID ; 
 int /*<<< orphan*/  FM_EREPORT_PAYLOAD_ZFS_VDEV_GUID ; 
 TYPE_1__* fmd_hdl_alloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmd_hdl_debug (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__) ; 
 TYPE_2__* fmd_hdl_getspecific (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static void
zfs_vdev_repair(fmd_hdl_t *hdl, nvlist_t *nvl)
{
	zfs_retire_data_t *zdp = fmd_hdl_getspecific(hdl);
	zfs_retire_repaired_t *zrp;
	uint64_t pool_guid, vdev_guid;
	if (nvlist_lookup_uint64(nvl, FM_EREPORT_PAYLOAD_ZFS_POOL_GUID,
	    &pool_guid) != 0 || nvlist_lookup_uint64(nvl,
	    FM_EREPORT_PAYLOAD_ZFS_VDEV_GUID, &vdev_guid) != 0)
		return;

	/*
	 * Before checking the state of the ASRU, go through and see if we've
	 * already made an attempt to repair this ASRU.  This list is cleared
	 * whenever we receive any kind of list event, and is designed to
	 * prevent us from generating a feedback loop when we attempt repairs
	 * against a faulted pool.  The problem is that checking the unusable
	 * state of the ASRU can involve opening the pool, which can post
	 * statechange events but otherwise leave the pool in the faulted
	 * state.  This list allows us to detect when a statechange event is
	 * due to our own request.
	 */
	for (zrp = zdp->zrd_repaired; zrp != NULL; zrp = zrp->zrr_next) {
		if (zrp->zrr_pool == pool_guid &&
		    zrp->zrr_vdev == vdev_guid)
			return;
	}

	zrp = fmd_hdl_alloc(hdl, sizeof (zfs_retire_repaired_t), FMD_SLEEP);
	zrp->zrr_next = zdp->zrd_repaired;
	zrp->zrr_pool = pool_guid;
	zrp->zrr_vdev = vdev_guid;
	zdp->zrd_repaired = zrp;

	fmd_hdl_debug(hdl, "marking repaired vdev %llu on pool %llu",
	    vdev_guid, pool_guid);
}