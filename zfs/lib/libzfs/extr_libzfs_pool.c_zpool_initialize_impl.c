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
struct TYPE_4__ {int /*<<< orphan*/  zpool_hdl; int /*<<< orphan*/  zpool_name; } ;
typedef  TYPE_1__ zpool_handle_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  pool_initialize_func_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  ZPOOL_INITIALIZE_VDEVS ; 
 int /*<<< orphan*/  ZPOOL_WAIT_INITIALIZE ; 
 int /*<<< orphan*/  dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fnvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvpair_value_int64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvpair_value_uint64 (int /*<<< orphan*/ *) ; 
 int lzc_initialize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int lzc_wait_tag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,char*,char**) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xlate_init_err (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_error_fmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  zpool_standard_error (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpool_standard_error_fmt (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*) ; 
 int zpool_translate_vdev_guids (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

int
zpool_initialize_impl(zpool_handle_t *zhp, pool_initialize_func_t cmd_type,
    nvlist_t *vds, boolean_t wait)
{
	int err;

	nvlist_t *vdev_guids = fnvlist_alloc();
	nvlist_t *guids_to_paths = fnvlist_alloc();
	nvlist_t *vd_errlist = NULL;
	nvlist_t *errlist;
	nvpair_t *elem;

	err = zpool_translate_vdev_guids(zhp, vds, vdev_guids,
	    guids_to_paths, &vd_errlist);

	if (err != 0) {
		verify(vd_errlist != NULL);
		goto list_errors;
	}

	err = lzc_initialize(zhp->zpool_name, cmd_type,
	    vdev_guids, &errlist);

	if (err != 0) {
		if (errlist != NULL) {
			vd_errlist = fnvlist_lookup_nvlist(errlist,
			    ZPOOL_INITIALIZE_VDEVS);
			goto list_errors;
		}
		(void) zpool_standard_error(zhp->zpool_hdl, err,
		    dgettext(TEXT_DOMAIN, "operation failed"));
		goto out;
	}

	if (wait) {
		for (elem = nvlist_next_nvpair(vdev_guids, NULL); elem != NULL;
		    elem = nvlist_next_nvpair(vdev_guids, elem)) {

			uint64_t guid = fnvpair_value_uint64(elem);

			err = lzc_wait_tag(zhp->zpool_name,
			    ZPOOL_WAIT_INITIALIZE, guid, NULL);
			if (err != 0) {
				(void) zpool_standard_error_fmt(zhp->zpool_hdl,
				    err, dgettext(TEXT_DOMAIN, "error "
				    "waiting for '%s' to initialize"),
				    nvpair_name(elem));

				goto out;
			}
		}
	}
	goto out;

list_errors:
	for (elem = nvlist_next_nvpair(vd_errlist, NULL); elem != NULL;
	    elem = nvlist_next_nvpair(vd_errlist, elem)) {
		int64_t vd_error = xlate_init_err(fnvpair_value_int64(elem));
		char *path;

		if (nvlist_lookup_string(guids_to_paths, nvpair_name(elem),
		    &path) != 0)
			path = nvpair_name(elem);

		(void) zfs_error_fmt(zhp->zpool_hdl, vd_error,
		    "cannot initialize '%s'", path);
	}

out:
	fnvlist_free(vdev_guids);
	fnvlist_free(guids_to_paths);

	if (vd_errlist != NULL)
		fnvlist_free(vd_errlist);

	return (err == 0 ? 0 : -1);
}