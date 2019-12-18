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
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_9__ {int /*<<< orphan*/ * dp_meta_objset; } ;
typedef  TYPE_1__ dsl_pool_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
struct TYPE_10__ {scalar_t__ doi_bonus_type; } ;
typedef  TYPE_2__ dmu_object_info_t ;
typedef  int boolean_t ;
typedef  int /*<<< orphan*/  blkptr_cb_t ;
struct TYPE_11__ {scalar_t__ ds_prev_snap_txg; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 scalar_t__ DMU_OT_DSL_DATASET ; 
 int ESRCH ; 
 int /*<<< orphan*/  FTAG ; 
 int TRAVERSE_HARD ; 
 int dmu_object_info (int /*<<< orphan*/ *,scalar_t__,TYPE_2__*) ; 
 int dmu_object_next (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int dsl_dataset_hold_obj (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 TYPE_6__* dsl_dataset_phys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_pool_config_enter (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_pool_config_exit (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* spa_get_dsl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_get_rootblkptr (int /*<<< orphan*/ *) ; 
 int traverse_dataset (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ ,void*) ; 
 int traverse_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,void*) ; 

int
traverse_pool(spa_t *spa, uint64_t txg_start, int flags,
    blkptr_cb_t func, void *arg)
{
	int err;
	dsl_pool_t *dp = spa_get_dsl(spa);
	objset_t *mos = dp->dp_meta_objset;
	boolean_t hard = (flags & TRAVERSE_HARD);

	/* visit the MOS */
	err = traverse_impl(spa, NULL, 0, spa_get_rootblkptr(spa),
	    txg_start, NULL, flags, func, arg);
	if (err != 0)
		return (err);

	/* visit each dataset */
	for (uint64_t obj = 1; err == 0;
	    err = dmu_object_next(mos, &obj, B_FALSE, txg_start)) {
		dmu_object_info_t doi;

		err = dmu_object_info(mos, obj, &doi);
		if (err != 0) {
			if (hard)
				continue;
			break;
		}

		if (doi.doi_bonus_type == DMU_OT_DSL_DATASET) {
			dsl_dataset_t *ds;
			uint64_t txg = txg_start;

			dsl_pool_config_enter(dp, FTAG);
			err = dsl_dataset_hold_obj(dp, obj, FTAG, &ds);
			dsl_pool_config_exit(dp, FTAG);
			if (err != 0) {
				if (hard)
					continue;
				break;
			}
			if (dsl_dataset_phys(ds)->ds_prev_snap_txg > txg)
				txg = dsl_dataset_phys(ds)->ds_prev_snap_txg;
			err = traverse_dataset(ds, txg, flags, func, arg);
			dsl_dataset_rele(ds, FTAG);
			if (err != 0)
				break;
		}
	}
	if (err == ESRCH)
		err = 0;
	return (err);
}