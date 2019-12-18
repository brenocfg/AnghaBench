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
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 scalar_t__ DMU_OST_ZFS ; 
 scalar_t__ dmu_objset_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_get_vfs_flag_unmounted (int /*<<< orphan*/ *) ; 

__attribute__((used)) static boolean_t
dmu_objset_zfs_unmounting(objset_t *os)
{
#ifdef _KERNEL
	if (dmu_objset_type(os) == DMU_OST_ZFS)
		return (zfs_get_vfs_flag_unmounted(os));
#endif
	return (B_FALSE);
}