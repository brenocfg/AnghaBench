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
struct TYPE_4__ {int /*<<< orphan*/  se_taskqid; } ;
typedef  TYPE_1__ zfs_snapentry_t ;

/* Variables and functions */
 int /*<<< orphan*/  TASKQID_INVALID ; 
 int /*<<< orphan*/  system_delay_taskq ; 
 scalar_t__ taskq_cancel_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfsctl_snapshot_rele (TYPE_1__*) ; 

__attribute__((used)) static void
zfsctl_snapshot_unmount_cancel(zfs_snapentry_t *se)
{
	if (taskq_cancel_id(system_delay_taskq, se->se_taskqid) == 0) {
		se->se_taskqid = TASKQID_INVALID;
		zfsctl_snapshot_rele(se);
	}
}