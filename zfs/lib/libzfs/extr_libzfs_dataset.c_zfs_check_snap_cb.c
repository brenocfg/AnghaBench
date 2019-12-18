#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* zfs_name; } ;
typedef  TYPE_1__ zfs_handle_t ;
struct destroydata {char* snapname; int /*<<< orphan*/  nvl; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int EINVAL ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 scalar_t__ lzc_exists (char*) ; 
 scalar_t__ nvlist_add_boolean (int /*<<< orphan*/ ,char*) ; 
 int snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  verify (int) ; 
 int /*<<< orphan*/  zfs_close (TYPE_1__*) ; 
 int zfs_iter_filesystems (TYPE_1__*,int (*) (TYPE_1__*,void*),struct destroydata*) ; 

__attribute__((used)) static int
zfs_check_snap_cb(zfs_handle_t *zhp, void *arg)
{
	struct destroydata *dd = arg;
	char name[ZFS_MAX_DATASET_NAME_LEN];
	int rv = 0;

	if (snprintf(name, sizeof (name), "%s@%s", zhp->zfs_name,
	    dd->snapname) >= sizeof (name))
		return (EINVAL);

	if (lzc_exists(name))
		verify(nvlist_add_boolean(dd->nvl, name) == 0);

	rv = zfs_iter_filesystems(zhp, zfs_check_snap_cb, dd);
	zfs_close(zhp);
	return (rv);
}