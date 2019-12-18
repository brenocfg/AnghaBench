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
typedef  int /*<<< orphan*/  zfs_handle_t ;
struct TYPE_3__ {scalar_t__ sd_recursive; int /*<<< orphan*/  sd_nvl; int /*<<< orphan*/  sd_snapname; } ;
typedef  TYPE_1__ snap_cbdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_PROP_INCONSISTENT ; 
 int asprintf (char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvlist_add_boolean (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  nomem () ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_get_name (int /*<<< orphan*/ *) ; 
 int zfs_iter_filesystems (int /*<<< orphan*/ *,int (*) (int /*<<< orphan*/ *,void*),TYPE_1__*) ; 
 scalar_t__ zfs_prop_get_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_snapshot_cb(zfs_handle_t *zhp, void *arg)
{
	snap_cbdata_t *sd = arg;
	char *name;
	int rv = 0;
	int error;

	if (sd->sd_recursive &&
	    zfs_prop_get_int(zhp, ZFS_PROP_INCONSISTENT) != 0) {
		zfs_close(zhp);
		return (0);
	}

	error = asprintf(&name, "%s@%s", zfs_get_name(zhp), sd->sd_snapname);
	if (error == -1)
		nomem();
	fnvlist_add_boolean(sd->sd_nvl, name);
	free(name);

	if (sd->sd_recursive)
		rv = zfs_iter_filesystems(zhp, zfs_snapshot_cb, sd);
	zfs_close(zhp);
	return (rv);
}