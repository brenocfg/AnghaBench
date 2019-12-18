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
 int /*<<< orphan*/  system_delay_taskq ; 
 int /*<<< orphan*/  system_taskq ; 
 int /*<<< orphan*/  taskq_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_filesystem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_znode_fini () ; 
 int /*<<< orphan*/  zfsctl_fini () ; 
 int /*<<< orphan*/  zpl_fs_type ; 

void
zfs_fini(void)
{
	/*
	 * we don't use outstanding because zpl_posix_acl_free might add more.
	 */
	taskq_wait(system_delay_taskq);
	taskq_wait(system_taskq);
	unregister_filesystem(&zpl_fs_type);
	zfs_znode_fini();
	zfsctl_fini();
}