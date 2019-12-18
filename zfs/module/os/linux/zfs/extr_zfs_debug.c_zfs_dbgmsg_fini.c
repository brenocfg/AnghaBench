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
 int /*<<< orphan*/  procfs_list_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  procfs_list_uninstall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_dbgmsg_purge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_dbgmsgs ; 

void
zfs_dbgmsg_fini(void)
{
	procfs_list_uninstall(&zfs_dbgmsgs);
	zfs_dbgmsg_purge(0);

	/*
	 * TODO - decide how to make this permanent
	 */
#ifdef _KERNEL
	procfs_list_destroy(&zfs_dbgmsgs);
#endif
}