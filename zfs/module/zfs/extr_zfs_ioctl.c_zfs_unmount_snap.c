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
 int /*<<< orphan*/  MNT_FORCE ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 int /*<<< orphan*/  zfsctl_snapshot_unmount (char*,int /*<<< orphan*/ ) ; 

void
zfs_unmount_snap(const char *snapname)
{
	if (strchr(snapname, '@') == NULL)
		return;

	(void) zfsctl_snapshot_unmount((char *)snapname, MNT_FORCE);
}