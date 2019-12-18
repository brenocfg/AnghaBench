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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  ZFS_SYSFS_POOL_FEATURES ; 
 int /*<<< orphan*/  zfs_mod_supported (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static boolean_t
zfs_mod_supported_feature(const char *name)
{
	/*
	 * The zfs module spa_feature_table[], whether in-kernel or in
	 * libzpool, always supports all the features. libzfs needs to
	 * query the running module, via sysfs, to determine which
	 * features are supported.
	 */
#if defined(_KERNEL) || defined(LIB_ZPOOL_BUILD)
	return (B_TRUE);
#else
	return (zfs_mod_supported(ZFS_SYSFS_POOL_FEATURES, name));
#endif
}