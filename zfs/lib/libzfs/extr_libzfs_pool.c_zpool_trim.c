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
struct TYPE_6__ {int /*<<< orphan*/  zpool_hdl; int /*<<< orphan*/  zpool_name; } ;
typedef  TYPE_1__ zpool_handle_t ;
struct TYPE_7__ {int /*<<< orphan*/  secure; scalar_t__ fullpool; int /*<<< orphan*/  rate; } ;
typedef  TYPE_2__ trimflags_t ;
typedef  int /*<<< orphan*/  pool_trim_func_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  msg ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ EZFS_TRIM_NOTSUP ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  ZPOOL_TRIM_VDEVS ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fnvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvpair_value_int64 (int /*<<< orphan*/ *) ; 
 int lzc_trim (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,char*,char**) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*) ; 
 int /*<<< orphan*/  verify (int /*<<< orphan*/ ) ; 
 scalar_t__ xlate_trim_err (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_error_fmt (int /*<<< orphan*/ ,scalar_t__,char*,char*) ; 
 int zpool_standard_error (int /*<<< orphan*/ ,int,char*) ; 
 int zpool_translate_vdev_guids (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

int
zpool_trim(zpool_handle_t *zhp, pool_trim_func_t cmd_type, nvlist_t *vds,
    trimflags_t *trim_flags)
{
	char msg[1024];
	int err;

	nvlist_t *vdev_guids = fnvlist_alloc();
	nvlist_t *guids_to_paths = fnvlist_alloc();
	nvlist_t *vd_errlist = NULL;
	nvlist_t *errlist;
	nvpair_t *elem;

	err = zpool_translate_vdev_guids(zhp, vds, vdev_guids,
	    guids_to_paths, &vd_errlist);
	if (err == 0) {
		err = lzc_trim(zhp->zpool_name, cmd_type, trim_flags->rate,
		    trim_flags->secure, vdev_guids, &errlist);
		if (err == 0) {
			fnvlist_free(vdev_guids);
			fnvlist_free(guids_to_paths);
			return (0);
		}

		if (errlist != NULL) {
			vd_errlist = fnvlist_lookup_nvlist(errlist,
			    ZPOOL_TRIM_VDEVS);
		}

		(void) snprintf(msg, sizeof (msg),
		    dgettext(TEXT_DOMAIN, "operation failed"));
	} else {
		verify(vd_errlist != NULL);
	}

	for (elem = nvlist_next_nvpair(vd_errlist, NULL);
	    elem != NULL; elem = nvlist_next_nvpair(vd_errlist, elem)) {
		int64_t vd_error = xlate_trim_err(fnvpair_value_int64(elem));
		char *path;

		/*
		 * If only the pool was specified, and it was not a secure
		 * trim then suppress warnings for individual vdevs which
		 * do not support trimming.
		 */
		if (vd_error == EZFS_TRIM_NOTSUP &&
		    trim_flags->fullpool &&
		    !trim_flags->secure) {
			continue;
		}

		if (nvlist_lookup_string(guids_to_paths, nvpair_name(elem),
		    &path) != 0)
			path = nvpair_name(elem);

		(void) zfs_error_fmt(zhp->zpool_hdl, vd_error,
		    "cannot trim '%s'", path);
	}

	fnvlist_free(vdev_guids);
	fnvlist_free(guids_to_paths);

	if (vd_errlist != NULL) {
		fnvlist_free(vd_errlist);
		return (-1);
	}

	return (zpool_standard_error(zhp->zpool_hdl, err, msg));
}