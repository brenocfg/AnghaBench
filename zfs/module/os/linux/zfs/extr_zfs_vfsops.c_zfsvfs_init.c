#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ z_version; int z_norm; int z_utf8; scalar_t__ z_case; scalar_t__ z_root; scalar_t__ z_unlinkedobj; scalar_t__ z_userquota_obj; scalar_t__ z_groupquota_obj; scalar_t__ z_projectquota_obj; scalar_t__ z_userobjquota_obj; scalar_t__ z_groupobjquota_obj; scalar_t__ z_projectobjquota_obj; scalar_t__ z_fuid_obj; scalar_t__ z_shares_dir; int /*<<< orphan*/  z_attr_table; int /*<<< orphan*/  z_xattr_sa; scalar_t__ z_use_sa; int /*<<< orphan*/ * z_os; int /*<<< orphan*/  z_use_fuids; void* z_acl_type; int /*<<< orphan*/  z_show_ctldir; int /*<<< orphan*/  z_max_blksz; } ;
typedef  TYPE_1__ zfsvfs_t ;
typedef  void* uint_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
typedef  int /*<<< orphan*/  objset_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_TRUE ; 
 int ENOENT ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  MASTER_NODE_OBJ ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPA_OLD_MAXBLOCKSIZE ; 
 int U8_TEXTPREP_TOUPPER ; 
 int /*<<< orphan*/  USE_FUIDS (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ USE_SA (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ ZFS_CASE_INSENSITIVE ; 
 scalar_t__ ZFS_CASE_MIXED ; 
 int /*<<< orphan*/  ZFS_FUID_TABLES ; 
 int /*<<< orphan*/  ZFS_PROP_ACLTYPE ; 
 int /*<<< orphan*/  ZFS_PROP_CASE ; 
 size_t ZFS_PROP_GROUPOBJQUOTA ; 
 size_t ZFS_PROP_GROUPQUOTA ; 
 int /*<<< orphan*/  ZFS_PROP_NORMALIZE ; 
 size_t ZFS_PROP_PROJECTOBJQUOTA ; 
 size_t ZFS_PROP_PROJECTQUOTA ; 
 size_t ZFS_PROP_USEROBJQUOTA ; 
 size_t ZFS_PROP_USERQUOTA ; 
 int /*<<< orphan*/  ZFS_PROP_UTF8ONLY ; 
 int /*<<< orphan*/  ZFS_PROP_VERSION ; 
 int /*<<< orphan*/  ZFS_PROP_XATTR ; 
 int /*<<< orphan*/  ZFS_ROOT_OBJ ; 
 int /*<<< orphan*/  ZFS_SA_ATTRS ; 
 int /*<<< orphan*/  ZFS_SHARES_DIR ; 
 int /*<<< orphan*/  ZFS_SNAPDIR_VISIBLE ; 
 int /*<<< orphan*/  ZFS_UNLINKED_SET ; 
 scalar_t__ ZFS_XATTR_SA ; 
 int /*<<< orphan*/  ZPL_END ; 
 scalar_t__ ZPL_VERSION_SA ; 
 int /*<<< orphan*/  dmu_objset_spa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sa_register_update_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sa_setup (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ spa_version (int /*<<< orphan*/ ) ; 
 int zap_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,scalar_t__*) ; 
 int /*<<< orphan*/  zfs_attr_table ; 
 int zfs_get_zplprop (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  zfs_sa_upgrade ; 
 int /*<<< orphan*/ * zfs_userquota_prop_prefixes ; 
 scalar_t__ zfs_zpl_version_map (scalar_t__) ; 

__attribute__((used)) static int
zfsvfs_init(zfsvfs_t *zfsvfs, objset_t *os)
{
	int error;
	uint64_t val;

	zfsvfs->z_max_blksz = SPA_OLD_MAXBLOCKSIZE;
	zfsvfs->z_show_ctldir = ZFS_SNAPDIR_VISIBLE;
	zfsvfs->z_os = os;

	error = zfs_get_zplprop(os, ZFS_PROP_VERSION, &zfsvfs->z_version);
	if (error != 0)
		return (error);
	if (zfsvfs->z_version >
	    zfs_zpl_version_map(spa_version(dmu_objset_spa(os)))) {
		(void) printk("Can't mount a version %lld file system "
		    "on a version %lld pool\n. Pool must be upgraded to mount "
		    "this file system.\n", (u_longlong_t)zfsvfs->z_version,
		    (u_longlong_t)spa_version(dmu_objset_spa(os)));
		return (SET_ERROR(ENOTSUP));
	}
	error = zfs_get_zplprop(os, ZFS_PROP_NORMALIZE, &val);
	if (error != 0)
		return (error);
	zfsvfs->z_norm = (int)val;

	error = zfs_get_zplprop(os, ZFS_PROP_UTF8ONLY, &val);
	if (error != 0)
		return (error);
	zfsvfs->z_utf8 = (val != 0);

	error = zfs_get_zplprop(os, ZFS_PROP_CASE, &val);
	if (error != 0)
		return (error);
	zfsvfs->z_case = (uint_t)val;

	if ((error = zfs_get_zplprop(os, ZFS_PROP_ACLTYPE, &val)) != 0)
		return (error);
	zfsvfs->z_acl_type = (uint_t)val;

	/*
	 * Fold case on file systems that are always or sometimes case
	 * insensitive.
	 */
	if (zfsvfs->z_case == ZFS_CASE_INSENSITIVE ||
	    zfsvfs->z_case == ZFS_CASE_MIXED)
		zfsvfs->z_norm |= U8_TEXTPREP_TOUPPER;

	zfsvfs->z_use_fuids = USE_FUIDS(zfsvfs->z_version, zfsvfs->z_os);
	zfsvfs->z_use_sa = USE_SA(zfsvfs->z_version, zfsvfs->z_os);

	uint64_t sa_obj = 0;
	if (zfsvfs->z_use_sa) {
		/* should either have both of these objects or none */
		error = zap_lookup(os, MASTER_NODE_OBJ, ZFS_SA_ATTRS, 8, 1,
		    &sa_obj);
		if (error != 0)
			return (error);

		error = zfs_get_zplprop(os, ZFS_PROP_XATTR, &val);
		if ((error == 0) && (val == ZFS_XATTR_SA))
			zfsvfs->z_xattr_sa = B_TRUE;
	}

	error = zap_lookup(os, MASTER_NODE_OBJ, ZFS_ROOT_OBJ, 8, 1,
	    &zfsvfs->z_root);
	if (error != 0)
		return (error);
	ASSERT(zfsvfs->z_root != 0);

	error = zap_lookup(os, MASTER_NODE_OBJ, ZFS_UNLINKED_SET, 8, 1,
	    &zfsvfs->z_unlinkedobj);
	if (error != 0)
		return (error);

	error = zap_lookup(os, MASTER_NODE_OBJ,
	    zfs_userquota_prop_prefixes[ZFS_PROP_USERQUOTA],
	    8, 1, &zfsvfs->z_userquota_obj);
	if (error == ENOENT)
		zfsvfs->z_userquota_obj = 0;
	else if (error != 0)
		return (error);

	error = zap_lookup(os, MASTER_NODE_OBJ,
	    zfs_userquota_prop_prefixes[ZFS_PROP_GROUPQUOTA],
	    8, 1, &zfsvfs->z_groupquota_obj);
	if (error == ENOENT)
		zfsvfs->z_groupquota_obj = 0;
	else if (error != 0)
		return (error);

	error = zap_lookup(os, MASTER_NODE_OBJ,
	    zfs_userquota_prop_prefixes[ZFS_PROP_PROJECTQUOTA],
	    8, 1, &zfsvfs->z_projectquota_obj);
	if (error == ENOENT)
		zfsvfs->z_projectquota_obj = 0;
	else if (error != 0)
		return (error);

	error = zap_lookup(os, MASTER_NODE_OBJ,
	    zfs_userquota_prop_prefixes[ZFS_PROP_USEROBJQUOTA],
	    8, 1, &zfsvfs->z_userobjquota_obj);
	if (error == ENOENT)
		zfsvfs->z_userobjquota_obj = 0;
	else if (error != 0)
		return (error);

	error = zap_lookup(os, MASTER_NODE_OBJ,
	    zfs_userquota_prop_prefixes[ZFS_PROP_GROUPOBJQUOTA],
	    8, 1, &zfsvfs->z_groupobjquota_obj);
	if (error == ENOENT)
		zfsvfs->z_groupobjquota_obj = 0;
	else if (error != 0)
		return (error);

	error = zap_lookup(os, MASTER_NODE_OBJ,
	    zfs_userquota_prop_prefixes[ZFS_PROP_PROJECTOBJQUOTA],
	    8, 1, &zfsvfs->z_projectobjquota_obj);
	if (error == ENOENT)
		zfsvfs->z_projectobjquota_obj = 0;
	else if (error != 0)
		return (error);

	error = zap_lookup(os, MASTER_NODE_OBJ, ZFS_FUID_TABLES, 8, 1,
	    &zfsvfs->z_fuid_obj);
	if (error == ENOENT)
		zfsvfs->z_fuid_obj = 0;
	else if (error != 0)
		return (error);

	error = zap_lookup(os, MASTER_NODE_OBJ, ZFS_SHARES_DIR, 8, 1,
	    &zfsvfs->z_shares_dir);
	if (error == ENOENT)
		zfsvfs->z_shares_dir = 0;
	else if (error != 0)
		return (error);

	error = sa_setup(os, sa_obj, zfs_attr_table, ZPL_END,
	    &zfsvfs->z_attr_table);
	if (error != 0)
		return (error);

	if (zfsvfs->z_version >= ZPL_VERSION_SA)
		sa_register_update_callback(os, zfs_sa_upgrade);

	return (0);
}