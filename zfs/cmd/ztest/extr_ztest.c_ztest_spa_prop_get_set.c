#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ztest_ds_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_2__ {int zo_verbose; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZPOOL_PROP_AUTOTRIM ; 
 int /*<<< orphan*/  dump_nvlist (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_rwlock_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_rwlock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_prop_get (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ztest_name_lock ; 
 TYPE_1__ ztest_opts ; 
 int /*<<< orphan*/  ztest_random (int) ; 
 int /*<<< orphan*/  ztest_spa ; 
 int /*<<< orphan*/  ztest_spa_prop_set_uint64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ztest_spa_prop_get_set(ztest_ds_t *zd, uint64_t id)
{
	nvlist_t *props = NULL;

	(void) pthread_rwlock_rdlock(&ztest_name_lock);

	(void) ztest_spa_prop_set_uint64(ZPOOL_PROP_AUTOTRIM, ztest_random(2));

	VERIFY0(spa_prop_get(ztest_spa, &props));

	if (ztest_opts.zo_verbose >= 6)
		dump_nvlist(props, 4);

	nvlist_free(props);

	(void) pthread_rwlock_unlock(&ztest_name_lock);
}