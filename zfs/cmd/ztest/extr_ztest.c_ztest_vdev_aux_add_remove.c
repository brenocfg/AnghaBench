#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ zs_vdev_aux; } ;
typedef  TYPE_2__ ztest_shared_t ;
typedef  int /*<<< orphan*/  ztest_ds_t ;
typedef  int /*<<< orphan*/  vdev_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_16__ {int sav_count; TYPE_1__** sav_vdevs; } ;
struct TYPE_15__ {TYPE_4__ spa_l2cache; TYPE_4__ spa_spares; int /*<<< orphan*/ * spa_root_vdev; } ;
typedef  TYPE_3__ spa_t ;
typedef  TYPE_4__ spa_aux_vdev_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_17__ {int zo_vdev_size; int /*<<< orphan*/  zo_pool; int /*<<< orphan*/  zo_dir; scalar_t__ zo_mmp_test; } ;
struct TYPE_13__ {scalar_t__ vdev_guid; int /*<<< orphan*/  vdev_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
#define  EBUSY 130 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  MAXPATHLEN ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  SCL_VDEV ; 
 int /*<<< orphan*/  UMEM_NOFAIL ; 
#define  ZFS_ERR_CHECKPOINT_EXISTS 129 
#define  ZFS_ERR_DISCARDING_CHECKPOINT 128 
 char* ZPOOL_CONFIG_L2CACHE ; 
 char* ZPOOL_CONFIG_SPARES ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,char*,scalar_t__,int) ; 
 int /*<<< orphan*/ * make_vdev_root (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  spa_config_enter (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int spa_vdev_add (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int spa_vdev_remove (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 char* umem_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umem_free (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vdev_lookup_by_path (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vdev_online (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* ztest_aux_template ; 
 TYPE_7__ ztest_opts ; 
 size_t ztest_random (int) ; 
 TYPE_2__* ztest_shared ; 
 TYPE_3__* ztest_spa ; 
 int /*<<< orphan*/  ztest_vdev_lock ; 

void
ztest_vdev_aux_add_remove(ztest_ds_t *zd, uint64_t id)
{
	ztest_shared_t *zs = ztest_shared;
	spa_t *spa = ztest_spa;
	vdev_t *rvd = spa->spa_root_vdev;
	spa_aux_vdev_t *sav;
	char *aux;
	char *path;
	uint64_t guid = 0;
	int error;

	if (ztest_opts.zo_mmp_test)
		return;

	path = umem_alloc(MAXPATHLEN, UMEM_NOFAIL);

	if (ztest_random(2) == 0) {
		sav = &spa->spa_spares;
		aux = ZPOOL_CONFIG_SPARES;
	} else {
		sav = &spa->spa_l2cache;
		aux = ZPOOL_CONFIG_L2CACHE;
	}

	mutex_enter(&ztest_vdev_lock);

	spa_config_enter(spa, SCL_VDEV, FTAG, RW_READER);

	if (sav->sav_count != 0 && ztest_random(4) == 0) {
		/*
		 * Pick a random device to remove.
		 */
		guid = sav->sav_vdevs[ztest_random(sav->sav_count)]->vdev_guid;
	} else {
		/*
		 * Find an unused device we can add.
		 */
		zs->zs_vdev_aux = 0;
		for (;;) {
			int c;
			(void) snprintf(path, MAXPATHLEN, ztest_aux_template,
			    ztest_opts.zo_dir, ztest_opts.zo_pool, aux,
			    zs->zs_vdev_aux);
			for (c = 0; c < sav->sav_count; c++)
				if (strcmp(sav->sav_vdevs[c]->vdev_path,
				    path) == 0)
					break;
			if (c == sav->sav_count &&
			    vdev_lookup_by_path(rvd, path) == NULL)
				break;
			zs->zs_vdev_aux++;
		}
	}

	spa_config_exit(spa, SCL_VDEV, FTAG);

	if (guid == 0) {
		/*
		 * Add a new device.
		 */
		nvlist_t *nvroot = make_vdev_root(NULL, aux, NULL,
		    (ztest_opts.zo_vdev_size * 5) / 4, 0, NULL, 0, 0, 1);
		error = spa_vdev_add(spa, nvroot);

		switch (error) {
		case 0:
			break;
		default:
			fatal(0, "spa_vdev_add(%p) = %d", nvroot, error);
		}
		nvlist_free(nvroot);
	} else {
		/*
		 * Remove an existing device.  Sometimes, dirty its
		 * vdev state first to make sure we handle removal
		 * of devices that have pending state changes.
		 */
		if (ztest_random(2) == 0)
			(void) vdev_online(spa, guid, 0, NULL);

		error = spa_vdev_remove(spa, guid, B_FALSE);

		switch (error) {
		case 0:
		case EBUSY:
		case ZFS_ERR_CHECKPOINT_EXISTS:
		case ZFS_ERR_DISCARDING_CHECKPOINT:
			break;
		default:
			fatal(0, "spa_vdev_remove(%llu) = %d", guid, error);
		}
	}

	mutex_exit(&ztest_vdev_lock);

	umem_free(path, MAXPATHLEN);
}