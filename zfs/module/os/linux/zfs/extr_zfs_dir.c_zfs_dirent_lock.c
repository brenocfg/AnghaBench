#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zoid ;
struct TYPE_16__ {int /*<<< orphan*/  z_sa_hdl; int /*<<< orphan*/  z_lock; TYPE_3__* z_dirlocks; int /*<<< orphan*/  z_name_lock; scalar_t__ z_unlinked; } ;
typedef  TYPE_1__ znode_t ;
struct TYPE_17__ {int z_norm; scalar_t__ z_case; } ;
typedef  TYPE_2__ zfsvfs_t ;
struct TYPE_18__ {char* dl_name; int dl_sharecnt; int dl_namelock; int dl_namesize; int /*<<< orphan*/  dl_cv; struct TYPE_18__* dl_next; TYPE_1__* dl_dzp; } ;
typedef  TYPE_3__ zfs_dirlock_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  pathname_t ;
typedef  int /*<<< orphan*/  matchtype_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  CV_DEFAULT ; 
 int EEXIST ; 
 int ENOENT ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  MT_MATCH_CASE ; 
 int /*<<< orphan*/  MT_NORMALIZE ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  SA_ZPL_XATTR (TYPE_2__*) ; 
 int SET_ERROR (int) ; 
 int U8_TEXTPREP_TOUPPER ; 
 int /*<<< orphan*/  U8_UNICODE_LATEST ; 
 int ZCIEXACT ; 
 int ZCILOOK ; 
 int ZEXISTS ; 
 scalar_t__ ZFS_CASE_INSENSITIVE ; 
 scalar_t__ ZFS_CASE_MIXED ; 
 int /*<<< orphan*/  ZFS_CTLDIR_NAME ; 
 int ZHAVELOCK ; 
 int ZNEW ; 
 int ZRENAMING ; 
 int ZSHARED ; 
 TYPE_2__* ZTOZSB (TYPE_1__*) ; 
 int ZXATTR ; 
 int /*<<< orphan*/  bcopy (char*,char*,int) ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 int sa_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 scalar_t__ u8_strcmp (char*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  zfs_dirent_unlock (TYPE_3__*) ; 
 scalar_t__ zfs_has_ctldir (TYPE_1__*) ; 
 int zfs_match_find (TYPE_2__*,TYPE_1__*,char*,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int zfs_zget (TYPE_2__*,scalar_t__,TYPE_1__**) ; 

int
zfs_dirent_lock(zfs_dirlock_t **dlpp, znode_t *dzp, char *name, znode_t **zpp,
    int flag, int *direntflags, pathname_t *realpnp)
{
	zfsvfs_t	*zfsvfs = ZTOZSB(dzp);
	zfs_dirlock_t	*dl;
	boolean_t	update;
	matchtype_t	mt = 0;
	uint64_t	zoid;
	int		error = 0;
	int		cmpflags;

	*zpp = NULL;
	*dlpp = NULL;

	/*
	 * Verify that we are not trying to lock '.', '..', or '.zfs'
	 */
	if ((name[0] == '.' &&
	    (name[1] == '\0' || (name[1] == '.' && name[2] == '\0'))) ||
	    (zfs_has_ctldir(dzp) && strcmp(name, ZFS_CTLDIR_NAME) == 0))
		return (SET_ERROR(EEXIST));

	/*
	 * Case sensitivity and normalization preferences are set when
	 * the file system is created.  These are stored in the
	 * zfsvfs->z_case and zfsvfs->z_norm fields.  These choices
	 * affect what vnodes can be cached in the DNLC, how we
	 * perform zap lookups, and the "width" of our dirlocks.
	 *
	 * A normal dirlock locks a single name.  Note that with
	 * normalization a name can be composed multiple ways, but
	 * when normalized, these names all compare equal.  A wide
	 * dirlock locks multiple names.  We need these when the file
	 * system is supporting mixed-mode access.  It is sometimes
	 * necessary to lock all case permutations of file name at
	 * once so that simultaneous case-insensitive/case-sensitive
	 * behaves as rationally as possible.
	 */

	/*
	 * When matching we may need to normalize & change case according to
	 * FS settings.
	 *
	 * Note that a normalized match is necessary for a case insensitive
	 * filesystem when the lookup request is not exact because normalization
	 * can fold case independent of normalizing code point sequences.
	 *
	 * See the table above zfs_dropname().
	 */
	if (zfsvfs->z_norm != 0) {
		mt = MT_NORMALIZE;

		/*
		 * Determine if the match needs to honor the case specified in
		 * lookup, and if so keep track of that so that during
		 * normalization we don't fold case.
		 */
		if ((zfsvfs->z_case == ZFS_CASE_INSENSITIVE &&
		    (flag & ZCIEXACT)) ||
		    (zfsvfs->z_case == ZFS_CASE_MIXED && !(flag & ZCILOOK))) {
			mt |= MT_MATCH_CASE;
		}
	}

	/*
	 * Only look in or update the DNLC if we are looking for the
	 * name on a file system that does not require normalization
	 * or case folding.  We can also look there if we happen to be
	 * on a non-normalizing, mixed sensitivity file system IF we
	 * are looking for the exact name.
	 *
	 * Maybe can add TO-UPPERed version of name to dnlc in ci-only
	 * case for performance improvement?
	 */
	update = !zfsvfs->z_norm ||
	    (zfsvfs->z_case == ZFS_CASE_MIXED &&
	    !(zfsvfs->z_norm & ~U8_TEXTPREP_TOUPPER) && !(flag & ZCILOOK));

	/*
	 * ZRENAMING indicates we are in a situation where we should
	 * take narrow locks regardless of the file system's
	 * preferences for normalizing and case folding.  This will
	 * prevent us deadlocking trying to grab the same wide lock
	 * twice if the two names happen to be case-insensitive
	 * matches.
	 */
	if (flag & ZRENAMING)
		cmpflags = 0;
	else
		cmpflags = zfsvfs->z_norm;

	/*
	 * Wait until there are no locks on this name.
	 *
	 * Don't grab the lock if it is already held. However, cannot
	 * have both ZSHARED and ZHAVELOCK together.
	 */
	ASSERT(!(flag & ZSHARED) || !(flag & ZHAVELOCK));
	if (!(flag & ZHAVELOCK))
		rw_enter(&dzp->z_name_lock, RW_READER);

	mutex_enter(&dzp->z_lock);
	for (;;) {
		if (dzp->z_unlinked && !(flag & ZXATTR)) {
			mutex_exit(&dzp->z_lock);
			if (!(flag & ZHAVELOCK))
				rw_exit(&dzp->z_name_lock);
			return (SET_ERROR(ENOENT));
		}
		for (dl = dzp->z_dirlocks; dl != NULL; dl = dl->dl_next) {
			if ((u8_strcmp(name, dl->dl_name, 0, cmpflags,
			    U8_UNICODE_LATEST, &error) == 0) || error != 0)
				break;
		}
		if (error != 0) {
			mutex_exit(&dzp->z_lock);
			if (!(flag & ZHAVELOCK))
				rw_exit(&dzp->z_name_lock);
			return (SET_ERROR(ENOENT));
		}
		if (dl == NULL)	{
			/*
			 * Allocate a new dirlock and add it to the list.
			 */
			dl = kmem_alloc(sizeof (zfs_dirlock_t), KM_SLEEP);
			cv_init(&dl->dl_cv, NULL, CV_DEFAULT, NULL);
			dl->dl_name = name;
			dl->dl_sharecnt = 0;
			dl->dl_namelock = 0;
			dl->dl_namesize = 0;
			dl->dl_dzp = dzp;
			dl->dl_next = dzp->z_dirlocks;
			dzp->z_dirlocks = dl;
			break;
		}
		if ((flag & ZSHARED) && dl->dl_sharecnt != 0)
			break;
		cv_wait(&dl->dl_cv, &dzp->z_lock);
	}

	/*
	 * If the z_name_lock was NOT held for this dirlock record it.
	 */
	if (flag & ZHAVELOCK)
		dl->dl_namelock = 1;

	if ((flag & ZSHARED) && ++dl->dl_sharecnt > 1 && dl->dl_namesize == 0) {
		/*
		 * We're the second shared reference to dl.  Make a copy of
		 * dl_name in case the first thread goes away before we do.
		 * Note that we initialize the new name before storing its
		 * pointer into dl_name, because the first thread may load
		 * dl->dl_name at any time.  It'll either see the old value,
		 * which belongs to it, or the new shared copy; either is OK.
		 */
		dl->dl_namesize = strlen(dl->dl_name) + 1;
		name = kmem_alloc(dl->dl_namesize, KM_SLEEP);
		bcopy(dl->dl_name, name, dl->dl_namesize);
		dl->dl_name = name;
	}

	mutex_exit(&dzp->z_lock);

	/*
	 * We have a dirlock on the name.  (Note that it is the dirlock,
	 * not the dzp's z_lock, that protects the name in the zap object.)
	 * See if there's an object by this name; if so, put a hold on it.
	 */
	if (flag & ZXATTR) {
		error = sa_lookup(dzp->z_sa_hdl, SA_ZPL_XATTR(zfsvfs), &zoid,
		    sizeof (zoid));
		if (error == 0)
			error = (zoid == 0 ? SET_ERROR(ENOENT) : 0);
	} else {
		error = zfs_match_find(zfsvfs, dzp, name, mt,
		    update, direntflags, realpnp, &zoid);
	}
	if (error) {
		if (error != ENOENT || (flag & ZEXISTS)) {
			zfs_dirent_unlock(dl);
			return (error);
		}
	} else {
		if (flag & ZNEW) {
			zfs_dirent_unlock(dl);
			return (SET_ERROR(EEXIST));
		}
		error = zfs_zget(zfsvfs, zoid, zpp);
		if (error) {
			zfs_dirent_unlock(dl);
			return (error);
		}
	}

	*dlpp = dl;

	return (0);
}