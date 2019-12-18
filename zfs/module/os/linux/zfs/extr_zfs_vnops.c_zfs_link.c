#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_12__ ;

/* Type definitions */
struct TYPE_22__ {int z_pflags; scalar_t__ z_projid; void* z_unlinked; int /*<<< orphan*/  z_id; int /*<<< orphan*/  z_sa_hdl; } ;
typedef  TYPE_1__ znode_t ;
typedef  int /*<<< orphan*/  zilog_t ;
struct TYPE_23__ {scalar_t__ z_shares_dir; TYPE_12__* z_os; int /*<<< orphan*/  z_unlinkedobj; scalar_t__ z_utf8; int /*<<< orphan*/ * z_log; } ;
typedef  TYPE_2__ zfsvfs_t ;
typedef  int /*<<< orphan*/  zfs_dirlock_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uid_t ;
struct inode {scalar_t__ i_nlink; int i_state; scalar_t__ i_sb; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_mode; } ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  cred_t ;
typedef  int boolean_t ;
struct TYPE_21__ {scalar_t__ os_sync; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACE_ADD_FILE ; 
 int /*<<< orphan*/  ASSERT (scalar_t__) ; 
 void* B_FALSE ; 
 void* B_TRUE ; 
 int /*<<< orphan*/  EILSEQ ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EPERM ; 
 int ERESTART ; 
 int /*<<< orphan*/  EXDEV ; 
 int /*<<< orphan*/  FALSE ; 
 int FIGNORECASE ; 
 TYPE_1__* ITOZ (struct inode*) ; 
 TYPE_2__* ITOZSB (struct inode*) ; 
 int I_LINKABLE ; 
 int /*<<< orphan*/  KUID_TO_SUID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SA_ZPL_PARENT (TYPE_2__*) ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int TXG_NOTHROTTLE ; 
 int TXG_NOWAIT ; 
 scalar_t__ TX_CI ; 
 scalar_t__ TX_LINK ; 
 int /*<<< orphan*/  U8_VALIDATE_ENTIRE ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int ZCILOOK ; 
 int /*<<< orphan*/  ZFS_ENTER (TYPE_2__*) ; 
 int /*<<< orphan*/  ZFS_EXIT (TYPE_2__*) ; 
 int /*<<< orphan*/  ZFS_OWNER ; 
 int ZFS_PROJINHERIT ; 
 scalar_t__ ZFS_SYNC_ALWAYS ; 
 int /*<<< orphan*/  ZFS_VERIFY_ZP (TYPE_1__*) ; 
 int ZFS_XATTR ; 
 int ZNEW ; 
 scalar_t__ crgetuid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_objset_pool (TYPE_12__*) ; 
 int /*<<< orphan*/  dmu_tx_abort (int /*<<< orphan*/ *) ; 
 int dmu_tx_assign (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dmu_tx_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_tx_create (TYPE_12__*) ; 
 scalar_t__ dmu_tx_get_txg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_tx_hold_sa (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  dmu_tx_hold_zap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dmu_tx_wait (int /*<<< orphan*/ *) ; 
 int sa_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 scalar_t__ secpolicy_basic_link (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  txg_wait_synced (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ u8_validate (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ zap_remove_int (TYPE_12__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int zfs_dirent_lock (int /*<<< orphan*/ **,TYPE_1__*,char*,TYPE_1__**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_dirent_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_fuid_map_id (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_inode_update (TYPE_1__*) ; 
 int zfs_link_create (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_log_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,TYPE_1__*,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  zfs_sa_upgrade_txholds (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int zfs_zaccess (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 scalar_t__ zfsctl_is_node (struct inode*) ; 
 int /*<<< orphan*/  zil_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
zfs_link(struct inode *tdip, struct inode *sip, char *name, cred_t *cr,
    int flags)
{
	znode_t		*dzp = ITOZ(tdip);
	znode_t		*tzp, *szp;
	zfsvfs_t	*zfsvfs = ITOZSB(tdip);
	zilog_t		*zilog;
	zfs_dirlock_t	*dl;
	dmu_tx_t	*tx;
	int		error;
	int		zf = ZNEW;
	uint64_t	parent;
	uid_t		owner;
	boolean_t	waited = B_FALSE;
	boolean_t	is_tmpfile = 0;
	uint64_t	txg;
#ifdef HAVE_TMPFILE
	is_tmpfile = (sip->i_nlink == 0 && (sip->i_state & I_LINKABLE));
#endif
	ASSERT(S_ISDIR(tdip->i_mode));

	if (name == NULL)
		return (SET_ERROR(EINVAL));

	ZFS_ENTER(zfsvfs);
	ZFS_VERIFY_ZP(dzp);
	zilog = zfsvfs->z_log;

	/*
	 * POSIX dictates that we return EPERM here.
	 * Better choices include ENOTSUP or EISDIR.
	 */
	if (S_ISDIR(sip->i_mode)) {
		ZFS_EXIT(zfsvfs);
		return (SET_ERROR(EPERM));
	}

	szp = ITOZ(sip);
	ZFS_VERIFY_ZP(szp);

	/*
	 * If we are using project inheritance, means if the directory has
	 * ZFS_PROJINHERIT set, then its descendant directories will inherit
	 * not only the project ID, but also the ZFS_PROJINHERIT flag. Under
	 * such case, we only allow hard link creation in our tree when the
	 * project IDs are the same.
	 */
	if (dzp->z_pflags & ZFS_PROJINHERIT && dzp->z_projid != szp->z_projid) {
		ZFS_EXIT(zfsvfs);
		return (SET_ERROR(EXDEV));
	}

	/*
	 * We check i_sb because snapshots and the ctldir must have different
	 * super blocks.
	 */
	if (sip->i_sb != tdip->i_sb || zfsctl_is_node(sip)) {
		ZFS_EXIT(zfsvfs);
		return (SET_ERROR(EXDEV));
	}

	/* Prevent links to .zfs/shares files */

	if ((error = sa_lookup(szp->z_sa_hdl, SA_ZPL_PARENT(zfsvfs),
	    &parent, sizeof (uint64_t))) != 0) {
		ZFS_EXIT(zfsvfs);
		return (error);
	}
	if (parent == zfsvfs->z_shares_dir) {
		ZFS_EXIT(zfsvfs);
		return (SET_ERROR(EPERM));
	}

	if (zfsvfs->z_utf8 && u8_validate(name,
	    strlen(name), NULL, U8_VALIDATE_ENTIRE, &error) < 0) {
		ZFS_EXIT(zfsvfs);
		return (SET_ERROR(EILSEQ));
	}
	if (flags & FIGNORECASE)
		zf |= ZCILOOK;

	/*
	 * We do not support links between attributes and non-attributes
	 * because of the potential security risk of creating links
	 * into "normal" file space in order to circumvent restrictions
	 * imposed in attribute space.
	 */
	if ((szp->z_pflags & ZFS_XATTR) != (dzp->z_pflags & ZFS_XATTR)) {
		ZFS_EXIT(zfsvfs);
		return (SET_ERROR(EINVAL));
	}

	owner = zfs_fuid_map_id(zfsvfs, KUID_TO_SUID(sip->i_uid),
	    cr, ZFS_OWNER);
	if (owner != crgetuid(cr) && secpolicy_basic_link(cr) != 0) {
		ZFS_EXIT(zfsvfs);
		return (SET_ERROR(EPERM));
	}

	if ((error = zfs_zaccess(dzp, ACE_ADD_FILE, 0, B_FALSE, cr))) {
		ZFS_EXIT(zfsvfs);
		return (error);
	}

top:
	/*
	 * Attempt to lock directory; fail if entry already exists.
	 */
	error = zfs_dirent_lock(&dl, dzp, name, &tzp, zf, NULL, NULL);
	if (error) {
		ZFS_EXIT(zfsvfs);
		return (error);
	}

	tx = dmu_tx_create(zfsvfs->z_os);
	dmu_tx_hold_sa(tx, szp->z_sa_hdl, B_FALSE);
	dmu_tx_hold_zap(tx, dzp->z_id, TRUE, name);
	if (is_tmpfile)
		dmu_tx_hold_zap(tx, zfsvfs->z_unlinkedobj, FALSE, NULL);

	zfs_sa_upgrade_txholds(tx, szp);
	zfs_sa_upgrade_txholds(tx, dzp);
	error = dmu_tx_assign(tx, (waited ? TXG_NOTHROTTLE : 0) | TXG_NOWAIT);
	if (error) {
		zfs_dirent_unlock(dl);
		if (error == ERESTART) {
			waited = B_TRUE;
			dmu_tx_wait(tx);
			dmu_tx_abort(tx);
			goto top;
		}
		dmu_tx_abort(tx);
		ZFS_EXIT(zfsvfs);
		return (error);
	}
	/* unmark z_unlinked so zfs_link_create will not reject */
	if (is_tmpfile)
		szp->z_unlinked = B_FALSE;
	error = zfs_link_create(dl, szp, tx, 0);

	if (error == 0) {
		uint64_t txtype = TX_LINK;
		/*
		 * tmpfile is created to be in z_unlinkedobj, so remove it.
		 * Also, we don't log in ZIL, because all previous file
		 * operation on the tmpfile are ignored by ZIL. Instead we
		 * always wait for txg to sync to make sure all previous
		 * operation are sync safe.
		 */
		if (is_tmpfile) {
			VERIFY(zap_remove_int(zfsvfs->z_os,
			    zfsvfs->z_unlinkedobj, szp->z_id, tx) == 0);
		} else {
			if (flags & FIGNORECASE)
				txtype |= TX_CI;
			zfs_log_link(zilog, tx, txtype, dzp, szp, name);
		}
	} else if (is_tmpfile) {
		/* restore z_unlinked since when linking failed */
		szp->z_unlinked = B_TRUE;
	}
	txg = dmu_tx_get_txg(tx);
	dmu_tx_commit(tx);

	zfs_dirent_unlock(dl);

	if (!is_tmpfile && zfsvfs->z_os->os_sync == ZFS_SYNC_ALWAYS)
		zil_commit(zilog, 0);

	if (is_tmpfile)
		txg_wait_synced(dmu_objset_pool(zfsvfs->z_os), txg);

	zfs_inode_update(dzp);
	zfs_inode_update(szp);
	ZFS_EXIT(zfsvfs);
	return (error);
}