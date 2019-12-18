#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  os_lock; int /*<<< orphan*/  os_dnodes; int /*<<< orphan*/  os_spa; scalar_t__ os_sa; int /*<<< orphan*/ * os_dsl_dataset; } ;
typedef  TYPE_1__ objset_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int TXG_SIZE ; 
 int /*<<< orphan*/  dmu_objset_evict_dbufs (TYPE_1__*) ; 
 int /*<<< orphan*/  dmu_objset_evict_done (TYPE_1__*) ; 
 int /*<<< orphan*/  dmu_objset_is_dirty (TYPE_1__*,int) ; 
 int /*<<< orphan*/  dsl_prop_unregister_all (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ list_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sa_tear_down (TYPE_1__*) ; 
 int /*<<< orphan*/  spa_evicting_os_register (int /*<<< orphan*/ ,TYPE_1__*) ; 

void
dmu_objset_evict(objset_t *os)
{
	dsl_dataset_t *ds = os->os_dsl_dataset;

	for (int t = 0; t < TXG_SIZE; t++)
		ASSERT(!dmu_objset_is_dirty(os, t));

	if (ds)
		dsl_prop_unregister_all(ds, os);

	if (os->os_sa)
		sa_tear_down(os);

	dmu_objset_evict_dbufs(os);

	mutex_enter(&os->os_lock);
	spa_evicting_os_register(os->os_spa, os);
	if (list_is_empty(&os->os_dnodes)) {
		mutex_exit(&os->os_lock);
		dmu_objset_evict_done(os);
	} else {
		mutex_exit(&os->os_lock);
	}


}