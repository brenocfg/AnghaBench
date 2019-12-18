#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int (* zfs_iter_f ) (TYPE_1__*,void*) ;
struct TYPE_16__ {scalar_t__ zfs_type; int /*<<< orphan*/  zfs_hdl; } ;
typedef  TYPE_1__ zfs_handle_t ;
struct TYPE_17__ {char* member_0; scalar_t__ zc_simple; } ;
typedef  TYPE_3__ zfs_cmd_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  SNAP_ITER_MAX_TXG ; 
 int /*<<< orphan*/  SNAP_ITER_MIN_TXG ; 
 int /*<<< orphan*/  ZFS_IOC_SNAPSHOT_LIST_NEXT ; 
 scalar_t__ ZFS_TYPE_BOOKMARK ; 
 scalar_t__ ZFS_TYPE_SNAPSHOT ; 
 int /*<<< orphan*/  fnvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* make_dataset_handle_zc (int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_1__* make_dataset_simple_handle_zc (TYPE_1__*,TYPE_3__*) ; 
 scalar_t__ zcmd_alloc_dst_nvlist (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zcmd_free_nvlists (TYPE_3__*) ; 
 scalar_t__ zcmd_write_src_nvlist (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int zfs_do_list_ioctl (TYPE_1__*,int /*<<< orphan*/ ,TYPE_3__*) ; 

int
zfs_iter_snapshots(zfs_handle_t *zhp, boolean_t simple, zfs_iter_f func,
    void *data, uint64_t min_txg, uint64_t max_txg)
{
	zfs_cmd_t zc = {"\0"};
	zfs_handle_t *nzhp;
	int ret;
	nvlist_t *range_nvl = NULL;

	if (zhp->zfs_type == ZFS_TYPE_SNAPSHOT ||
	    zhp->zfs_type == ZFS_TYPE_BOOKMARK)
		return (0);

	zc.zc_simple = simple;

	if (zcmd_alloc_dst_nvlist(zhp->zfs_hdl, &zc, 0) != 0)
		return (-1);

	if (min_txg != 0) {
		range_nvl = fnvlist_alloc();
		fnvlist_add_uint64(range_nvl, SNAP_ITER_MIN_TXG, min_txg);
	}
	if (max_txg != 0) {
		if (range_nvl == NULL)
			range_nvl = fnvlist_alloc();
		fnvlist_add_uint64(range_nvl, SNAP_ITER_MAX_TXG, max_txg);
	}

	if (range_nvl != NULL &&
	    zcmd_write_src_nvlist(zhp->zfs_hdl, &zc, range_nvl) != 0) {
		zcmd_free_nvlists(&zc);
		fnvlist_free(range_nvl);
		return (-1);
	}

	while ((ret = zfs_do_list_ioctl(zhp, ZFS_IOC_SNAPSHOT_LIST_NEXT,
	    &zc)) == 0) {

		if (simple)
			nzhp = make_dataset_simple_handle_zc(zhp, &zc);
		else
			nzhp = make_dataset_handle_zc(zhp->zfs_hdl, &zc);
		if (nzhp == NULL)
			continue;

		if ((ret = func(nzhp, data)) != 0) {
			zcmd_free_nvlists(&zc);
			fnvlist_free(range_nvl);
			return (ret);
		}
	}
	zcmd_free_nvlists(&zc);
	fnvlist_free(range_nvl);
	return ((ret < 0) ? ret : 0);
}