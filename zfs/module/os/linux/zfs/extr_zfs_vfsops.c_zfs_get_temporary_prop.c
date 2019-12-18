#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* z_vfs; } ;
typedef  TYPE_1__ zfsvfs_t ;
typedef  int zfs_prop_t ;
struct TYPE_9__ {scalar_t__ vfs_atime; scalar_t__ vfs_relatime; scalar_t__ vfs_devices; scalar_t__ vfs_exec; scalar_t__ vfs_setuid; scalar_t__ vfs_readonly; scalar_t__ vfs_xattr; scalar_t__ vfs_nbmand; int /*<<< orphan*/  vfs_do_nbmand; int /*<<< orphan*/  vfs_do_xattr; int /*<<< orphan*/  vfs_do_readonly; int /*<<< orphan*/  vfs_do_setuid; int /*<<< orphan*/  vfs_do_exec; int /*<<< orphan*/  vfs_do_devices; int /*<<< orphan*/  vfs_do_relatime; int /*<<< orphan*/  vfs_do_atime; } ;
typedef  TYPE_2__ vfs_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_10__ {int /*<<< orphan*/  os_user_ptr_lock; } ;
typedef  TYPE_3__ objset_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;

/* Variables and functions */
 scalar_t__ DMU_OST_ZFS ; 
 int EINVAL ; 
 int ENOENT ; 
 int ESRCH ; 
#define  ZFS_PROP_ATIME 135 
#define  ZFS_PROP_DEVICES 134 
#define  ZFS_PROP_EXEC 133 
#define  ZFS_PROP_NBMAND 132 
#define  ZFS_PROP_READONLY 131 
#define  ZFS_PROP_RELATIME 130 
#define  ZFS_PROP_SETUID 129 
#define  ZFS_PROP_XATTR 128 
 int dmu_objset_from_ds (int /*<<< orphan*/ *,TYPE_3__**) ; 
 TYPE_1__* dmu_objset_get_user (TYPE_3__*) ; 
 scalar_t__ dmu_objset_type (TYPE_3__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

int
zfs_get_temporary_prop(dsl_dataset_t *ds, zfs_prop_t zfs_prop, uint64_t *val,
    char *setpoint)
{
	int error;
	zfsvfs_t *zfvp;
	vfs_t *vfsp;
	objset_t *os;
	uint64_t tmp = *val;

	error = dmu_objset_from_ds(ds, &os);
	if (error != 0)
		return (error);

	if (dmu_objset_type(os) != DMU_OST_ZFS)
		return (EINVAL);

	mutex_enter(&os->os_user_ptr_lock);
	zfvp = dmu_objset_get_user(os);
	mutex_exit(&os->os_user_ptr_lock);
	if (zfvp == NULL)
		return (ESRCH);

	vfsp = zfvp->z_vfs;

	switch (zfs_prop) {
	case ZFS_PROP_ATIME:
		if (vfsp->vfs_do_atime)
			tmp = vfsp->vfs_atime;
		break;
	case ZFS_PROP_RELATIME:
		if (vfsp->vfs_do_relatime)
			tmp = vfsp->vfs_relatime;
		break;
	case ZFS_PROP_DEVICES:
		if (vfsp->vfs_do_devices)
			tmp = vfsp->vfs_devices;
		break;
	case ZFS_PROP_EXEC:
		if (vfsp->vfs_do_exec)
			tmp = vfsp->vfs_exec;
		break;
	case ZFS_PROP_SETUID:
		if (vfsp->vfs_do_setuid)
			tmp = vfsp->vfs_setuid;
		break;
	case ZFS_PROP_READONLY:
		if (vfsp->vfs_do_readonly)
			tmp = vfsp->vfs_readonly;
		break;
	case ZFS_PROP_XATTR:
		if (vfsp->vfs_do_xattr)
			tmp = vfsp->vfs_xattr;
		break;
	case ZFS_PROP_NBMAND:
		if (vfsp->vfs_do_nbmand)
			tmp = vfsp->vfs_nbmand;
		break;
	default:
		return (ENOENT);
	}

	if (tmp != *val) {
		(void) strcpy(setpoint, "temporary");
		*val = tmp;
	}
	return (0);
}