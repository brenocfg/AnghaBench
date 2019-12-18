#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_45__   TYPE_6__ ;
typedef  struct TYPE_44__   TYPE_5__ ;
typedef  struct TYPE_43__   TYPE_4__ ;
typedef  struct TYPE_42__   TYPE_3__ ;
typedef  struct TYPE_41__   TYPE_2__ ;
typedef  struct TYPE_40__   TYPE_1__ ;

/* Type definitions */
struct TYPE_41__ {int z_pflags; int /*<<< orphan*/  z_lock; int /*<<< orphan*/  z_seq; int /*<<< orphan*/  z_sa_hdl; int /*<<< orphan*/  z_id; } ;
typedef  TYPE_2__ znode_t ;
typedef  int /*<<< orphan*/  zilog_t ;
struct TYPE_42__ {scalar_t__ z_use_fuids; TYPE_6__* z_os; int /*<<< orphan*/  z_use_sa; scalar_t__ z_fuid_dirty; scalar_t__ z_utf8; int /*<<< orphan*/ * z_log; } ;
typedef  TYPE_3__ zfsvfs_t ;
typedef  int /*<<< orphan*/  zfs_dirlock_t ;
struct TYPE_43__ {int /*<<< orphan*/  z_fuidp; TYPE_1__* z_aclp; } ;
typedef  TYPE_4__ zfs_acl_ids_t ;
typedef  int /*<<< orphan*/  xvattr_t ;
typedef  int /*<<< orphan*/  vsecattr_t ;
struct TYPE_44__ {int va_mask; scalar_t__ va_size; int /*<<< orphan*/  va_mode; } ;
typedef  TYPE_5__ vattr_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uid_t ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct TYPE_45__ {scalar_t__ os_sync; } ;
typedef  TYPE_6__ objset_t ;
typedef  int /*<<< orphan*/  gid_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  cred_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_40__ {scalar_t__ z_acl_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACE_ADD_FILE ; 
 int ATTR_SIZE ; 
 int ATTR_XVATTR ; 
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  DMU_NEW_OBJECT ; 
 int /*<<< orphan*/  EDQUOT ; 
 int /*<<< orphan*/  EEXIST ; 
 int /*<<< orphan*/  EILSEQ ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EISDIR ; 
 int ERESTART ; 
 int FAPPEND ; 
 int FIGNORECASE ; 
 scalar_t__ IS_EPHEMERAL (int /*<<< orphan*/ ) ; 
 TYPE_2__* ITOZ (struct inode*) ; 
 TYPE_3__* ITOZSB (struct inode*) ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int TXG_NOTHROTTLE ; 
 int TXG_NOWAIT ; 
 int /*<<< orphan*/  TX_CI ; 
 int /*<<< orphan*/  U8_VALIDATE_ENTIRE ; 
 int V_APPEND ; 
 int ZCILOOK ; 
 scalar_t__ ZFS_ACE_SPACE ; 
 int /*<<< orphan*/  ZFS_DEFAULT_PROJID ; 
 int /*<<< orphan*/  ZFS_ENTER (TYPE_3__*) ; 
 int /*<<< orphan*/  ZFS_EXIT (TYPE_3__*) ; 
 scalar_t__ ZFS_SA_BASE_ATTR_SIZE ; 
 scalar_t__ ZFS_SYNC_ALWAYS ; 
 int /*<<< orphan*/  ZFS_VERIFY_ZP (TYPE_2__*) ; 
 int ZFS_XATTR ; 
 int /*<<< orphan*/  ZNEW ; 
 struct inode* ZTOI (TYPE_2__*) ; 
 int /*<<< orphan*/  Z_FILE ; 
 int /*<<< orphan*/  crgetgid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crgetuid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_tx_abort (int /*<<< orphan*/ *) ; 
 int dmu_tx_assign (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dmu_tx_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_tx_create (TYPE_6__*) ; 
 int /*<<< orphan*/  dmu_tx_hold_sa (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dmu_tx_hold_sa_create (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  dmu_tx_hold_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dmu_tx_hold_zap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dmu_tx_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  igrab (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_inode_hash (struct inode*) ; 
 int secpolicy_xvattr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ u8_validate (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int zfs_acl_ids_create (TYPE_2__*,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  zfs_acl_ids_free (TYPE_4__*) ; 
 scalar_t__ zfs_acl_ids_overquota (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int zfs_dirent_lock (int /*<<< orphan*/ **,TYPE_2__*,char*,TYPE_2__**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_dirent_unlock (int /*<<< orphan*/ *) ; 
 int zfs_freesp (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_fuid_sync (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_fuid_txhold (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_inherit_projid (TYPE_2__*) ; 
 int /*<<< orphan*/  zfs_inode_update (TYPE_2__*) ; 
 int zfs_link_create (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_log_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  zfs_log_create_txtype (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  zfs_mknode (TYPE_2__*,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__**,TYPE_4__*) ; 
 int zfs_zaccess (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int zfs_zaccess_rwx (TYPE_2__*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_znode_delete (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zil_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
zfs_create(struct inode *dip, char *name, vattr_t *vap, int excl,
    int mode, struct inode **ipp, cred_t *cr, int flag, vsecattr_t *vsecp)
{
	znode_t		*zp, *dzp = ITOZ(dip);
	zfsvfs_t	*zfsvfs = ITOZSB(dip);
	zilog_t		*zilog;
	objset_t	*os;
	zfs_dirlock_t	*dl;
	dmu_tx_t	*tx;
	int		error;
	uid_t		uid;
	gid_t		gid;
	zfs_acl_ids_t   acl_ids;
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

	if (name == NULL)
		return (SET_ERROR(EINVAL));

	ZFS_ENTER(zfsvfs);
	ZFS_VERIFY_ZP(dzp);
	os = zfsvfs->z_os;
	zilog = zfsvfs->z_log;

	if (zfsvfs->z_utf8 && u8_validate(name, strlen(name),
	    NULL, U8_VALIDATE_ENTIRE, &error) < 0) {
		ZFS_EXIT(zfsvfs);
		return (SET_ERROR(EILSEQ));
	}

	if (vap->va_mask & ATTR_XVATTR) {
		if ((error = secpolicy_xvattr((xvattr_t *)vap,
		    crgetuid(cr), cr, vap->va_mode)) != 0) {
			ZFS_EXIT(zfsvfs);
			return (error);
		}
	}

top:
	*ipp = NULL;
	if (*name == '\0') {
		/*
		 * Null component name refers to the directory itself.
		 */
		igrab(dip);
		zp = dzp;
		dl = NULL;
		error = 0;
	} else {
		/* possible igrab(zp) */
		int zflg = 0;

		if (flag & FIGNORECASE)
			zflg |= ZCILOOK;

		error = zfs_dirent_lock(&dl, dzp, name, &zp, zflg,
		    NULL, NULL);
		if (error) {
			if (have_acl)
				zfs_acl_ids_free(&acl_ids);
			if (strcmp(name, "..") == 0)
				error = SET_ERROR(EISDIR);
			ZFS_EXIT(zfsvfs);
			return (error);
		}
	}

	if (zp == NULL) {
		uint64_t txtype;
		uint64_t projid = ZFS_DEFAULT_PROJID;

		/*
		 * Create a new file object and update the directory
		 * to reference it.
		 */
		if ((error = zfs_zaccess(dzp, ACE_ADD_FILE, 0, B_FALSE, cr))) {
			if (have_acl)
				zfs_acl_ids_free(&acl_ids);
			goto out;
		}

		/*
		 * We only support the creation of regular files in
		 * extended attribute directories.
		 */

		if ((dzp->z_pflags & ZFS_XATTR) && !S_ISREG(vap->va_mode)) {
			if (have_acl)
				zfs_acl_ids_free(&acl_ids);
			error = SET_ERROR(EINVAL);
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

		fuid_dirtied = zfsvfs->z_fuid_dirty;
		if (fuid_dirtied)
			zfs_fuid_txhold(zfsvfs, tx);
		dmu_tx_hold_zap(tx, dzp->z_id, TRUE, name);
		dmu_tx_hold_sa(tx, dzp->z_sa_hdl, B_FALSE);
		if (!zfsvfs->z_use_sa &&
		    acl_ids.z_aclp->z_acl_bytes > ZFS_ACE_SPACE) {
			dmu_tx_hold_write(tx, DMU_NEW_OBJECT,
			    0, acl_ids.z_aclp->z_acl_bytes);
		}

		error = dmu_tx_assign(tx,
		    (waited ? TXG_NOTHROTTLE : 0) | TXG_NOWAIT);
		if (error) {
			zfs_dirent_unlock(dl);
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
		zfs_mknode(dzp, vap, tx, cr, 0, &zp, &acl_ids);

		error = zfs_link_create(dl, zp, tx, ZNEW);
		if (error != 0) {
			/*
			 * Since, we failed to add the directory entry for it,
			 * delete the newly created dnode.
			 */
			zfs_znode_delete(zp, tx);
			remove_inode_hash(ZTOI(zp));
			zfs_acl_ids_free(&acl_ids);
			dmu_tx_commit(tx);
			goto out;
		}

		if (fuid_dirtied)
			zfs_fuid_sync(zfsvfs, tx);

		txtype = zfs_log_create_txtype(Z_FILE, vsecp, vap);
		if (flag & FIGNORECASE)
			txtype |= TX_CI;
		zfs_log_create(zilog, tx, txtype, dzp, zp, name,
		    vsecp, acl_ids.z_fuidp, vap);
		zfs_acl_ids_free(&acl_ids);
		dmu_tx_commit(tx);
	} else {
		int aflags = (flag & FAPPEND) ? V_APPEND : 0;

		if (have_acl)
			zfs_acl_ids_free(&acl_ids);
		have_acl = B_FALSE;

		/*
		 * A directory entry already exists for this name.
		 */
		/*
		 * Can't truncate an existing file if in exclusive mode.
		 */
		if (excl) {
			error = SET_ERROR(EEXIST);
			goto out;
		}
		/*
		 * Can't open a directory for writing.
		 */
		if (S_ISDIR(ZTOI(zp)->i_mode)) {
			error = SET_ERROR(EISDIR);
			goto out;
		}
		/*
		 * Verify requested access to file.
		 */
		if (mode && (error = zfs_zaccess_rwx(zp, mode, aflags, cr))) {
			goto out;
		}

		mutex_enter(&dzp->z_lock);
		dzp->z_seq++;
		mutex_exit(&dzp->z_lock);

		/*
		 * Truncate regular files if requested.
		 */
		if (S_ISREG(ZTOI(zp)->i_mode) &&
		    (vap->va_mask & ATTR_SIZE) && (vap->va_size == 0)) {
			/* we can't hold any locks when calling zfs_freesp() */
			if (dl) {
				zfs_dirent_unlock(dl);
				dl = NULL;
			}
			error = zfs_freesp(zp, 0, 0, mode, TRUE);
		}
	}
out:

	if (dl)
		zfs_dirent_unlock(dl);

	if (error) {
		if (zp)
			iput(ZTOI(zp));
	} else {
		zfs_inode_update(dzp);
		zfs_inode_update(zp);
		*ipp = ZTOI(zp);
	}

	if (zfsvfs->z_os->os_sync == ZFS_SYNC_ALWAYS)
		zil_commit(zilog, 0);

	ZFS_EXIT(zfsvfs);
	return (error);
}