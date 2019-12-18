#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ z_version; scalar_t__ z_userquota_obj; scalar_t__ z_groupquota_obj; scalar_t__ z_userobjquota_obj; scalar_t__ z_groupobjquota_obj; scalar_t__ z_projectquota_obj; scalar_t__ z_projectobjquota_obj; int /*<<< orphan*/  z_os; int /*<<< orphan*/  z_lock; scalar_t__ z_fuid_dirty; } ;
typedef  TYPE_1__ zfsvfs_t ;
typedef  int zfs_userquota_prop_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_TRUE ; 
 scalar_t__ DMU_NEW_OBJECT ; 
 int /*<<< orphan*/  DMU_OT_NONE ; 
 int /*<<< orphan*/  DMU_OT_USERGROUP_QUOTA ; 
 int /*<<< orphan*/  EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  ENOTSUP ; 
 scalar_t__ MASTER_NODE_OBJ ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TXG_WAIT ; 
 int /*<<< orphan*/  VERIFY (int) ; 
#define  ZFS_PROP_GROUPOBJQUOTA 133 
#define  ZFS_PROP_GROUPQUOTA 132 
#define  ZFS_PROP_PROJECTOBJQUOTA 131 
#define  ZFS_PROP_PROJECTQUOTA 130 
#define  ZFS_PROP_USEROBJQUOTA 129 
#define  ZFS_PROP_USERQUOTA 128 
 scalar_t__ ZPL_VERSION_USERSPACE ; 
 int /*<<< orphan*/  dmu_objset_projectquota_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_abort (int /*<<< orphan*/ *) ; 
 int dmu_tx_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_tx_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_hold_zap (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int id_to_fuidstr (TYPE_1__*,char const*,scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ zap_add (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ zap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int zap_remove (int /*<<< orphan*/ ,scalar_t__,char*,int /*<<< orphan*/ *) ; 
 int zap_update (int /*<<< orphan*/ ,scalar_t__,char*,int,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_fuid_sync (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_fuid_txhold (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** zfs_userquota_prop_prefixes ; 
 int /*<<< orphan*/  zpl_is_valid_projid (scalar_t__) ; 

int
zfs_set_userquota(zfsvfs_t *zfsvfs, zfs_userquota_prop_t type,
    const char *domain, uint64_t rid, uint64_t quota)
{
	char buf[32];
	int err;
	dmu_tx_t *tx;
	uint64_t *objp;
	boolean_t fuid_dirtied;

	if (zfsvfs->z_version < ZPL_VERSION_USERSPACE)
		return (SET_ERROR(ENOTSUP));

	switch (type) {
	case ZFS_PROP_USERQUOTA:
		objp = &zfsvfs->z_userquota_obj;
		break;
	case ZFS_PROP_GROUPQUOTA:
		objp = &zfsvfs->z_groupquota_obj;
		break;
	case ZFS_PROP_USEROBJQUOTA:
		objp = &zfsvfs->z_userobjquota_obj;
		break;
	case ZFS_PROP_GROUPOBJQUOTA:
		objp = &zfsvfs->z_groupobjquota_obj;
		break;
	case ZFS_PROP_PROJECTQUOTA:
		if (!dmu_objset_projectquota_enabled(zfsvfs->z_os))
			return (SET_ERROR(ENOTSUP));
		if (!zpl_is_valid_projid(rid))
			return (SET_ERROR(EINVAL));

		objp = &zfsvfs->z_projectquota_obj;
		break;
	case ZFS_PROP_PROJECTOBJQUOTA:
		if (!dmu_objset_projectquota_enabled(zfsvfs->z_os))
			return (SET_ERROR(ENOTSUP));
		if (!zpl_is_valid_projid(rid))
			return (SET_ERROR(EINVAL));

		objp = &zfsvfs->z_projectobjquota_obj;
		break;
	default:
		return (SET_ERROR(EINVAL));
	}

	err = id_to_fuidstr(zfsvfs, domain, rid, buf, B_TRUE);
	if (err)
		return (err);
	fuid_dirtied = zfsvfs->z_fuid_dirty;

	tx = dmu_tx_create(zfsvfs->z_os);
	dmu_tx_hold_zap(tx, *objp ? *objp : DMU_NEW_OBJECT, B_TRUE, NULL);
	if (*objp == 0) {
		dmu_tx_hold_zap(tx, MASTER_NODE_OBJ, B_TRUE,
		    zfs_userquota_prop_prefixes[type]);
	}
	if (fuid_dirtied)
		zfs_fuid_txhold(zfsvfs, tx);
	err = dmu_tx_assign(tx, TXG_WAIT);
	if (err) {
		dmu_tx_abort(tx);
		return (err);
	}

	mutex_enter(&zfsvfs->z_lock);
	if (*objp == 0) {
		*objp = zap_create(zfsvfs->z_os, DMU_OT_USERGROUP_QUOTA,
		    DMU_OT_NONE, 0, tx);
		VERIFY(0 == zap_add(zfsvfs->z_os, MASTER_NODE_OBJ,
		    zfs_userquota_prop_prefixes[type], 8, 1, objp, tx));
	}
	mutex_exit(&zfsvfs->z_lock);

	if (quota == 0) {
		err = zap_remove(zfsvfs->z_os, *objp, buf, tx);
		if (err == ENOENT)
			err = 0;
	} else {
		err = zap_update(zfsvfs->z_os, *objp, buf, 8, 1, &quota, tx);
	}
	ASSERT(err == 0);
	if (fuid_dirtied)
		zfs_fuid_sync(zfsvfs, tx);
	dmu_tx_commit(tx);
	return (err);
}