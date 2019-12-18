#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ zc_nvlist_src_size; scalar_t__ zc_name; scalar_t__ zc_simple; int /*<<< orphan*/  zc_obj; int /*<<< orphan*/  zc_cookie; int /*<<< orphan*/  zc_iflags; int /*<<< orphan*/  zc_nvlist_src; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;

/* Variables and functions */
 int EINTR ; 
 int ENOENT ; 
 int ESRCH ; 
 int /*<<< orphan*/  FORREAL ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  JUSTLOOKING ; 
 int SET_ERROR (int) ; 
 int /*<<< orphan*/  SNAP_ITER_MAX_TXG ; 
 int /*<<< orphan*/  SNAP_ITER_MIN_TXG ; 
 scalar_t__ ZFS_MAX_DATASET_NAME_LEN ; 
 int dmu_objset_from_ds (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int dmu_objset_hold (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dmu_objset_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_objset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dmu_snapshot_list_next (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dsl_dataset_hold_obj (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dsl_get_creationtxg (int /*<<< orphan*/ *) ; 
 int get_nvlist (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ issig (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 char* strchr (scalar_t__,char) ; 
 scalar_t__ strlcat (scalar_t__,char*,int) ; 
 scalar_t__ strlen (scalar_t__) ; 
 int zfs_ioc_objset_stats_impl (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_ioc_snapshot_list_next(zfs_cmd_t *zc)
{
	int error;
	objset_t *os, *ossnap;
	dsl_dataset_t *ds;
	uint64_t min_txg = 0, max_txg = 0;

	if (zc->zc_nvlist_src_size != 0) {
		nvlist_t *props = NULL;
		error = get_nvlist(zc->zc_nvlist_src, zc->zc_nvlist_src_size,
		    zc->zc_iflags, &props);
		if (error != 0)
			return (error);
		(void) nvlist_lookup_uint64(props, SNAP_ITER_MIN_TXG,
		    &min_txg);
		(void) nvlist_lookup_uint64(props, SNAP_ITER_MAX_TXG,
		    &max_txg);
		nvlist_free(props);
	}

	error = dmu_objset_hold(zc->zc_name, FTAG, &os);
	if (error != 0) {
		return (error == ENOENT ? ESRCH : error);
	}

	/*
	 * A dataset name of maximum length cannot have any snapshots,
	 * so exit immediately.
	 */
	if (strlcat(zc->zc_name, "@", sizeof (zc->zc_name)) >=
	    ZFS_MAX_DATASET_NAME_LEN) {
		dmu_objset_rele(os, FTAG);
		return (SET_ERROR(ESRCH));
	}

	while (error == 0) {
		if (issig(JUSTLOOKING) && issig(FORREAL)) {
			error = SET_ERROR(EINTR);
			break;
		}

		error = dmu_snapshot_list_next(os,
		    sizeof (zc->zc_name) - strlen(zc->zc_name),
		    zc->zc_name + strlen(zc->zc_name), &zc->zc_obj,
		    &zc->zc_cookie, NULL);
		if (error == ENOENT) {
			error = SET_ERROR(ESRCH);
			break;
		} else if (error != 0) {
			break;
		}

		error = dsl_dataset_hold_obj(dmu_objset_pool(os), zc->zc_obj,
		    FTAG, &ds);
		if (error != 0)
			break;

		if ((min_txg != 0 && dsl_get_creationtxg(ds) < min_txg) ||
		    (max_txg != 0 && dsl_get_creationtxg(ds) > max_txg)) {
			dsl_dataset_rele(ds, FTAG);
			/* undo snapshot name append */
			*(strchr(zc->zc_name, '@') + 1) = '\0';
			/* skip snapshot */
			continue;
		}

		if (zc->zc_simple) {
			dsl_dataset_rele(ds, FTAG);
			break;
		}

		if ((error = dmu_objset_from_ds(ds, &ossnap)) != 0) {
			dsl_dataset_rele(ds, FTAG);
			break;
		}
		if ((error = zfs_ioc_objset_stats_impl(zc, ossnap)) != 0) {
			dsl_dataset_rele(ds, FTAG);
			break;
		}
		dsl_dataset_rele(ds, FTAG);
		break;
	}

	dmu_objset_rele(os, FTAG);
	/* if we failed, undo the @ that we tacked on to zc_name */
	if (error != 0)
		*strchr(zc->zc_name, '@') = '\0';
	return (error);
}