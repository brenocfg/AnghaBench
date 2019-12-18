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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
struct TYPE_3__ {int /*<<< orphan*/ * cb_zhp; int /*<<< orphan*/  cb_guid; } ;
typedef  TYPE_1__ find_cbdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_TREE ; 
 int /*<<< orphan*/  find_pool ; 
 int /*<<< orphan*/ * find_vdev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  zpool_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zpool_get_config (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zpool_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static zpool_handle_t *
find_by_guid(libzfs_handle_t *zhdl, uint64_t pool_guid, uint64_t vdev_guid,
    nvlist_t **vdevp)
{
	find_cbdata_t cb;
	zpool_handle_t *zhp;
	nvlist_t *config, *nvroot;

	/*
	 * Find the corresponding pool and make sure the vdev still exists.
	 */
	cb.cb_guid = pool_guid;
	if (zpool_iter(zhdl, find_pool, &cb) != 1)
		return (NULL);

	zhp = cb.cb_zhp;
	config = zpool_get_config(zhp, NULL);
	if (nvlist_lookup_nvlist(config, ZPOOL_CONFIG_VDEV_TREE,
	    &nvroot) != 0) {
		zpool_close(zhp);
		return (NULL);
	}

	if (vdev_guid != 0) {
		if ((*vdevp = find_vdev(zhdl, nvroot, vdev_guid)) == NULL) {
			zpool_close(zhp);
			return (NULL);
		}
	}

	return (zhp);
}