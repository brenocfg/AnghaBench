#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ztest_ds_t ;
struct TYPE_10__ {int vdev_guid; int /*<<< orphan*/ * vdev_trim_thread; int /*<<< orphan*/  vdev_path; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int uint64_t ;
struct TYPE_11__ {int /*<<< orphan*/  spa_root_vdev; } ;
typedef  TYPE_2__ spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int boolean_t ;
struct TYPE_12__ {int zo_verbose; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
#define  POOL_TRIM_CANCEL 130 
 int POOL_TRIM_FUNCS ; 
#define  POOL_TRIM_START 129 
#define  POOL_TRIM_SUSPEND 128 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  SCL_VDEV ; 
 int /*<<< orphan*/  fnvlist_add_uint64 (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  spa_config_enter (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int spa_vdev_trim (TYPE_2__*,int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ *) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_dbgmsg (char*,TYPE_1__*,int) ; 
 TYPE_5__ ztest_opts ; 
 int ztest_random (int) ; 
 TYPE_1__* ztest_random_concrete_vdev_leaf (int /*<<< orphan*/ ) ; 
 TYPE_2__* ztest_spa ; 
 int /*<<< orphan*/  ztest_vdev_lock ; 

void
ztest_trim(ztest_ds_t *zd, uint64_t id)
{
	spa_t *spa = ztest_spa;
	int error = 0;

	mutex_enter(&ztest_vdev_lock);

	spa_config_enter(spa, SCL_VDEV, FTAG, RW_READER);

	/* Random leaf vdev */
	vdev_t *rand_vd = ztest_random_concrete_vdev_leaf(spa->spa_root_vdev);
	if (rand_vd == NULL) {
		spa_config_exit(spa, SCL_VDEV, FTAG);
		mutex_exit(&ztest_vdev_lock);
		return;
	}

	/*
	 * The random vdev we've selected may change as soon as we
	 * drop the spa_config_lock. We create local copies of things
	 * we're interested in.
	 */
	uint64_t guid = rand_vd->vdev_guid;
	char *path = strdup(rand_vd->vdev_path);
	boolean_t active = rand_vd->vdev_trim_thread != NULL;

	zfs_dbgmsg("vd %p, guid %llu", rand_vd, guid);
	spa_config_exit(spa, SCL_VDEV, FTAG);

	uint64_t cmd = ztest_random(POOL_TRIM_FUNCS);
	uint64_t rate = 1 << ztest_random(30);
	boolean_t partial = (ztest_random(5) > 0);
	boolean_t secure = (ztest_random(5) > 0);

	nvlist_t *vdev_guids = fnvlist_alloc();
	nvlist_t *vdev_errlist = fnvlist_alloc();
	fnvlist_add_uint64(vdev_guids, path, guid);
	error = spa_vdev_trim(spa, vdev_guids, cmd, rate, partial,
	    secure, vdev_errlist);
	fnvlist_free(vdev_guids);
	fnvlist_free(vdev_errlist);

	switch (cmd) {
	case POOL_TRIM_CANCEL:
		if (ztest_opts.zo_verbose >= 4) {
			(void) printf("Cancel TRIM %s", path);
			if (!active)
				(void) printf(" failed (no TRIM active)");
			(void) printf("\n");
		}
		break;
	case POOL_TRIM_START:
		if (ztest_opts.zo_verbose >= 4) {
			(void) printf("Start TRIM %s", path);
			if (active && error == 0)
				(void) printf(" failed (already active)");
			else if (error != 0)
				(void) printf(" failed (error %d)", error);
			(void) printf("\n");
		}
		break;
	case POOL_TRIM_SUSPEND:
		if (ztest_opts.zo_verbose >= 4) {
			(void) printf("Suspend TRIM %s", path);
			if (!active)
				(void) printf(" failed (no TRIM active)");
			(void) printf("\n");
		}
		break;
	}
	free(path);
	mutex_exit(&ztest_vdev_lock);
}