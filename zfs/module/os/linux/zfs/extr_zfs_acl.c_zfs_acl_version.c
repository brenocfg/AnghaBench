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
 int ZFS_ACL_VERSION_FUID ; 
 int ZFS_ACL_VERSION_INITIAL ; 
 int ZPL_VERSION_FUID ; 

__attribute__((used)) static int
zfs_acl_version(int version)
{
	if (version < ZPL_VERSION_FUID)
		return (ZFS_ACL_VERSION_INITIAL);
	else
		return (ZFS_ACL_VERSION_FUID);
}