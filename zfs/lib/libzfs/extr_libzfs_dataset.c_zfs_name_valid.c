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
typedef  scalar_t__ zfs_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 scalar_t__ ZFS_TYPE_POOL ; 
 int zfs_validate_name (int /*<<< orphan*/ *,char const*,scalar_t__,int /*<<< orphan*/ ) ; 
 int zpool_name_valid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 

int
zfs_name_valid(const char *name, zfs_type_t type)
{
	if (type == ZFS_TYPE_POOL)
		return (zpool_name_valid(NULL, B_FALSE, name));
	return (zfs_validate_name(NULL, name, type, B_FALSE));
}