#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int zlp_rewind; } ;
typedef  TYPE_1__ zpool_load_policy_t ;
struct TYPE_14__ {char const* zpool_name; int zpool_config_size; int /*<<< orphan*/ * zpool_hdl; } ;
typedef  TYPE_2__ zpool_handle_t ;
struct TYPE_15__ {char* member_0; int zc_cookie; int /*<<< orphan*/  zc_name; int /*<<< orphan*/  zc_guid; } ;
typedef  TYPE_3__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ EACCES ; 
 scalar_t__ ENOMEM ; 
 scalar_t__ EPERM ; 
 int /*<<< orphan*/  EZFS_ISSPARE ; 
 int /*<<< orphan*/  EZFS_NODEVICE ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  ZFS_IOC_CLEAR ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_GUID ; 
 int ZPOOL_DO_REWIND ; 
 int ZPOOL_TRY_REWIND ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  verify (int) ; 
 scalar_t__ zcmd_alloc_dst_nvlist (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 scalar_t__ zcmd_expand_dst_nvlist (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  zcmd_free_nvlists (TYPE_3__*) ; 
 int /*<<< orphan*/  zcmd_read_dst_nvlist (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ **) ; 
 scalar_t__ zcmd_write_src_nvlist (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int zfs_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/ * zpool_find_vdev (TYPE_2__*,char const*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpool_get_load_policy (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  zpool_rewind_exclaim (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int zpool_standard_error (int /*<<< orphan*/ *,scalar_t__,char*) ; 

int
zpool_clear(zpool_handle_t *zhp, const char *path, nvlist_t *rewindnvl)
{
	zfs_cmd_t zc = {"\0"};
	char msg[1024];
	nvlist_t *tgt;
	zpool_load_policy_t policy;
	boolean_t avail_spare, l2cache;
	libzfs_handle_t *hdl = zhp->zpool_hdl;
	nvlist_t *nvi = NULL;
	int error;

	if (path)
		(void) snprintf(msg, sizeof (msg),
		    dgettext(TEXT_DOMAIN, "cannot clear errors for %s"),
		    path);
	else
		(void) snprintf(msg, sizeof (msg),
		    dgettext(TEXT_DOMAIN, "cannot clear errors for %s"),
		    zhp->zpool_name);

	(void) strlcpy(zc.zc_name, zhp->zpool_name, sizeof (zc.zc_name));
	if (path) {
		if ((tgt = zpool_find_vdev(zhp, path, &avail_spare,
		    &l2cache, NULL)) == NULL)
			return (zfs_error(hdl, EZFS_NODEVICE, msg));

		/*
		 * Don't allow error clearing for hot spares.  Do allow
		 * error clearing for l2cache devices.
		 */
		if (avail_spare)
			return (zfs_error(hdl, EZFS_ISSPARE, msg));

		verify(nvlist_lookup_uint64(tgt, ZPOOL_CONFIG_GUID,
		    &zc.zc_guid) == 0);
	}

	zpool_get_load_policy(rewindnvl, &policy);
	zc.zc_cookie = policy.zlp_rewind;

	if (zcmd_alloc_dst_nvlist(hdl, &zc, zhp->zpool_config_size * 2) != 0)
		return (-1);

	if (zcmd_write_src_nvlist(hdl, &zc, rewindnvl) != 0)
		return (-1);

	while ((error = zfs_ioctl(hdl, ZFS_IOC_CLEAR, &zc)) != 0 &&
	    errno == ENOMEM) {
		if (zcmd_expand_dst_nvlist(hdl, &zc) != 0) {
			zcmd_free_nvlists(&zc);
			return (-1);
		}
	}

	if (!error || ((policy.zlp_rewind & ZPOOL_TRY_REWIND) &&
	    errno != EPERM && errno != EACCES)) {
		if (policy.zlp_rewind &
		    (ZPOOL_DO_REWIND | ZPOOL_TRY_REWIND)) {
			(void) zcmd_read_dst_nvlist(hdl, &zc, &nvi);
			zpool_rewind_exclaim(hdl, zc.zc_name,
			    ((policy.zlp_rewind & ZPOOL_TRY_REWIND) != 0),
			    nvi);
			nvlist_free(nvi);
		}
		zcmd_free_nvlists(&zc);
		return (0);
	}

	zcmd_free_nvlists(&zc);
	return (zpool_standard_error(hdl, errno, msg));
}