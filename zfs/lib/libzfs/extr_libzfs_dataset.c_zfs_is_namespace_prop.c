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
typedef  int zfs_prop_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
#define  ZFS_PROP_ATIME 135 
#define  ZFS_PROP_DEVICES 134 
#define  ZFS_PROP_EXEC 133 
#define  ZFS_PROP_NBMAND 132 
#define  ZFS_PROP_READONLY 131 
#define  ZFS_PROP_RELATIME 130 
#define  ZFS_PROP_SETUID 129 
#define  ZFS_PROP_XATTR 128 

__attribute__((used)) static boolean_t
zfs_is_namespace_prop(zfs_prop_t prop)
{
	switch (prop) {

	case ZFS_PROP_ATIME:
	case ZFS_PROP_RELATIME:
	case ZFS_PROP_DEVICES:
	case ZFS_PROP_EXEC:
	case ZFS_PROP_SETUID:
	case ZFS_PROP_READONLY:
	case ZFS_PROP_XATTR:
	case ZFS_PROP_NBMAND:
		return (B_TRUE);

	default:
		return (B_FALSE);
	}
}