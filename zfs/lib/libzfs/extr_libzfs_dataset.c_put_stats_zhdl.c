#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * zfs_user_props; int /*<<< orphan*/ * zfs_props; int /*<<< orphan*/  zfs_hdl; int /*<<< orphan*/  zfs_dmustats; } ;
typedef  TYPE_1__ zfs_handle_t ;
struct TYPE_8__ {int /*<<< orphan*/  zc_objset_stats; } ;
typedef  TYPE_2__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * process_user_props (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ zcmd_read_dst_nvlist (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
put_stats_zhdl(zfs_handle_t *zhp, zfs_cmd_t *zc)
{
	nvlist_t *allprops, *userprops;

	zhp->zfs_dmustats = zc->zc_objset_stats; /* structure assignment */

	if (zcmd_read_dst_nvlist(zhp->zfs_hdl, zc, &allprops) != 0) {
		return (-1);
	}

	/*
	 * XXX Why do we store the user props separately, in addition to
	 * storing them in zfs_props?
	 */
	if ((userprops = process_user_props(zhp, allprops)) == NULL) {
		nvlist_free(allprops);
		return (-1);
	}

	nvlist_free(zhp->zfs_props);
	nvlist_free(zhp->zfs_user_props);

	zhp->zfs_props = allprops;
	zhp->zfs_user_props = userprops;

	return (0);
}