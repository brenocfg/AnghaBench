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

/* Variables and functions */
 int /*<<< orphan*/  avl_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_snapshot_lock ; 
 int /*<<< orphan*/  zfs_snapshots_by_name ; 
 int /*<<< orphan*/  zfs_snapshots_by_objsetid ; 

void
zfsctl_fini(void)
{
	avl_destroy(&zfs_snapshots_by_name);
	avl_destroy(&zfs_snapshots_by_objsetid);
	rw_destroy(&zfs_snapshot_lock);
}