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
struct TYPE_3__ {int /*<<< orphan*/  zc_cleanup_fd; int /*<<< orphan*/  zc_value; int /*<<< orphan*/  zc_name; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
typedef  int /*<<< orphan*/  minor_t ;

/* Variables and functions */
 scalar_t__ ddi_get_lbolt64 () ; 
 int dsl_dataset_snapshot_tmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 char* kmem_asprintf (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  kmem_strfree (char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int zfs_onexit_fd_hold (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_onexit_fd_rele (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_ioc_tmp_snapshot(zfs_cmd_t *zc)
{
	char *snap_name;
	char *hold_name;
	int error;
	minor_t minor;

	error = zfs_onexit_fd_hold(zc->zc_cleanup_fd, &minor);
	if (error != 0)
		return (error);

	snap_name = kmem_asprintf("%s-%016llx", zc->zc_value,
	    (u_longlong_t)ddi_get_lbolt64());
	hold_name = kmem_asprintf("%%%s", zc->zc_value);

	error = dsl_dataset_snapshot_tmp(zc->zc_name, snap_name, minor,
	    hold_name);
	if (error == 0)
		(void) strlcpy(zc->zc_value, snap_name,
		    sizeof (zc->zc_value));
	kmem_strfree(snap_name);
	kmem_strfree(hold_name);
	zfs_onexit_fd_rele(zc->zc_cleanup_fd);
	return (error);
}