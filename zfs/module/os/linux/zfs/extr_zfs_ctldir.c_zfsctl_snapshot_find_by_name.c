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
struct TYPE_6__ {char* se_name; } ;
typedef  TYPE_1__ zfs_snapentry_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RW_LOCK_HELD (int /*<<< orphan*/ *) ; 
 TYPE_1__* avl_find (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_snapshot_lock ; 
 int /*<<< orphan*/  zfs_snapshots_by_name ; 
 int /*<<< orphan*/  zfsctl_snapshot_hold (TYPE_1__*) ; 

__attribute__((used)) static zfs_snapentry_t *
zfsctl_snapshot_find_by_name(char *snapname)
{
	zfs_snapentry_t *se, search;

	ASSERT(RW_LOCK_HELD(&zfs_snapshot_lock));

	search.se_name = snapname;
	se = avl_find(&zfs_snapshots_by_name, &search, NULL);
	if (se)
		zfsctl_snapshot_hold(se);

	return (se);
}