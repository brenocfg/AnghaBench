#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;

/* Type definitions */
struct TYPE_16__ {int zlp_rewind; scalar_t__ zlp_maxmeta; scalar_t__ zlp_maxdata; } ;
typedef  TYPE_2__ zpool_load_policy_t ;
typedef  int /*<<< orphan*/  zio_t ;
typedef  scalar_t__ u_longlong_t ;
struct TYPE_15__ {scalar_t__ ub_timestamp; int /*<<< orphan*/  ub_txg; } ;
struct TYPE_17__ {scalar_t__ spa_load_meta_errors; scalar_t__ spa_load_data_errors; scalar_t__ spa_load_txg_ts; scalar_t__ spa_last_ubsync_txg_ts; TYPE_1__ spa_uberblock; int /*<<< orphan*/  spa_load_max_txg; int /*<<< orphan*/  spa_load_info; int /*<<< orphan*/  spa_load_txg; int /*<<< orphan*/  spa_load_verify_bytes; int /*<<< orphan*/  spa_verify_min_txg; scalar_t__ spa_extreme_rewind; TYPE_11__* spa_dsl_pool; int /*<<< orphan*/  spa_config; } ;
typedef  TYPE_3__ spa_t ;
struct TYPE_18__ {scalar_t__ sle_meta_count; scalar_t__ sle_data_count; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ spa_load_error_t ;
typedef  scalar_t__ int64_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_14__ {int /*<<< orphan*/  dp_root_dir_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT0 (int /*<<< orphan*/ ) ; 
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  DS_FIND_CHILDREN ; 
 int EIO ; 
 int ENXIO ; 
 int /*<<< orphan*/  FTAG ; 
 int SET_ERROR (int) ; 
 int TRAVERSE_NO_DECRYPT ; 
 int TRAVERSE_PRE ; 
 int TRAVERSE_PREFETCH_METADATA ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int ZIO_FLAG_CANFAIL ; 
 int ZIO_FLAG_SPECULATIVE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_LOAD_DATA_ERRORS ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_LOAD_TIME ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_REWIND_TIME ; 
 int ZPOOL_NEVER_REWIND ; 
 int dmu_objset_find_dp (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_pool_config_enter (TYPE_11__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_pool_config_exit (TYPE_11__*,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_add_int64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nvlist_add_uint64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spa_load_note (TYPE_3__*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  spa_load_verify_cb ; 
 scalar_t__ spa_load_verify_data ; 
 scalar_t__ spa_load_verify_dryrun ; 
 scalar_t__ spa_load_verify_metadata ; 
 int traverse_pool (TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify_dataset_name_len ; 
 int /*<<< orphan*/ * zio_root (TYPE_3__*,int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int /*<<< orphan*/  zio_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpool_get_load_policy (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int
spa_load_verify(spa_t *spa)
{
	zio_t *rio;
	spa_load_error_t sle = { 0 };
	zpool_load_policy_t policy;
	boolean_t verify_ok = B_FALSE;
	int error = 0;

	zpool_get_load_policy(spa->spa_config, &policy);

	if (policy.zlp_rewind & ZPOOL_NEVER_REWIND)
		return (0);

	dsl_pool_config_enter(spa->spa_dsl_pool, FTAG);
	error = dmu_objset_find_dp(spa->spa_dsl_pool,
	    spa->spa_dsl_pool->dp_root_dir_obj, verify_dataset_name_len, NULL,
	    DS_FIND_CHILDREN);
	dsl_pool_config_exit(spa->spa_dsl_pool, FTAG);
	if (error != 0)
		return (error);

	rio = zio_root(spa, NULL, &sle,
	    ZIO_FLAG_CANFAIL | ZIO_FLAG_SPECULATIVE);

	if (spa_load_verify_metadata) {
		if (spa->spa_extreme_rewind) {
			spa_load_note(spa, "performing a complete scan of the "
			    "pool since extreme rewind is on. This may take "
			    "a very long time.\n  (spa_load_verify_data=%u, "
			    "spa_load_verify_metadata=%u)",
			    spa_load_verify_data, spa_load_verify_metadata);
		}

		error = traverse_pool(spa, spa->spa_verify_min_txg,
		    TRAVERSE_PRE | TRAVERSE_PREFETCH_METADATA |
		    TRAVERSE_NO_DECRYPT, spa_load_verify_cb, rio);
	}

	(void) zio_wait(rio);
	ASSERT0(spa->spa_load_verify_bytes);

	spa->spa_load_meta_errors = sle.sle_meta_count;
	spa->spa_load_data_errors = sle.sle_data_count;

	if (sle.sle_meta_count != 0 || sle.sle_data_count != 0) {
		spa_load_note(spa, "spa_load_verify found %llu metadata errors "
		    "and %llu data errors", (u_longlong_t)sle.sle_meta_count,
		    (u_longlong_t)sle.sle_data_count);
	}

	if (spa_load_verify_dryrun ||
	    (!error && sle.sle_meta_count <= policy.zlp_maxmeta &&
	    sle.sle_data_count <= policy.zlp_maxdata)) {
		int64_t loss = 0;

		verify_ok = B_TRUE;
		spa->spa_load_txg = spa->spa_uberblock.ub_txg;
		spa->spa_load_txg_ts = spa->spa_uberblock.ub_timestamp;

		loss = spa->spa_last_ubsync_txg_ts - spa->spa_load_txg_ts;
		VERIFY(nvlist_add_uint64(spa->spa_load_info,
		    ZPOOL_CONFIG_LOAD_TIME, spa->spa_load_txg_ts) == 0);
		VERIFY(nvlist_add_int64(spa->spa_load_info,
		    ZPOOL_CONFIG_REWIND_TIME, loss) == 0);
		VERIFY(nvlist_add_uint64(spa->spa_load_info,
		    ZPOOL_CONFIG_LOAD_DATA_ERRORS, sle.sle_data_count) == 0);
	} else {
		spa->spa_load_max_txg = spa->spa_uberblock.ub_txg;
	}

	if (spa_load_verify_dryrun)
		return (0);

	if (error) {
		if (error != ENXIO && error != EIO)
			error = SET_ERROR(EIO);
		return (error);
	}

	return (verify_ok ? 0 : EIO);
}