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
typedef  int /*<<< orphan*/  zpool_handle_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_3__ {scalar_t__ gs_vdev_guid; int /*<<< orphan*/  gs_pool_guid; } ;
typedef  TYPE_1__ guid_search_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZPOOL_CONFIG_POOL_GUID ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_TREE ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_agent_iter_vdev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  zpool_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zpool_get_config (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_agent_iter_pool(zpool_handle_t *zhp, void *arg)
{
	guid_search_t *gsp = arg;
	nvlist_t *config, *nvl;

	/*
	 * For each vdev in this pool, look for a match by devid
	 */
	if ((config = zpool_get_config(zhp, NULL)) != NULL) {
		if (nvlist_lookup_nvlist(config, ZPOOL_CONFIG_VDEV_TREE,
		    &nvl) == 0) {
			(void) zfs_agent_iter_vdev(zhp, nvl, gsp);
		}
	}
	/*
	 * if a match was found then grab the pool guid
	 */
	if (gsp->gs_vdev_guid) {
		(void) nvlist_lookup_uint64(config, ZPOOL_CONFIG_POOL_GUID,
		    &gsp->gs_pool_guid);
	}

	zpool_close(zhp);
	return (gsp->gs_vdev_guid != 0);
}