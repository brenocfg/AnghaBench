#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_snapentry_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_snapshot_lock ; 
 int /*<<< orphan*/ * zfsctl_snapshot_find_by_name (char*) ; 
 int /*<<< orphan*/  zfsctl_snapshot_rele (int /*<<< orphan*/ *) ; 

__attribute__((used)) static boolean_t
zfsctl_snapshot_ismounted(char *snapname)
{
	zfs_snapentry_t *se;
	boolean_t ismounted = B_FALSE;

	rw_enter(&zfs_snapshot_lock, RW_READER);
	if ((se = zfsctl_snapshot_find_by_name(snapname)) != NULL) {
		zfsctl_snapshot_rele(se);
		ismounted = B_TRUE;
	}
	rw_exit(&zfs_snapshot_lock);

	return (ismounted);
}