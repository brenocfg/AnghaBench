#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_5__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;

/* Type definitions */
struct TYPE_30__ {void* z_unlinked; } ;
typedef  TYPE_2__ znode_t ;
struct TYPE_31__ {scalar_t__ z_use_fuids; int /*<<< orphan*/  z_use_sa; void* z_fuid_dirty; int /*<<< orphan*/  z_unlinkedobj; int /*<<< orphan*/ * z_os; } ;
typedef  TYPE_3__ zfsvfs_t ;
struct TYPE_32__ {TYPE_1__* z_aclp; } ;
typedef  TYPE_4__ zfs_acl_ids_t ;
typedef  int /*<<< orphan*/  xvattr_t ;
typedef  int /*<<< orphan*/  vsecattr_t ;
struct TYPE_33__ {int va_mask; int /*<<< orphan*/  va_mode; } ;
typedef  TYPE_5__ vattr_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uid_t ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  gid_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  cred_t ;
typedef  void* boolean_t ;
struct TYPE_29__ {scalar_t__ z_acl_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACE_ADD_FILE ; 
 int ATTR_XVATTR ; 
 scalar_t__ B_FALSE ; 
 void* B_TRUE ; 
 int /*<<< orphan*/  DMU_NEW_OBJECT ; 
 int /*<<< orphan*/  EDQUOT ; 
 int /*<<< orphan*/  EINVAL ; 
 int ERESTART ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IS_EPHEMERAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_TMPFILE ; 
 TYPE_2__* ITOZ (struct inode*) ; 
 TYPE_3__* ITOZSB (struct inode*) ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int TXG_NOTHROTTLE ; 
 int TXG_NOWAIT ; 
 scalar_t__ ZFS_ACE_SPACE ; 
 int /*<<< orphan*/  ZFS_DEFAULT_PROJID ; 
 int /*<<< orphan*/  ZFS_ENTER (TYPE_3__*) ; 
 int /*<<< orphan*/  ZFS_EXIT (TYPE_3__*) ; 
 scalar_t__ ZFS_SA_BASE_ATTR_SIZE ; 
 int /*<<< orphan*/  ZFS_VERIFY_ZP (TYPE_2__*) ; 
 struct inode* ZTOI (TYPE_2__*) ; 
 int /*<<< orphan*/  crgetgid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crgetuid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_tx_abort (int /*<<< orphan*/ *) ; 
 int dmu_tx_assign (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dmu_tx_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_tx_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_tx_hold_sa_create (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  dmu_tx_hold_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dmu_tx_hold_zap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_tx_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int secpolicy_xvattr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int zfs_acl_ids_create (TYPE_2__*,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  zfs_acl_ids_free (TYPE_4__*) ; 
 scalar_t__ zfs_acl_ids_overquota (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_fuid_sync (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_fuid_txhold (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_inherit_projid (TYPE_2__*) ; 
 int /*<<< orphan*/  zfs_inode_update (TYPE_2__*) ; 
 int /*<<< orphan*/  zfs_mknode (TYPE_2__*,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__**,TYPE_4__*) ; 
 int /*<<< orphan*/  zfs_unlinked_add (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int zfs_zaccess (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 

int
zfs_tmpfile(struct inode *dip, vattr_t *vap, int excl,
    int mode, struct inode **ipp, cred_t *cr, int flag, vsecattr_t *vsecp)
{
	znode_t		*zp = NULL, *dzp = ITOZ(dip);
	zfsvfs_t	*zfsvfs = ITOZSB(dip);
	objset_t	*os;
	dmu_tx_t	*tx;
	int		error;
	uid_t		uid;
	gid_t		gid;
	zfs_acl_ids_t   acl_ids;
	uint64_t	projid = ZFS_DEFAULT_PROJID;
	boolean_t	fuid_dirtied;
	boolean_t	have_acl = B_FALSE;
	boolean_t	waited = B_FALSE;

	/*
	 * If we have an ephemeral id, ACL, or XVATTR then
	 * make sure file system is at proper version
	 */

	gid = crgetgid(cr);
	uid = crgetuid(cr);

	if (zfsvfs->z_use_fuids == B_FALSE &&
	    (vsecp || IS_EPHEMERAL(uid) || IS_EPHEMERAL(gid)))
		return (SET_ERROR(EINVAL));

	ZFS_ENTER(zfsvfs);
	ZFS_VERIFY_ZP(dzp);
	os = zfsvfs->z_os;

	if (vap->va_mask & ATTR_XVATTR) {
		if ((error = secpolicy_xvattr((xvattr_t *)vap,
		    crgetuid(cr), cr, vap->va_mode)) != 0) {
			ZFS_EXIT(zfsvfs);
			return (error);
		}
	}

top:
	*ipp = NULL;

	/*
	 * Create a new file object and update the directory
	 * to reference it.
	 */
	if ((error = zfs_zaccess(dzp, ACE_ADD_FILE, 0, B_FALSE, cr))) {
		if (have_acl)
			zfs_acl_ids_free(&acl_ids);
		goto out;
	}

	if (!have_acl && (error = zfs_acl_ids_create(dzp, 0, vap,
	    cr, vsecp, &acl_ids)) != 0)
		goto out;
	have_acl = B_TRUE;

	if (S_ISREG(vap->va_mode) || S_ISDIR(vap->va_mode))
		projid = zfs_inherit_projid(dzp);
	if (zfs_acl_ids_overquota(zfsvfs, &acl_ids, projid)) {
		zfs_acl_ids_free(&acl_ids);
		error = SET_ERROR(EDQUOT);
		goto out;
	}

	tx = dmu_tx_create(os);

	dmu_tx_hold_sa_create(tx, acl_ids.z_aclp->z_acl_bytes +
	    ZFS_SA_BASE_ATTR_SIZE);
	dmu_tx_hold_zap(tx, zfsvfs->z_unlinkedobj, FALSE, NULL);

	fuid_dirtied = zfsvfs->z_fuid_dirty;
	if (fuid_dirtied)
		zfs_fuid_txhold(zfsvfs, tx);
	if (!zfsvfs->z_use_sa &&
	    acl_ids.z_aclp->z_acl_bytes > ZFS_ACE_SPACE) {
		dmu_tx_hold_write(tx, DMU_NEW_OBJECT,
		    0, acl_ids.z_aclp->z_acl_bytes);
	}
	error = dmu_tx_assign(tx, (waited ? TXG_NOTHROTTLE : 0) | TXG_NOWAIT);
	if (error) {
		if (error == ERESTART) {
			waited = B_TRUE;
			dmu_tx_wait(tx);
			dmu_tx_abort(tx);
			goto top;
		}
		zfs_acl_ids_free(&acl_ids);
		dmu_tx_abort(tx);
		ZFS_EXIT(zfsvfs);
		return (error);
	}
	zfs_mknode(dzp, vap, tx, cr, IS_TMPFILE, &zp, &acl_ids);

	if (fuid_dirtied)
		zfs_fuid_sync(zfsvfs, tx);

	/* Add to unlinked set */
	zp->z_unlinked = B_TRUE;
	zfs_unlinked_add(zp, tx);
	zfs_acl_ids_free(&acl_ids);
	dmu_tx_commit(tx);
out:

	if (error) {
		if (zp)
			iput(ZTOI(zp));
	} else {
		zfs_inode_update(dzp);
		zfs_inode_update(zp);
		*ipp = ZTOI(zp);
	}

	ZFS_EXIT(zfsvfs);
	return (error);
}