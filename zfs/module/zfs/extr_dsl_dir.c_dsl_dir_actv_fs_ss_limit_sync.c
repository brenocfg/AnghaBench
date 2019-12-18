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
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
struct TYPE_5__ {int /*<<< orphan*/  ds_dir; } ;
typedef  TYPE_1__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  SPA_FEATURE_FS_SS_LIMIT ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dmu_tx_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dsl_dataset_get_spa (TYPE_1__*) ; 
 int /*<<< orphan*/  dsl_dataset_hold (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  dsl_dataset_rele (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dir_init_fs_ss_count (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_feature_incr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_feature_is_active (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dsl_dir_actv_fs_ss_limit_sync(void *arg, dmu_tx_t *tx)
{
	char *ddname = (char *)arg;
	dsl_pool_t *dp = dmu_tx_pool(tx);
	dsl_dataset_t *ds;
	spa_t *spa;

	VERIFY0(dsl_dataset_hold(dp, ddname, FTAG, &ds));

	spa = dsl_dataset_get_spa(ds);

	if (!spa_feature_is_active(spa, SPA_FEATURE_FS_SS_LIMIT)) {
		/*
		 * Since the feature was not active and we're now setting a
		 * limit, increment the feature-active counter so that the
		 * feature becomes active for the first time.
		 *
		 * We are already in a sync task so we can update the MOS.
		 */
		spa_feature_incr(spa, SPA_FEATURE_FS_SS_LIMIT, tx);
	}

	/*
	 * Since we are now setting a non-UINT64_MAX limit on the filesystem,
	 * we need to ensure the counts are correct. Descend down the tree from
	 * this point and update all of the counts to be accurate.
	 */
	dsl_dir_init_fs_ss_count(ds->ds_dir, tx);

	dsl_dataset_rele(ds, FTAG);
}