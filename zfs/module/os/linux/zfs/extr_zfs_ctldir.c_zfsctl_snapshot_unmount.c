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
struct TYPE_4__ {char* se_path; } ;
typedef  TYPE_1__ zfs_snapentry_t ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  ENOENT ; 
 int MNT_FORCE ; 
 int /*<<< orphan*/  RW_READER ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UMH_WAIT_PROC ; 
 int call_usermodehelper (char*,char**,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,char*) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_snapshot_lock ; 
 TYPE_1__* zfsctl_snapshot_find_by_name (char*) ; 
 int /*<<< orphan*/  zfsctl_snapshot_rele (TYPE_1__*) ; 

int
zfsctl_snapshot_unmount(char *snapname, int flags)
{
	char *argv[] = { "/usr/bin/env", "umount", "-t", "zfs", "-n", NULL,
	    NULL };
	char *envp[] = { NULL };
	zfs_snapentry_t *se;
	int error;

	rw_enter(&zfs_snapshot_lock, RW_READER);
	if ((se = zfsctl_snapshot_find_by_name(snapname)) == NULL) {
		rw_exit(&zfs_snapshot_lock);
		return (SET_ERROR(ENOENT));
	}
	rw_exit(&zfs_snapshot_lock);

	if (flags & MNT_FORCE)
		argv[4] = "-fn";
	argv[5] = se->se_path;
	dprintf("unmount; path=%s\n", se->se_path);
	error = call_usermodehelper(argv[0], argv, envp, UMH_WAIT_PROC);
	zfsctl_snapshot_rele(se);


	/*
	 * The umount system utility will return 256 on error.  We must
	 * assume this error is because the file system is busy so it is
	 * converted to the more sensible EBUSY.
	 */
	if (error)
		error = SET_ERROR(EBUSY);

	return (error);
}