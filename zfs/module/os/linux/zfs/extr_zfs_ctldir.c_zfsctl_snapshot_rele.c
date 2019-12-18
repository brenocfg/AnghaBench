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
struct TYPE_4__ {int /*<<< orphan*/  se_refcount; } ;
typedef  TYPE_1__ zfs_snapentry_t ;

/* Variables and functions */
 scalar_t__ zfs_refcount_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfsctl_snapshot_free (TYPE_1__*) ; 

__attribute__((used)) static void
zfsctl_snapshot_rele(zfs_snapentry_t *se)
{
	if (zfs_refcount_remove(&se->se_refcount, NULL) == 0)
		zfsctl_snapshot_free(se);
}