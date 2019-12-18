#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  procfs_list_t ;
struct TYPE_2__ {int /*<<< orphan*/  pl_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_dbgmsg_purge (int /*<<< orphan*/ ) ; 
 TYPE_1__ zfs_dbgmsgs ; 

__attribute__((used)) static int
zfs_dbgmsg_clear(procfs_list_t *procfs_list)
{
	mutex_enter(&zfs_dbgmsgs.pl_lock);
	zfs_dbgmsg_purge(0);
	mutex_exit(&zfs_dbgmsgs.pl_lock);
	return (0);
}