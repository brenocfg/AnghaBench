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
struct TYPE_6__ {int /*<<< orphan*/  se_name; } ;
typedef  TYPE_1__ zfs_snapentry_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  RW_WRITE_HELD (int /*<<< orphan*/ *) ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_strdup (char*) ; 
 int /*<<< orphan*/  kmem_strfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_snapshot_lock ; 
 int /*<<< orphan*/  zfsctl_snapshot_add (TYPE_1__*) ; 
 TYPE_1__* zfsctl_snapshot_find_by_name (char*) ; 
 int /*<<< orphan*/  zfsctl_snapshot_rele (TYPE_1__*) ; 
 int /*<<< orphan*/  zfsctl_snapshot_remove (TYPE_1__*) ; 

__attribute__((used)) static int
zfsctl_snapshot_rename(char *old_snapname, char *new_snapname)
{
	zfs_snapentry_t *se;

	ASSERT(RW_WRITE_HELD(&zfs_snapshot_lock));

	se = zfsctl_snapshot_find_by_name(old_snapname);
	if (se == NULL)
		return (SET_ERROR(ENOENT));

	zfsctl_snapshot_remove(se);
	kmem_strfree(se->se_name);
	se->se_name = kmem_strdup(new_snapname);
	zfsctl_snapshot_add(se);
	zfsctl_snapshot_rele(se);

	return (0);
}