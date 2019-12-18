#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_10__ {int /*<<< orphan*/  ds_remap_deadlist; int /*<<< orphan*/  ds_deadlist; int /*<<< orphan*/  ds_remap_deadlist_lock; TYPE_2__* ds_dir; } ;
typedef  TYPE_3__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_11__ {int /*<<< orphan*/  ds_prev_snap_obj; } ;
struct TYPE_9__ {TYPE_1__* dd_pool; } ;
struct TYPE_8__ {int /*<<< orphan*/ * dp_spa; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPA_FEATURE_DEVICE_REMOVAL ; 
 int /*<<< orphan*/  SPA_FEATURE_OBSOLETE_COUNTS ; 
 int /*<<< orphan*/  UINT64_MAX ; 
 int /*<<< orphan*/  dmu_tx_is_syncing (int /*<<< orphan*/ *) ; 
 TYPE_5__* dsl_dataset_phys (TYPE_3__*) ; 
 int /*<<< orphan*/  dsl_dataset_set_remap_deadlist_object (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_deadlist_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_deadlist_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_feature_incr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_feature_is_active (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_meta_objset (int /*<<< orphan*/ *) ; 

void
dsl_dataset_create_remap_deadlist(dsl_dataset_t *ds, dmu_tx_t *tx)
{
	uint64_t remap_deadlist_obj;
	spa_t *spa = ds->ds_dir->dd_pool->dp_spa;

	ASSERT(dmu_tx_is_syncing(tx));
	ASSERT(MUTEX_HELD(&ds->ds_remap_deadlist_lock));
	/*
	 * Currently we only create remap deadlists when there are indirect
	 * vdevs with referenced mappings.
	 */
	ASSERT(spa_feature_is_active(spa, SPA_FEATURE_DEVICE_REMOVAL));

	remap_deadlist_obj = dsl_deadlist_clone(
	    &ds->ds_deadlist, UINT64_MAX,
	    dsl_dataset_phys(ds)->ds_prev_snap_obj, tx);
	dsl_dataset_set_remap_deadlist_object(ds,
	    remap_deadlist_obj, tx);
	dsl_deadlist_open(&ds->ds_remap_deadlist, spa_meta_objset(spa),
	    remap_deadlist_obj);
	spa_feature_incr(spa, SPA_FEATURE_OBSOLETE_COUNTS, tx);
}