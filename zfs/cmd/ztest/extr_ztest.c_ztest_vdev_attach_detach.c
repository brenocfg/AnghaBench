#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
struct TYPE_21__ {int zs_mirrors; } ;
typedef  TYPE_2__ ztest_shared_t ;
typedef  int /*<<< orphan*/  ztest_ds_t ;
struct TYPE_22__ {int vdev_children; size_t vdev_guid; TYPE_1__* vdev_top; int /*<<< orphan*/ * vdev_ops; int /*<<< orphan*/  vdev_path; struct TYPE_22__* vdev_parent; struct TYPE_22__** vdev_child; } ;
typedef  TYPE_3__ vdev_t ;
typedef  size_t uint64_t ;
struct TYPE_24__ {int sav_count; TYPE_3__** sav_vdevs; } ;
struct TYPE_23__ {TYPE_3__* spa_root_vdev; TYPE_5__ spa_spares; } ;
typedef  TYPE_4__ spa_t ;
typedef  TYPE_5__ spa_aux_vdev_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_20__ {int vdev_islog; size_t vdev_ashift; } ;
struct TYPE_19__ {size_t zo_raidz; int /*<<< orphan*/  zo_pool; int /*<<< orphan*/  zo_dir; scalar_t__ zo_mmp_test; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int B_FALSE ; 
 int B_TRUE ; 
 int EBUSY ; 
 int EDOM ; 
 int ENODEV ; 
 int ENOTSUP ; 
 int EOVERFLOW ; 
 int /*<<< orphan*/  FTAG ; 
 size_t MAX (int,int) ; 
 int /*<<< orphan*/  MAXPATHLEN ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  SCL_ALL ; 
 int /*<<< orphan*/  UMEM_NOFAIL ; 
 int ZFS_ERR_CHECKPOINT_EXISTS ; 
 int ZFS_ERR_DISCARDING_CHECKPOINT ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,char*,char*,size_t,...) ; 
 int /*<<< orphan*/ * make_vdev_root (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  spa_config_enter (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int spa_vdev_attach (TYPE_4__*,size_t,int /*<<< orphan*/ *,int) ; 
 int spa_vdev_detach (TYPE_4__*,size_t,size_t,int) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 char* umem_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umem_free (char*,int /*<<< orphan*/ ) ; 
 size_t vdev_get_min_asize (TYPE_3__*) ; 
 TYPE_3__* vdev_lookup_by_path (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  vdev_mirror_ops ; 
 int /*<<< orphan*/  vdev_raidz_ops ; 
 int /*<<< orphan*/  vdev_reopen (TYPE_3__*) ; 
 int /*<<< orphan*/  vdev_replacing_ops ; 
 int /*<<< orphan*/  vdev_root_ops ; 
 int /*<<< orphan*/  vdev_spare_ops ; 
 char* ztest_dev_template ; 
 scalar_t__ ztest_device_removal_active ; 
 size_t ztest_get_ashift () ; 
 TYPE_10__ ztest_opts ; 
 int ztest_random (int) ; 
 size_t ztest_random_vdev_top (TYPE_4__*,int) ; 
 int ztest_scrub_impl (TYPE_4__*) ; 
 TYPE_2__* ztest_shared ; 
 TYPE_4__* ztest_spa ; 
 int /*<<< orphan*/  ztest_vdev_lock ; 

void
ztest_vdev_attach_detach(ztest_ds_t *zd, uint64_t id)
{
	ztest_shared_t *zs = ztest_shared;
	spa_t *spa = ztest_spa;
	spa_aux_vdev_t *sav = &spa->spa_spares;
	vdev_t *rvd = spa->spa_root_vdev;
	vdev_t *oldvd, *newvd, *pvd;
	nvlist_t *root;
	uint64_t leaves;
	uint64_t leaf, top;
	uint64_t ashift = ztest_get_ashift();
	uint64_t oldguid, pguid;
	uint64_t oldsize, newsize;
	char *oldpath, *newpath;
	int replacing;
	int oldvd_has_siblings = B_FALSE;
	int newvd_is_spare = B_FALSE;
	int oldvd_is_log;
	int error, expected_error;

	if (ztest_opts.zo_mmp_test)
		return;

	oldpath = umem_alloc(MAXPATHLEN, UMEM_NOFAIL);
	newpath = umem_alloc(MAXPATHLEN, UMEM_NOFAIL);

	mutex_enter(&ztest_vdev_lock);
	leaves = MAX(zs->zs_mirrors, 1) * ztest_opts.zo_raidz;

	spa_config_enter(spa, SCL_ALL, FTAG, RW_WRITER);

	/*
	 * If a vdev is in the process of being removed, its removal may
	 * finish while we are in progress, leading to an unexpected error
	 * value.  Don't bother trying to attach while we are in the middle
	 * of removal.
	 */
	if (ztest_device_removal_active) {
		spa_config_exit(spa, SCL_ALL, FTAG);
		mutex_exit(&ztest_vdev_lock);
		return;
	}

	/*
	 * Decide whether to do an attach or a replace.
	 */
	replacing = ztest_random(2);

	/*
	 * Pick a random top-level vdev.
	 */
	top = ztest_random_vdev_top(spa, B_TRUE);

	/*
	 * Pick a random leaf within it.
	 */
	leaf = ztest_random(leaves);

	/*
	 * Locate this vdev.
	 */
	oldvd = rvd->vdev_child[top];

	/* pick a child from the mirror */
	if (zs->zs_mirrors >= 1) {
		ASSERT(oldvd->vdev_ops == &vdev_mirror_ops);
		ASSERT(oldvd->vdev_children >= zs->zs_mirrors);
		oldvd = oldvd->vdev_child[leaf / ztest_opts.zo_raidz];
	}

	/* pick a child out of the raidz group */
	if (ztest_opts.zo_raidz > 1) {
		ASSERT(oldvd->vdev_ops == &vdev_raidz_ops);
		ASSERT(oldvd->vdev_children == ztest_opts.zo_raidz);
		oldvd = oldvd->vdev_child[leaf % ztest_opts.zo_raidz];
	}

	/*
	 * If we're already doing an attach or replace, oldvd may be a
	 * mirror vdev -- in which case, pick a random child.
	 */
	while (oldvd->vdev_children != 0) {
		oldvd_has_siblings = B_TRUE;
		ASSERT(oldvd->vdev_children >= 2);
		oldvd = oldvd->vdev_child[ztest_random(oldvd->vdev_children)];
	}

	oldguid = oldvd->vdev_guid;
	oldsize = vdev_get_min_asize(oldvd);
	oldvd_is_log = oldvd->vdev_top->vdev_islog;
	(void) strcpy(oldpath, oldvd->vdev_path);
	pvd = oldvd->vdev_parent;
	pguid = pvd->vdev_guid;

	/*
	 * If oldvd has siblings, then half of the time, detach it.  Prior
	 * to the detach the pool is scrubbed in order to prevent creating
	 * unrepairable blocks as a result of the data corruption injection.
	 */
	if (oldvd_has_siblings && ztest_random(2) == 0) {
		spa_config_exit(spa, SCL_ALL, FTAG);

		error = ztest_scrub_impl(spa);
		if (error)
			goto out;

		error = spa_vdev_detach(spa, oldguid, pguid, B_FALSE);
		if (error != 0 && error != ENODEV && error != EBUSY &&
		    error != ENOTSUP && error != ZFS_ERR_CHECKPOINT_EXISTS &&
		    error != ZFS_ERR_DISCARDING_CHECKPOINT)
			fatal(0, "detach (%s) returned %d", oldpath, error);
		goto out;
	}

	/*
	 * For the new vdev, choose with equal probability between the two
	 * standard paths (ending in either 'a' or 'b') or a random hot spare.
	 */
	if (sav->sav_count != 0 && ztest_random(3) == 0) {
		newvd = sav->sav_vdevs[ztest_random(sav->sav_count)];
		newvd_is_spare = B_TRUE;
		(void) strcpy(newpath, newvd->vdev_path);
	} else {
		(void) snprintf(newpath, MAXPATHLEN, ztest_dev_template,
		    ztest_opts.zo_dir, ztest_opts.zo_pool,
		    top * leaves + leaf);
		if (ztest_random(2) == 0)
			newpath[strlen(newpath) - 1] = 'b';
		newvd = vdev_lookup_by_path(rvd, newpath);
	}

	if (newvd) {
		/*
		 * Reopen to ensure the vdev's asize field isn't stale.
		 */
		vdev_reopen(newvd);
		newsize = vdev_get_min_asize(newvd);
	} else {
		/*
		 * Make newsize a little bigger or smaller than oldsize.
		 * If it's smaller, the attach should fail.
		 * If it's larger, and we're doing a replace,
		 * we should get dynamic LUN growth when we're done.
		 */
		newsize = 10 * oldsize / (9 + ztest_random(3));
	}

	/*
	 * If pvd is not a mirror or root, the attach should fail with ENOTSUP,
	 * unless it's a replace; in that case any non-replacing parent is OK.
	 *
	 * If newvd is already part of the pool, it should fail with EBUSY.
	 *
	 * If newvd is too small, it should fail with EOVERFLOW.
	 */
	if (pvd->vdev_ops != &vdev_mirror_ops &&
	    pvd->vdev_ops != &vdev_root_ops && (!replacing ||
	    pvd->vdev_ops == &vdev_replacing_ops ||
	    pvd->vdev_ops == &vdev_spare_ops))
		expected_error = ENOTSUP;
	else if (newvd_is_spare && (!replacing || oldvd_is_log))
		expected_error = ENOTSUP;
	else if (newvd == oldvd)
		expected_error = replacing ? 0 : EBUSY;
	else if (vdev_lookup_by_path(rvd, newpath) != NULL)
		expected_error = EBUSY;
	else if (newsize < oldsize)
		expected_error = EOVERFLOW;
	else if (ashift > oldvd->vdev_top->vdev_ashift)
		expected_error = EDOM;
	else
		expected_error = 0;

	spa_config_exit(spa, SCL_ALL, FTAG);

	/*
	 * Build the nvlist describing newpath.
	 */
	root = make_vdev_root(newpath, NULL, NULL, newvd == NULL ? newsize : 0,
	    ashift, NULL, 0, 0, 1);

	error = spa_vdev_attach(spa, oldguid, root, replacing);

	nvlist_free(root);

	/*
	 * If our parent was the replacing vdev, but the replace completed,
	 * then instead of failing with ENOTSUP we may either succeed,
	 * fail with ENODEV, or fail with EOVERFLOW.
	 */
	if (expected_error == ENOTSUP &&
	    (error == 0 || error == ENODEV || error == EOVERFLOW))
		expected_error = error;

	/*
	 * If someone grew the LUN, the replacement may be too small.
	 */
	if (error == EOVERFLOW || error == EBUSY)
		expected_error = error;

	if (error == ZFS_ERR_CHECKPOINT_EXISTS ||
	    error == ZFS_ERR_DISCARDING_CHECKPOINT)
		expected_error = error;

	/* XXX workaround 6690467 */
	if (error != expected_error && expected_error != EBUSY) {
		fatal(0, "attach (%s %llu, %s %llu, %d) "
		    "returned %d, expected %d",
		    oldpath, oldsize, newpath,
		    newsize, replacing, error, expected_error);
	}
out:
	mutex_exit(&ztest_vdev_lock);

	umem_free(oldpath, MAXPATHLEN);
	umem_free(newpath, MAXPATHLEN);
}