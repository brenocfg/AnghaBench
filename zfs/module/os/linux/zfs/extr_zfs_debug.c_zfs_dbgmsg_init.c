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
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  procfs_list_install (char*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zdm_node ; 
 int /*<<< orphan*/  zfs_dbgmsg_clear ; 
 int /*<<< orphan*/  zfs_dbgmsg_show ; 
 int /*<<< orphan*/  zfs_dbgmsg_show_header ; 
 int /*<<< orphan*/  zfs_dbgmsg_t ; 
 int /*<<< orphan*/  zfs_dbgmsgs ; 

void
zfs_dbgmsg_init(void)
{
	procfs_list_install("zfs",
	    "dbgmsg",
	    0600,
	    &zfs_dbgmsgs,
	    zfs_dbgmsg_show,
	    zfs_dbgmsg_show_header,
	    zfs_dbgmsg_clear,
	    offsetof(zfs_dbgmsg_t, zdm_node));
}