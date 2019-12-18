#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ z_projid; int z_pflags; int /*<<< orphan*/  z_sa_hdl; int /*<<< orphan*/  z_lock; int /*<<< orphan*/  z_id; } ;
typedef  TYPE_1__ znode_t ;
struct TYPE_15__ {int /*<<< orphan*/ * z_os; } ;
typedef  TYPE_2__ zfsvfs_t ;
typedef  int /*<<< orphan*/  zfs_dirlock_t ;
typedef  int /*<<< orphan*/  zap_cursor_t ;
struct TYPE_16__ {int za_integer_length; int za_num_integers; scalar_t__ za_name; } ;
typedef  TYPE_3__ zap_attribute_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uid ;
struct inode {int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
typedef  int /*<<< orphan*/  sa_bulk_attr_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  gid ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int ENOENT ; 
 int ENXIO ; 
 TYPE_2__* ITOZSB (struct inode*) ; 
 scalar_t__ KGID_TO_SGID (int /*<<< orphan*/ ) ; 
 scalar_t__ KUID_TO_SUID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SA_ADD_BULK_ATTR (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  SA_ZPL_FLAGS (TYPE_2__*) ; 
 int /*<<< orphan*/  SA_ZPL_GID (TYPE_2__*) ; 
 int /*<<< orphan*/  SA_ZPL_PROJID (TYPE_2__*) ; 
 int /*<<< orphan*/  SA_ZPL_UID (TYPE_2__*) ; 
 int /*<<< orphan*/  TXG_WAIT ; 
 int /*<<< orphan*/  ZEXISTS ; 
 int ZFS_PROJID ; 
 struct inode* ZTOI (TYPE_1__*) ; 
 int /*<<< orphan*/  dmu_tx_abort (int /*<<< orphan*/ *) ; 
 int dmu_tx_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_tx_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_tx_hold_sa (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int sa_bulk_update (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_advance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int zap_cursor_retrieve (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int zfs_dirent_lock (int /*<<< orphan*/ **,TYPE_1__*,char*,TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_dirent_unlock (int /*<<< orphan*/ *) ; 
 int zfs_gid_read (struct inode*) ; 
 int zfs_uid_read (struct inode*) ; 

__attribute__((used)) static int
zfs_setattr_dir(znode_t *dzp)
{
	struct inode	*dxip = ZTOI(dzp);
	struct inode	*xip = NULL;
	zfsvfs_t	*zfsvfs = ITOZSB(dxip);
	objset_t	*os = zfsvfs->z_os;
	zap_cursor_t	zc;
	zap_attribute_t	zap;
	zfs_dirlock_t	*dl;
	znode_t		*zp;
	dmu_tx_t	*tx = NULL;
	uint64_t	uid, gid;
	sa_bulk_attr_t	bulk[4];
	int		count;
	int		err;

	zap_cursor_init(&zc, os, dzp->z_id);
	while ((err = zap_cursor_retrieve(&zc, &zap)) == 0) {
		count = 0;
		if (zap.za_integer_length != 8 || zap.za_num_integers != 1) {
			err = ENXIO;
			break;
		}

		err = zfs_dirent_lock(&dl, dzp, (char *)zap.za_name, &zp,
		    ZEXISTS, NULL, NULL);
		if (err == ENOENT)
			goto next;
		if (err)
			break;

		xip = ZTOI(zp);
		if (KUID_TO_SUID(xip->i_uid) == KUID_TO_SUID(dxip->i_uid) &&
		    KGID_TO_SGID(xip->i_gid) == KGID_TO_SGID(dxip->i_gid) &&
		    zp->z_projid == dzp->z_projid)
			goto next;

		tx = dmu_tx_create(os);
		if (!(zp->z_pflags & ZFS_PROJID))
			dmu_tx_hold_sa(tx, zp->z_sa_hdl, B_TRUE);
		else
			dmu_tx_hold_sa(tx, zp->z_sa_hdl, B_FALSE);

		err = dmu_tx_assign(tx, TXG_WAIT);
		if (err)
			break;

		mutex_enter(&dzp->z_lock);

		if (KUID_TO_SUID(xip->i_uid) != KUID_TO_SUID(dxip->i_uid)) {
			xip->i_uid = dxip->i_uid;
			uid = zfs_uid_read(dxip);
			SA_ADD_BULK_ATTR(bulk, count, SA_ZPL_UID(zfsvfs), NULL,
			    &uid, sizeof (uid));
		}

		if (KGID_TO_SGID(xip->i_gid) != KGID_TO_SGID(dxip->i_gid)) {
			xip->i_gid = dxip->i_gid;
			gid = zfs_gid_read(dxip);
			SA_ADD_BULK_ATTR(bulk, count, SA_ZPL_GID(zfsvfs), NULL,
			    &gid, sizeof (gid));
		}

		if (zp->z_projid != dzp->z_projid) {
			if (!(zp->z_pflags & ZFS_PROJID)) {
				zp->z_pflags |= ZFS_PROJID;
				SA_ADD_BULK_ATTR(bulk, count,
				    SA_ZPL_FLAGS(zfsvfs), NULL, &zp->z_pflags,
				    sizeof (zp->z_pflags));
			}

			zp->z_projid = dzp->z_projid;
			SA_ADD_BULK_ATTR(bulk, count, SA_ZPL_PROJID(zfsvfs),
			    NULL, &zp->z_projid, sizeof (zp->z_projid));
		}

		mutex_exit(&dzp->z_lock);

		if (likely(count > 0)) {
			err = sa_bulk_update(zp->z_sa_hdl, bulk, count, tx);
			dmu_tx_commit(tx);
		} else {
			dmu_tx_abort(tx);
		}
		tx = NULL;
		if (err != 0 && err != ENOENT)
			break;

next:
		if (xip) {
			iput(xip);
			xip = NULL;
			zfs_dirent_unlock(dl);
		}
		zap_cursor_advance(&zc);
	}

	if (tx)
		dmu_tx_abort(tx);
	if (xip) {
		iput(xip);
		zfs_dirent_unlock(dl);
	}
	zap_cursor_fini(&zc);

	return (err == ENOENT ? 0 : err);
}