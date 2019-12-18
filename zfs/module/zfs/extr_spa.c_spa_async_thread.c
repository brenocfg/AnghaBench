#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
struct TYPE_24__ {int sav_count; int /*<<< orphan*/ * sav_vdevs; } ;
struct TYPE_23__ {int sav_count; int /*<<< orphan*/ * sav_vdevs; } ;
struct TYPE_25__ {int spa_async_tasks; int /*<<< orphan*/  spa_async_lock; int /*<<< orphan*/  spa_async_cv; int /*<<< orphan*/ * spa_async_thread; int /*<<< orphan*/  spa_root_vdev; TYPE_2__ spa_spares; TYPE_1__ spa_l2cache; int /*<<< orphan*/  spa_sync_on; TYPE_4__* spa_dsl_pool; } ;
typedef  TYPE_3__ spa_t ;
struct TYPE_26__ {int /*<<< orphan*/  dp_spa; } ;
typedef  TYPE_4__ dsl_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  SCL_CONFIG ; 
 int /*<<< orphan*/  SCL_NONE ; 
 int SPA_ASYNC_AUTOEXPAND ; 
 int SPA_ASYNC_AUTOTRIM_RESTART ; 
 int SPA_ASYNC_CONFIG_UPDATE ; 
 int SPA_ASYNC_INITIALIZE_RESTART ; 
 int SPA_ASYNC_PROBE ; 
 int SPA_ASYNC_REMOVE ; 
 int SPA_ASYNC_RESILVER ; 
 int SPA_ASYNC_RESILVER_DONE ; 
 int SPA_ASYNC_TRIM_RESTART ; 
 int /*<<< orphan*/  SPA_CONFIG_UPDATE_POOL ; 
 int /*<<< orphan*/  SPA_FEATURE_RESILVER_DEFER ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_resilver_restart (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_scan_resilvering (TYPE_4__*) ; 
 scalar_t__ metaslab_class_get_space (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_async_autoexpand (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_async_probe (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_async_remove (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_enter (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_update (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_dedup_class (TYPE_3__*) ; 
 int /*<<< orphan*/  spa_feature_is_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_history_log_internal (TYPE_3__*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_name (TYPE_3__*) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 int /*<<< orphan*/  spa_normal_class (TYPE_3__*) ; 
 int /*<<< orphan*/  spa_special_class (TYPE_3__*) ; 
 int /*<<< orphan*/  spa_suspended (TYPE_3__*) ; 
 int /*<<< orphan*/  spa_vdev_resilver_done (TYPE_3__*) ; 
 int /*<<< orphan*/  spa_vdev_state_enter (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_vdev_state_exit (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_exit () ; 
 int /*<<< orphan*/  vdev_autotrim_restart (TYPE_3__*) ; 
 int /*<<< orphan*/  vdev_initialize_restart (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_trim_restart (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
spa_async_thread(void *arg)
{
	spa_t *spa = (spa_t *)arg;
	dsl_pool_t *dp = spa->spa_dsl_pool;
	int tasks;

	ASSERT(spa->spa_sync_on);

	mutex_enter(&spa->spa_async_lock);
	tasks = spa->spa_async_tasks;
	spa->spa_async_tasks = 0;
	mutex_exit(&spa->spa_async_lock);

	/*
	 * See if the config needs to be updated.
	 */
	if (tasks & SPA_ASYNC_CONFIG_UPDATE) {
		uint64_t old_space, new_space;

		mutex_enter(&spa_namespace_lock);
		old_space = metaslab_class_get_space(spa_normal_class(spa));
		old_space += metaslab_class_get_space(spa_special_class(spa));
		old_space += metaslab_class_get_space(spa_dedup_class(spa));

		spa_config_update(spa, SPA_CONFIG_UPDATE_POOL);

		new_space = metaslab_class_get_space(spa_normal_class(spa));
		new_space += metaslab_class_get_space(spa_special_class(spa));
		new_space += metaslab_class_get_space(spa_dedup_class(spa));
		mutex_exit(&spa_namespace_lock);

		/*
		 * If the pool grew as a result of the config update,
		 * then log an internal history event.
		 */
		if (new_space != old_space) {
			spa_history_log_internal(spa, "vdev online", NULL,
			    "pool '%s' size: %llu(+%llu)",
			    spa_name(spa), (u_longlong_t)new_space,
			    (u_longlong_t)(new_space - old_space));
		}
	}

	/*
	 * See if any devices need to be marked REMOVED.
	 */
	if (tasks & SPA_ASYNC_REMOVE) {
		spa_vdev_state_enter(spa, SCL_NONE);
		spa_async_remove(spa, spa->spa_root_vdev);
		for (int i = 0; i < spa->spa_l2cache.sav_count; i++)
			spa_async_remove(spa, spa->spa_l2cache.sav_vdevs[i]);
		for (int i = 0; i < spa->spa_spares.sav_count; i++)
			spa_async_remove(spa, spa->spa_spares.sav_vdevs[i]);
		(void) spa_vdev_state_exit(spa, NULL, 0);
	}

	if ((tasks & SPA_ASYNC_AUTOEXPAND) && !spa_suspended(spa)) {
		spa_config_enter(spa, SCL_CONFIG, FTAG, RW_READER);
		spa_async_autoexpand(spa, spa->spa_root_vdev);
		spa_config_exit(spa, SCL_CONFIG, FTAG);
	}

	/*
	 * See if any devices need to be probed.
	 */
	if (tasks & SPA_ASYNC_PROBE) {
		spa_vdev_state_enter(spa, SCL_NONE);
		spa_async_probe(spa, spa->spa_root_vdev);
		(void) spa_vdev_state_exit(spa, NULL, 0);
	}

	/*
	 * If any devices are done replacing, detach them.
	 */
	if (tasks & SPA_ASYNC_RESILVER_DONE)
		spa_vdev_resilver_done(spa);

	/*
	 * Kick off a resilver.
	 */
	if (tasks & SPA_ASYNC_RESILVER &&
	    (!dsl_scan_resilvering(dp) ||
	    !spa_feature_is_enabled(dp->dp_spa, SPA_FEATURE_RESILVER_DEFER)))
		dsl_resilver_restart(dp, 0);

	if (tasks & SPA_ASYNC_INITIALIZE_RESTART) {
		mutex_enter(&spa_namespace_lock);
		spa_config_enter(spa, SCL_CONFIG, FTAG, RW_READER);
		vdev_initialize_restart(spa->spa_root_vdev);
		spa_config_exit(spa, SCL_CONFIG, FTAG);
		mutex_exit(&spa_namespace_lock);
	}

	if (tasks & SPA_ASYNC_TRIM_RESTART) {
		mutex_enter(&spa_namespace_lock);
		spa_config_enter(spa, SCL_CONFIG, FTAG, RW_READER);
		vdev_trim_restart(spa->spa_root_vdev);
		spa_config_exit(spa, SCL_CONFIG, FTAG);
		mutex_exit(&spa_namespace_lock);
	}

	if (tasks & SPA_ASYNC_AUTOTRIM_RESTART) {
		mutex_enter(&spa_namespace_lock);
		spa_config_enter(spa, SCL_CONFIG, FTAG, RW_READER);
		vdev_autotrim_restart(spa);
		spa_config_exit(spa, SCL_CONFIG, FTAG);
		mutex_exit(&spa_namespace_lock);
	}

	/*
	 * Let the world know that we're done.
	 */
	mutex_enter(&spa->spa_async_lock);
	spa->spa_async_thread = NULL;
	cv_broadcast(&spa->spa_async_cv);
	mutex_exit(&spa->spa_async_lock);
	thread_exit();
}