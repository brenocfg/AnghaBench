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
struct TYPE_4__ {int /*<<< orphan*/  zfs_hdl; int /*<<< orphan*/  zfs_name; } ;
typedef  TYPE_1__ zfs_handle_t ;
struct destroydata {char* snapname; int /*<<< orphan*/  nvl; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  dgettext (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify (int) ; 
 int /*<<< orphan*/  zfs_check_snap_cb (int /*<<< orphan*/ ,struct destroydata*) ; 
 int zfs_destroy_snaps_nvl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_handle_dup (TYPE_1__*) ; 
 int zfs_standard_error_fmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

int
zfs_destroy_snaps(zfs_handle_t *zhp, char *snapname, boolean_t defer)
{
	int ret;
	struct destroydata dd = { 0 };

	dd.snapname = snapname;
	verify(nvlist_alloc(&dd.nvl, NV_UNIQUE_NAME, 0) == 0);
	(void) zfs_check_snap_cb(zfs_handle_dup(zhp), &dd);

	if (nvlist_empty(dd.nvl)) {
		ret = zfs_standard_error_fmt(zhp->zfs_hdl, ENOENT,
		    dgettext(TEXT_DOMAIN, "cannot destroy '%s@%s'"),
		    zhp->zfs_name, snapname);
	} else {
		ret = zfs_destroy_snaps_nvl(zhp->zfs_hdl, dd.nvl, defer);
	}
	nvlist_free(dd.nvl);
	return (ret);
}