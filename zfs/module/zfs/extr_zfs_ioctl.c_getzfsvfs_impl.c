#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfsvfs_t ;
struct TYPE_5__ {int /*<<< orphan*/  os_user_ptr_lock; } ;
typedef  TYPE_1__ objset_t ;

/* Variables and functions */
 scalar_t__ DMU_OST_ZFS ; 
 int /*<<< orphan*/  EINVAL ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dmu_objset_get_user (TYPE_1__*) ; 
 scalar_t__ dmu_objset_type (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int zfs_vfs_ref (int /*<<< orphan*/ **) ; 

int
getzfsvfs_impl(objset_t *os, zfsvfs_t **zfvp)
{
	int error = 0;
	if (dmu_objset_type(os) != DMU_OST_ZFS) {
		return (SET_ERROR(EINVAL));
	}

	mutex_enter(&os->os_user_ptr_lock);
	*zfvp = dmu_objset_get_user(os);
	/* bump s_active only when non-zero to prevent umount race */
	error = zfs_vfs_ref(zfvp);
	mutex_exit(&os->os_user_ptr_lock);
	return (error);
}