#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_14__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_15__ {int /*<<< orphan*/  spa_suspended; int /*<<< orphan*/  spa_failmode; TYPE_1__ spa_loaded_ts; } ;
typedef  TYPE_2__ spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  SCL_CONFIG ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_ERRCOUNT ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_LOADED_TIME ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_SUSPENDED ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_SUSPENDED_REASON ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_add_uint64_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spa_add_feature_stats (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_add_l2cache (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_add_spares (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_altroot (TYPE_2__*,char*,size_t) ; 
 int /*<<< orphan*/  spa_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_enter (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_get_errlog_size (TYPE_2__*) ; 
 TYPE_2__* spa_lookup (char const*) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 int spa_open_common (char const*,TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ spa_suspended (TYPE_2__*) ; 

int
spa_get_stats(const char *name, nvlist_t **config,
    char *altroot, size_t buflen)
{
	int error;
	spa_t *spa;

	*config = NULL;
	error = spa_open_common(name, &spa, FTAG, NULL, config);

	if (spa != NULL) {
		/*
		 * This still leaves a window of inconsistency where the spares
		 * or l2cache devices could change and the config would be
		 * self-inconsistent.
		 */
		spa_config_enter(spa, SCL_CONFIG, FTAG, RW_READER);

		if (*config != NULL) {
			uint64_t loadtimes[2];

			loadtimes[0] = spa->spa_loaded_ts.tv_sec;
			loadtimes[1] = spa->spa_loaded_ts.tv_nsec;
			VERIFY(nvlist_add_uint64_array(*config,
			    ZPOOL_CONFIG_LOADED_TIME, loadtimes, 2) == 0);

			VERIFY(nvlist_add_uint64(*config,
			    ZPOOL_CONFIG_ERRCOUNT,
			    spa_get_errlog_size(spa)) == 0);

			if (spa_suspended(spa)) {
				VERIFY(nvlist_add_uint64(*config,
				    ZPOOL_CONFIG_SUSPENDED,
				    spa->spa_failmode) == 0);
				VERIFY(nvlist_add_uint64(*config,
				    ZPOOL_CONFIG_SUSPENDED_REASON,
				    spa->spa_suspended) == 0);
			}

			spa_add_spares(spa, *config);
			spa_add_l2cache(spa, *config);
			spa_add_feature_stats(spa, *config);
		}
	}

	/*
	 * We want to get the alternate root even for faulted pools, so we cheat
	 * and call spa_lookup() directly.
	 */
	if (altroot) {
		if (spa == NULL) {
			mutex_enter(&spa_namespace_lock);
			spa = spa_lookup(name);
			if (spa)
				spa_altroot(spa, altroot, buflen);
			else
				altroot[0] = '\0';
			spa = NULL;
			mutex_exit(&spa_namespace_lock);
		} else {
			spa_altroot(spa, altroot, buflen);
		}
	}

	if (spa != NULL) {
		spa_config_exit(spa, SCL_CONFIG, FTAG);
		spa_close(spa, FTAG);
	}

	return (error);
}