#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {void* vfs_nbmand; scalar_t__ vfs_do_nbmand; void* vfs_relatime; scalar_t__ vfs_do_relatime; void* vfs_atime; scalar_t__ vfs_do_atime; void* vfs_xattr; scalar_t__ vfs_do_xattr; void* vfs_devices; scalar_t__ vfs_do_devices; void* vfs_exec; scalar_t__ vfs_do_exec; void* vfs_setuid; scalar_t__ vfs_do_setuid; void* vfs_readonly; void* vfs_do_readonly; int /*<<< orphan*/ * z_os; struct TYPE_22__* vfs_data; } ;
typedef  TYPE_1__ zfsvfs_t ;
typedef  TYPE_1__ vfs_t ;
struct dsl_dataset {int dummy; } ;
typedef  int /*<<< orphan*/  objset_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_1__*) ; 
 void* B_TRUE ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  ZFS_PROP_ACLINHERIT ; 
 int /*<<< orphan*/  ZFS_PROP_ACLTYPE ; 
 int /*<<< orphan*/  ZFS_PROP_ATIME ; 
 int /*<<< orphan*/  ZFS_PROP_DEVICES ; 
 int /*<<< orphan*/  ZFS_PROP_EXEC ; 
 int /*<<< orphan*/  ZFS_PROP_NBMAND ; 
 int /*<<< orphan*/  ZFS_PROP_READONLY ; 
 int /*<<< orphan*/  ZFS_PROP_RECORDSIZE ; 
 int /*<<< orphan*/  ZFS_PROP_RELATIME ; 
 int /*<<< orphan*/  ZFS_PROP_SETUID ; 
 int /*<<< orphan*/  ZFS_PROP_SNAPDIR ; 
 int /*<<< orphan*/  ZFS_PROP_VSCAN ; 
 int /*<<< orphan*/  ZFS_PROP_XATTR ; 
 int /*<<< orphan*/  acl_inherit_changed_cb (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  acltype_changed_cb (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  atime_changed_cb (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  blksz_changed_cb (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  devices_changed_cb (TYPE_1__*,void*) ; 
 struct dsl_dataset* dmu_objset_ds (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_objset_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_objset_spa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_pool_config_enter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_pool_config_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dsl_prop_register (struct dsl_dataset*,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (TYPE_1__*,void*),TYPE_1__*) ; 
 int /*<<< orphan*/  dsl_prop_unregister_all (struct dsl_dataset*,TYPE_1__*) ; 
 int /*<<< orphan*/  exec_changed_cb (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  nbmand_changed_cb (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  readonly_changed_cb (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  relatime_changed_cb (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  setuid_changed_cb (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  snapdir_changed_cb (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  spa_writeable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vscan_changed_cb (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  xattr_changed_cb (TYPE_1__*,void*) ; 
 scalar_t__ zfs_is_readonly (TYPE_1__*) ; 
 int /*<<< orphan*/  zfs_prop_to_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_register_callbacks(vfs_t *vfsp)
{
	struct dsl_dataset *ds = NULL;
	objset_t *os = NULL;
	zfsvfs_t *zfsvfs = NULL;
	int error = 0;

	ASSERT(vfsp);
	zfsvfs = vfsp->vfs_data;
	ASSERT(zfsvfs);
	os = zfsvfs->z_os;

	/*
	 * The act of registering our callbacks will destroy any mount
	 * options we may have.  In order to enable temporary overrides
	 * of mount options, we stash away the current values and
	 * restore them after we register the callbacks.
	 */
	if (zfs_is_readonly(zfsvfs) || !spa_writeable(dmu_objset_spa(os))) {
		vfsp->vfs_do_readonly = B_TRUE;
		vfsp->vfs_readonly = B_TRUE;
	}

	/*
	 * Register property callbacks.
	 *
	 * It would probably be fine to just check for i/o error from
	 * the first prop_register(), but I guess I like to go
	 * overboard...
	 */
	ds = dmu_objset_ds(os);
	dsl_pool_config_enter(dmu_objset_pool(os), FTAG);
	error = dsl_prop_register(ds,
	    zfs_prop_to_name(ZFS_PROP_ATIME), atime_changed_cb, zfsvfs);
	error = error ? error : dsl_prop_register(ds,
	    zfs_prop_to_name(ZFS_PROP_RELATIME), relatime_changed_cb, zfsvfs);
	error = error ? error : dsl_prop_register(ds,
	    zfs_prop_to_name(ZFS_PROP_XATTR), xattr_changed_cb, zfsvfs);
	error = error ? error : dsl_prop_register(ds,
	    zfs_prop_to_name(ZFS_PROP_RECORDSIZE), blksz_changed_cb, zfsvfs);
	error = error ? error : dsl_prop_register(ds,
	    zfs_prop_to_name(ZFS_PROP_READONLY), readonly_changed_cb, zfsvfs);
	error = error ? error : dsl_prop_register(ds,
	    zfs_prop_to_name(ZFS_PROP_DEVICES), devices_changed_cb, zfsvfs);
	error = error ? error : dsl_prop_register(ds,
	    zfs_prop_to_name(ZFS_PROP_SETUID), setuid_changed_cb, zfsvfs);
	error = error ? error : dsl_prop_register(ds,
	    zfs_prop_to_name(ZFS_PROP_EXEC), exec_changed_cb, zfsvfs);
	error = error ? error : dsl_prop_register(ds,
	    zfs_prop_to_name(ZFS_PROP_SNAPDIR), snapdir_changed_cb, zfsvfs);
	error = error ? error : dsl_prop_register(ds,
	    zfs_prop_to_name(ZFS_PROP_ACLTYPE), acltype_changed_cb, zfsvfs);
	error = error ? error : dsl_prop_register(ds,
	    zfs_prop_to_name(ZFS_PROP_ACLINHERIT), acl_inherit_changed_cb,
	    zfsvfs);
	error = error ? error : dsl_prop_register(ds,
	    zfs_prop_to_name(ZFS_PROP_VSCAN), vscan_changed_cb, zfsvfs);
	error = error ? error : dsl_prop_register(ds,
	    zfs_prop_to_name(ZFS_PROP_NBMAND), nbmand_changed_cb, zfsvfs);
	dsl_pool_config_exit(dmu_objset_pool(os), FTAG);
	if (error)
		goto unregister;

	/*
	 * Invoke our callbacks to restore temporary mount options.
	 */
	if (vfsp->vfs_do_readonly)
		readonly_changed_cb(zfsvfs, vfsp->vfs_readonly);
	if (vfsp->vfs_do_setuid)
		setuid_changed_cb(zfsvfs, vfsp->vfs_setuid);
	if (vfsp->vfs_do_exec)
		exec_changed_cb(zfsvfs, vfsp->vfs_exec);
	if (vfsp->vfs_do_devices)
		devices_changed_cb(zfsvfs, vfsp->vfs_devices);
	if (vfsp->vfs_do_xattr)
		xattr_changed_cb(zfsvfs, vfsp->vfs_xattr);
	if (vfsp->vfs_do_atime)
		atime_changed_cb(zfsvfs, vfsp->vfs_atime);
	if (vfsp->vfs_do_relatime)
		relatime_changed_cb(zfsvfs, vfsp->vfs_relatime);
	if (vfsp->vfs_do_nbmand)
		nbmand_changed_cb(zfsvfs, vfsp->vfs_nbmand);

	return (0);

unregister:
	dsl_prop_unregister_all(ds, zfsvfs);
	return (error);
}