#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ zfs_prop_t ;
struct TYPE_21__ {scalar_t__ zfs_type; int /*<<< orphan*/  zfs_name; int /*<<< orphan*/  zfs_hdl; } ;
typedef  TYPE_2__ zfs_handle_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_22__ {int cb_force; scalar_t__ cb_create; scalar_t__ cb_error; int /*<<< orphan*/  cb_target; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ rollback_data_t ;
typedef  int /*<<< orphan*/  errbuf ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
#define  EEXIST 130 
#define  EINVAL 129 
#define  ESRCH 128 
 int /*<<< orphan*/  EZFS_BADTYPE ; 
 int /*<<< orphan*/  EZFS_EXISTS ; 
 int /*<<< orphan*/  EZFS_NOENT ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 TYPE_1__ ZFS_PROP_CREATETXG ; 
 TYPE_1__ ZFS_PROP_VOLSIZE ; 
 scalar_t__ ZFS_TYPE_FILESYSTEM ; 
 scalar_t__ ZFS_TYPE_VOLUME ; 
 int /*<<< orphan*/  assert (int) ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int lzc_rollback_to (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* make_dataset_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rollback_destroy ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_close (TYPE_2__*) ; 
 int /*<<< orphan*/  zfs_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  zfs_iter_bookmarks (TYPE_2__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  zfs_iter_snapshots (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_prop_get_int (TYPE_2__*,TYPE_1__) ; 
 int zfs_prop_set_int (TYPE_2__*,TYPE_1__,scalar_t__) ; 
 int /*<<< orphan*/  zfs_standard_error (int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ zfs_which_resv_prop (TYPE_2__*,TYPE_1__*) ; 

int
zfs_rollback(zfs_handle_t *zhp, zfs_handle_t *snap, boolean_t force)
{
	rollback_data_t cb = { 0 };
	int err;
	boolean_t restore_resv = 0;
	uint64_t old_volsize = 0, new_volsize;
	zfs_prop_t resv_prop = { 0 };
	uint64_t min_txg = 0;

	assert(zhp->zfs_type == ZFS_TYPE_FILESYSTEM ||
	    zhp->zfs_type == ZFS_TYPE_VOLUME);

	/*
	 * Destroy all recent snapshots and their dependents.
	 */
	cb.cb_force = force;
	cb.cb_target = snap->zfs_name;
	cb.cb_create = zfs_prop_get_int(snap, ZFS_PROP_CREATETXG);

	if (cb.cb_create > 0)
		min_txg = cb.cb_create;

	(void) zfs_iter_snapshots(zhp, B_FALSE, rollback_destroy, &cb,
	    min_txg, 0);

	(void) zfs_iter_bookmarks(zhp, rollback_destroy, &cb);

	if (cb.cb_error)
		return (-1);

	/*
	 * Now that we have verified that the snapshot is the latest,
	 * rollback to the given snapshot.
	 */

	if (zhp->zfs_type == ZFS_TYPE_VOLUME) {
		if (zfs_which_resv_prop(zhp, &resv_prop) < 0)
			return (-1);
		old_volsize = zfs_prop_get_int(zhp, ZFS_PROP_VOLSIZE);
		restore_resv =
		    (old_volsize == zfs_prop_get_int(zhp, resv_prop));
	}

	/*
	 * Pass both the filesystem and the wanted snapshot names,
	 * we would get an error back if the snapshot is destroyed or
	 * a new snapshot is created before this request is processed.
	 */
	err = lzc_rollback_to(zhp->zfs_name, snap->zfs_name);
	if (err != 0) {
		char errbuf[1024];

		(void) snprintf(errbuf, sizeof (errbuf),
		    dgettext(TEXT_DOMAIN, "cannot rollback '%s'"),
		    zhp->zfs_name);
		switch (err) {
		case EEXIST:
			zfs_error_aux(zhp->zfs_hdl, dgettext(TEXT_DOMAIN,
			    "there is a snapshot or bookmark more recent "
			    "than '%s'"), snap->zfs_name);
			(void) zfs_error(zhp->zfs_hdl, EZFS_EXISTS, errbuf);
			break;
		case ESRCH:
			zfs_error_aux(zhp->zfs_hdl, dgettext(TEXT_DOMAIN,
			    "'%s' is not found among snapshots of '%s'"),
			    snap->zfs_name, zhp->zfs_name);
			(void) zfs_error(zhp->zfs_hdl, EZFS_NOENT, errbuf);
			break;
		case EINVAL:
			(void) zfs_error(zhp->zfs_hdl, EZFS_BADTYPE, errbuf);
			break;
		default:
			(void) zfs_standard_error(zhp->zfs_hdl, err, errbuf);
		}
		return (err);
	}

	/*
	 * For volumes, if the pre-rollback volsize matched the pre-
	 * rollback reservation and the volsize has changed then set
	 * the reservation property to the post-rollback volsize.
	 * Make a new handle since the rollback closed the dataset.
	 */
	if ((zhp->zfs_type == ZFS_TYPE_VOLUME) &&
	    (zhp = make_dataset_handle(zhp->zfs_hdl, zhp->zfs_name))) {
		if (restore_resv) {
			new_volsize = zfs_prop_get_int(zhp, ZFS_PROP_VOLSIZE);
			if (old_volsize != new_volsize)
				err = zfs_prop_set_int(zhp, resv_prop,
				    new_volsize);
		}
		zfs_close(zhp);
	}
	return (err);
}