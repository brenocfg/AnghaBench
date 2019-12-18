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
 int /*<<< orphan*/  DMU_OST_ZFS ; 
 int /*<<< orphan*/  dmu_objset_register_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_filesystem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_space_delta_cb ; 
 int /*<<< orphan*/  zfs_znode_init () ; 
 int /*<<< orphan*/  zfsctl_init () ; 
 int /*<<< orphan*/  zpl_fs_type ; 

void
zfs_init(void)
{
	zfsctl_init();
	zfs_znode_init();
	dmu_objset_register_type(DMU_OST_ZFS, zfs_space_delta_cb);
	register_filesystem(&zpl_fs_type);
}