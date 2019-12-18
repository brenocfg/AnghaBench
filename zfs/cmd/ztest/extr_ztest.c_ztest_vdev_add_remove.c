#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int zs_vdev_next_leaf; scalar_t__ zs_mirrors; scalar_t__ zs_splits; } ;
typedef  TYPE_2__ ztest_shared_t ;
typedef  int /*<<< orphan*/  ztest_ds_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_9__ {TYPE_1__* mg_vd; struct TYPE_9__* mg_next; } ;
typedef  TYPE_3__ metaslab_group_t ;
struct TYPE_11__ {TYPE_3__* mc_rotor; } ;
struct TYPE_10__ {int zo_raidz; int /*<<< orphan*/  zo_vdev_size; scalar_t__ zo_mmp_test; } ;
struct TYPE_7__ {int vdev_guid; int /*<<< orphan*/  vdev_islog; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
#define  EACCES 133 
#define  EBUSY 132 
#define  EEXIST 131 
#define  ENOSPC 130 
 int /*<<< orphan*/  FTAG ; 
 int MAX (scalar_t__,int) ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  SCL_VDEV ; 
#define  ZFS_ERR_CHECKPOINT_EXISTS 129 
#define  ZFS_ERR_DISCARDING_CHECKPOINT 128 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * make_vdev_root (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,scalar_t__,int) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_rwlock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_rwlock_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_config_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_has_slogs (int /*<<< orphan*/ *) ; 
 TYPE_6__* spa_log_class (int /*<<< orphan*/ *) ; 
 int spa_num_top_vdevs (int /*<<< orphan*/ *) ; 
 int spa_vdev_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int spa_vdev_remove (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ztest_name_lock ; 
 TYPE_5__ ztest_opts ; 
 scalar_t__ ztest_random (int) ; 
 int /*<<< orphan*/  ztest_record_enospc (char*) ; 
 TYPE_2__* ztest_shared ; 
 int /*<<< orphan*/ * ztest_spa ; 
 int /*<<< orphan*/  ztest_vdev_lock ; 

void
ztest_vdev_add_remove(ztest_ds_t *zd, uint64_t id)
{
	ztest_shared_t *zs = ztest_shared;
	spa_t *spa = ztest_spa;
	uint64_t leaves;
	uint64_t guid;
	nvlist_t *nvroot;
	int error;

	if (ztest_opts.zo_mmp_test)
		return;

	mutex_enter(&ztest_vdev_lock);
	leaves = MAX(zs->zs_mirrors + zs->zs_splits, 1) * ztest_opts.zo_raidz;

	spa_config_enter(spa, SCL_VDEV, FTAG, RW_READER);

	ztest_shared->zs_vdev_next_leaf = spa_num_top_vdevs(spa) * leaves;

	/*
	 * If we have slogs then remove them 1/4 of the time.
	 */
	if (spa_has_slogs(spa) && ztest_random(4) == 0) {
		metaslab_group_t *mg;

		/*
		 * find the first real slog in log allocation class
		 */
		mg =  spa_log_class(spa)->mc_rotor;
		while (!mg->mg_vd->vdev_islog)
			mg = mg->mg_next;

		guid = mg->mg_vd->vdev_guid;

		spa_config_exit(spa, SCL_VDEV, FTAG);

		/*
		 * We have to grab the zs_name_lock as writer to
		 * prevent a race between removing a slog (dmu_objset_find)
		 * and destroying a dataset. Removing the slog will
		 * grab a reference on the dataset which may cause
		 * dsl_destroy_head() to fail with EBUSY thus
		 * leaving the dataset in an inconsistent state.
		 */
		pthread_rwlock_wrlock(&ztest_name_lock);
		error = spa_vdev_remove(spa, guid, B_FALSE);
		pthread_rwlock_unlock(&ztest_name_lock);

		switch (error) {
		case 0:
		case EEXIST:	/* Generic zil_reset() error */
		case EBUSY:	/* Replay required */
		case EACCES:	/* Crypto key not loaded */
		case ZFS_ERR_CHECKPOINT_EXISTS:
		case ZFS_ERR_DISCARDING_CHECKPOINT:
			break;
		default:
			fatal(0, "spa_vdev_remove() = %d", error);
		}
	} else {
		spa_config_exit(spa, SCL_VDEV, FTAG);

		/*
		 * Make 1/4 of the devices be log devices
		 */
		nvroot = make_vdev_root(NULL, NULL, NULL,
		    ztest_opts.zo_vdev_size, 0, (ztest_random(4) == 0) ?
		    "log" : NULL, ztest_opts.zo_raidz, zs->zs_mirrors, 1);

		error = spa_vdev_add(spa, nvroot);
		nvlist_free(nvroot);

		switch (error) {
		case 0:
			break;
		case ENOSPC:
			ztest_record_enospc("spa_vdev_add");
			break;
		default:
			fatal(0, "spa_vdev_add() = %d", error);
		}
	}

	mutex_exit(&ztest_vdev_lock);
}