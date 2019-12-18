#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_5__ {int /*<<< orphan*/  spa_props_lock; int /*<<< orphan*/  spa_config; } ;
typedef  TYPE_1__ spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 scalar_t__ INGLOBALZONE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curproc ; 
 int /*<<< orphan*/  fnvlist_add_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ spa_config_generation ; 
 int /*<<< orphan*/  spa_name (TYPE_1__*) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 TYPE_1__* spa_next (TYPE_1__*) ; 
 scalar_t__ zone_dataset_visible (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

nvlist_t *
spa_all_configs(uint64_t *generation)
{
	nvlist_t *pools;
	spa_t *spa = NULL;

	if (*generation == spa_config_generation)
		return (NULL);

	pools = fnvlist_alloc();

	mutex_enter(&spa_namespace_lock);
	while ((spa = spa_next(spa)) != NULL) {
		if (INGLOBALZONE(curproc) ||
		    zone_dataset_visible(spa_name(spa), NULL)) {
			mutex_enter(&spa->spa_props_lock);
			fnvlist_add_nvlist(pools, spa_name(spa),
			    spa->spa_config);
			mutex_exit(&spa->spa_props_lock);
		}
	}
	*generation = spa_config_generation;
	mutex_exit(&spa_namespace_lock);

	return (pools);
}