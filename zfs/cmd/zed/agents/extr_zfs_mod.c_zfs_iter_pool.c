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
typedef  int /*<<< orphan*/  zpool_handle_t ;
struct TYPE_8__ {int /*<<< orphan*/ * uap_zhp; } ;
typedef  TYPE_1__ unavailpool_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_9__ {char* dd_prop; scalar_t__ dd_pool_guid; int dd_found; scalar_t__ dd_vdev_guid; } ;
typedef  TYPE_2__ dev_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
 scalar_t__ VDEV_STATE_DEGRADED ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_POOL_GUID ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_TREE ; 
 scalar_t__ g_enumeration_done ; 
 int /*<<< orphan*/  g_pool_list ; 
 int /*<<< orphan*/  g_tpool ; 
 TYPE_1__* list_head (int /*<<< orphan*/ *) ; 
 TYPE_1__* list_next (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  nvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpool_dispatch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  zed_log_msg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_enable_ds ; 
 int /*<<< orphan*/  zfs_iter_vdev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 scalar_t__ zfs_toplevel_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpool_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zpool_get_config (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpool_get_name (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_iter_pool(zpool_handle_t *zhp, void *data)
{
	nvlist_t *config, *nvl;
	dev_data_t *dp = data;
	uint64_t pool_guid;
	unavailpool_t *pool;

	zed_log_msg(LOG_INFO, "zfs_iter_pool: evaluating vdevs on %s (by %s)",
	    zpool_get_name(zhp), dp->dd_vdev_guid ? "GUID" : dp->dd_prop);

	/*
	 * For each vdev in this pool, look for a match to apply dd_func
	 */
	if ((config = zpool_get_config(zhp, NULL)) != NULL) {
		if (dp->dd_pool_guid == 0 ||
		    (nvlist_lookup_uint64(config, ZPOOL_CONFIG_POOL_GUID,
		    &pool_guid) == 0 && pool_guid == dp->dd_pool_guid)) {
			(void) nvlist_lookup_nvlist(config,
			    ZPOOL_CONFIG_VDEV_TREE, &nvl);
			zfs_iter_vdev(zhp, nvl, data);
		}
	}

	/*
	 * if this pool was originally unavailable,
	 * then enable its datasets asynchronously
	 */
	if (g_enumeration_done)  {
		for (pool = list_head(&g_pool_list); pool != NULL;
		    pool = list_next(&g_pool_list, pool)) {

			if (strcmp(zpool_get_name(zhp),
			    zpool_get_name(pool->uap_zhp)))
				continue;
			if (zfs_toplevel_state(zhp) >= VDEV_STATE_DEGRADED) {
				list_remove(&g_pool_list, pool);
				(void) tpool_dispatch(g_tpool, zfs_enable_ds,
				    pool);
				break;
			}
		}
	}

	zpool_close(zhp);
	return (dp->dd_found);	/* cease iteration after a match */
}