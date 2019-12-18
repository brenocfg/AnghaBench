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
struct TYPE_6__ {int /*<<< orphan*/  se_objsetid; int /*<<< orphan*/ * se_spa; } ;
typedef  TYPE_1__ zfs_snapentry_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RW_LOCK_HELD (int /*<<< orphan*/ *) ; 
 TYPE_1__* avl_find (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_snapshot_lock ; 
 int /*<<< orphan*/  zfs_snapshots_by_objsetid ; 
 int /*<<< orphan*/  zfsctl_snapshot_hold (TYPE_1__*) ; 

__attribute__((used)) static zfs_snapentry_t *
zfsctl_snapshot_find_by_objsetid(spa_t *spa, uint64_t objsetid)
{
	zfs_snapentry_t *se, search;

	ASSERT(RW_LOCK_HELD(&zfs_snapshot_lock));

	search.se_spa = spa;
	search.se_objsetid = objsetid;
	se = avl_find(&zfs_snapshots_by_objsetid, &search, NULL);
	if (se)
		zfsctl_snapshot_hold(se);

	return (se);
}