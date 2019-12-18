#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  z_lock; int /*<<< orphan*/  z_sa_hdl; int /*<<< orphan*/  z_pflags; int /*<<< orphan*/  z_size; int /*<<< orphan*/  z_id; int /*<<< orphan*/  z_mode; scalar_t__ z_unlinked; } ;
typedef  TYPE_1__ znode_t ;
struct TYPE_21__ {int /*<<< orphan*/  z_os; } ;
typedef  TYPE_2__ zfsvfs_t ;
struct TYPE_22__ {int /*<<< orphan*/  dl_name; TYPE_1__* dl_dzp; } ;
typedef  TYPE_3__ zfs_dirlock_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  sa_bulk_attr_t ;
typedef  int /*<<< orphan*/  mtime ;
typedef  int /*<<< orphan*/  links ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  ctime ;
struct TYPE_23__ {int /*<<< orphan*/  i_nlink; int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  CONTENT_MODIFIED ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  SA_ADD_BULK_ATTR (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SA_ZPL_CTIME (TYPE_2__*) ; 
 int /*<<< orphan*/  SA_ZPL_FLAGS (TYPE_2__*) ; 
 int /*<<< orphan*/  SA_ZPL_LINKS (TYPE_2__*) ; 
 int /*<<< orphan*/  SA_ZPL_MTIME (TYPE_2__*) ; 
 int /*<<< orphan*/  SA_ZPL_PARENT (TYPE_2__*) ; 
 int /*<<< orphan*/  SA_ZPL_SIZE (TYPE_2__*) ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATE_CHANGED ; 
 int S_ISDIR (int /*<<< orphan*/ ) ; 
 int ZEXISTS ; 
 int ZNEW ; 
 int ZRENAMING ; 
 TYPE_8__* ZTOI (TYPE_1__*) ; 
 TYPE_2__* ZTOZSB (TYPE_1__*) ; 
 int /*<<< orphan*/  drop_nlink (TYPE_8__*) ; 
 int /*<<< orphan*/  inc_nlink (TYPE_8__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int sa_bulk_update (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int zap_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_dirent (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_tstamp_update_setup (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
zfs_link_create(zfs_dirlock_t *dl, znode_t *zp, dmu_tx_t *tx, int flag)
{
	znode_t *dzp = dl->dl_dzp;
	zfsvfs_t *zfsvfs = ZTOZSB(zp);
	uint64_t value;
	int zp_is_dir = S_ISDIR(ZTOI(zp)->i_mode);
	sa_bulk_attr_t bulk[5];
	uint64_t mtime[2], ctime[2];
	uint64_t links;
	int count = 0;
	int error;

	mutex_enter(&zp->z_lock);

	if (!(flag & ZRENAMING)) {
		if (zp->z_unlinked) {	/* no new links to unlinked zp */
			ASSERT(!(flag & (ZNEW | ZEXISTS)));
			mutex_exit(&zp->z_lock);
			return (SET_ERROR(ENOENT));
		}
		if (!(flag & ZNEW)) {
			/*
			 * ZNEW nodes come from zfs_mknode() where the link
			 * count has already been initialised
			 */
			inc_nlink(ZTOI(zp));
			links = ZTOI(zp)->i_nlink;
			SA_ADD_BULK_ATTR(bulk, count, SA_ZPL_LINKS(zfsvfs),
			    NULL, &links, sizeof (links));
		}
	}

	value = zfs_dirent(zp, zp->z_mode);
	error = zap_add(ZTOZSB(zp)->z_os, dzp->z_id, dl->dl_name, 8, 1,
	    &value, tx);

	/*
	 * zap_add could fail to add the entry if it exceeds the capacity of the
	 * leaf-block and zap_leaf_split() failed to help.
	 * The caller of this routine is responsible for failing the transaction
	 * which will rollback the SA updates done above.
	 */
	if (error != 0) {
		if (!(flag & ZRENAMING) && !(flag & ZNEW))
			drop_nlink(ZTOI(zp));
		mutex_exit(&zp->z_lock);
		return (error);
	}

	SA_ADD_BULK_ATTR(bulk, count, SA_ZPL_PARENT(zfsvfs), NULL,
	    &dzp->z_id, sizeof (dzp->z_id));
	SA_ADD_BULK_ATTR(bulk, count, SA_ZPL_FLAGS(zfsvfs), NULL,
	    &zp->z_pflags, sizeof (zp->z_pflags));

	if (!(flag & ZNEW)) {
		SA_ADD_BULK_ATTR(bulk, count, SA_ZPL_CTIME(zfsvfs), NULL,
		    ctime, sizeof (ctime));
		zfs_tstamp_update_setup(zp, STATE_CHANGED, mtime,
		    ctime);
	}
	error = sa_bulk_update(zp->z_sa_hdl, bulk, count, tx);
	ASSERT(error == 0);

	mutex_exit(&zp->z_lock);

	mutex_enter(&dzp->z_lock);
	dzp->z_size++;
	if (zp_is_dir)
		inc_nlink(ZTOI(dzp));
	links = ZTOI(dzp)->i_nlink;
	count = 0;
	SA_ADD_BULK_ATTR(bulk, count, SA_ZPL_SIZE(zfsvfs), NULL,
	    &dzp->z_size, sizeof (dzp->z_size));
	SA_ADD_BULK_ATTR(bulk, count, SA_ZPL_LINKS(zfsvfs), NULL,
	    &links, sizeof (links));
	SA_ADD_BULK_ATTR(bulk, count, SA_ZPL_MTIME(zfsvfs), NULL,
	    mtime, sizeof (mtime));
	SA_ADD_BULK_ATTR(bulk, count, SA_ZPL_CTIME(zfsvfs), NULL,
	    ctime, sizeof (ctime));
	SA_ADD_BULK_ATTR(bulk, count, SA_ZPL_FLAGS(zfsvfs), NULL,
	    &dzp->z_pflags, sizeof (dzp->z_pflags));
	zfs_tstamp_update_setup(dzp, CONTENT_MODIFIED, mtime, ctime);
	error = sa_bulk_update(dzp->z_sa_hdl, bulk, count, tx);
	ASSERT(error == 0);
	mutex_exit(&dzp->z_lock);

	return (0);
}