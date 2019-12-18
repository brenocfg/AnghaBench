#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {unsigned long long zs_metaslab_sz; } ;
typedef  TYPE_3__ ztest_shared_t ;
struct TYPE_14__ {TYPE_2__* spa_root_vdev; } ;
typedef  TYPE_4__ spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_15__ {int paths; char** path; int /*<<< orphan*/  can_be_active; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_5__ importargs_t ;
struct TYPE_16__ {char* zo_pool; char* zo_dir; int /*<<< orphan*/  zo_mmp_test; } ;
struct TYPE_12__ {TYPE_1__** vdev_child; } ;
struct TYPE_11__ {unsigned long long vdev_ms_shift; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int FREAD ; 
 int /*<<< orphan*/  FTAG ; 
 int FWRITE ; 
 int /*<<< orphan*/  MUTEX_DEFAULT ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int ZFS_IMPORT_MISSING_LOG ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kernel_fini () ; 
 int /*<<< orphan*/  kernel_init (int) ; 
 int /*<<< orphan*/  libzpool_config_ops ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_rwlock_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_rwlock_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_close (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_import (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spa_open (char*,TYPE_4__**,int /*<<< orphan*/ ) ; 
 int zpool_find_config (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ztest_checkpoint_lock ; 
 int /*<<< orphan*/  ztest_freeze () ; 
 int /*<<< orphan*/  ztest_name_lock ; 
 TYPE_6__ ztest_opts ; 
 int /*<<< orphan*/  ztest_run_zdb (char*) ; 
 int /*<<< orphan*/  ztest_vdev_lock ; 

__attribute__((used)) static void
ztest_import(ztest_shared_t *zs)
{
	importargs_t args = { 0 };
	spa_t *spa;
	nvlist_t *cfg = NULL;
	int nsearch = 1;
	char *searchdirs[nsearch];
	char *name = ztest_opts.zo_pool;
	int flags = ZFS_IMPORT_MISSING_LOG;
	int error;

	mutex_init(&ztest_vdev_lock, NULL, MUTEX_DEFAULT, NULL);
	mutex_init(&ztest_checkpoint_lock, NULL, MUTEX_DEFAULT, NULL);
	VERIFY0(pthread_rwlock_init(&ztest_name_lock, NULL));

	kernel_init(FREAD | FWRITE);

	searchdirs[0] = ztest_opts.zo_dir;
	args.paths = nsearch;
	args.path = searchdirs;
	args.can_be_active = B_FALSE;

	error = zpool_find_config(NULL, name, &cfg, &args,
	    &libzpool_config_ops);
	if (error)
		(void) fatal(0, "No pools found\n");

	VERIFY0(spa_import(name, cfg, NULL, flags));
	VERIFY0(spa_open(name, &spa, FTAG));
	zs->zs_metaslab_sz =
	    1ULL << spa->spa_root_vdev->vdev_child[0]->vdev_ms_shift;
	spa_close(spa, FTAG);

	kernel_fini();

	if (!ztest_opts.zo_mmp_test) {
		ztest_run_zdb(ztest_opts.zo_pool);
		ztest_freeze();
		ztest_run_zdb(ztest_opts.zo_pool);
	}

	(void) pthread_rwlock_destroy(&ztest_name_lock);
	mutex_destroy(&ztest_vdev_lock);
	mutex_destroy(&ztest_checkpoint_lock);
}