#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdb_log_sm_cb_t ;
struct TYPE_13__ {void* uic_arg; int /*<<< orphan*/  uic_cb; int /*<<< orphan*/  uic_txg; TYPE_2__* uic_spa; } ;
typedef  TYPE_1__ unflushed_iter_cb_arg_t ;
typedef  int /*<<< orphan*/  space_map_t ;
struct TYPE_14__ {int /*<<< orphan*/  spa_sm_logs_by_txg; } ;
typedef  TYPE_2__ spa_t ;
struct TYPE_15__ {int /*<<< orphan*/  sls_txg; int /*<<< orphan*/  sls_sm_obj; } ;
typedef  TYPE_3__ spa_log_sm_t ;

/* Variables and functions */
 TYPE_3__* AVL_NEXT (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  SCL_CONFIG ; 
 int /*<<< orphan*/  SPA_FEATURE_LOG_SPACEMAP ; 
 int /*<<< orphan*/  SPA_MINBLOCKSHIFT ; 
 int /*<<< orphan*/  UINT64_MAX ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 TYPE_3__* avl_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iterate_through_spacemap_logs_cb ; 
 int /*<<< orphan*/  spa_config_enter (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_feature_is_active (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_meta_objset (TYPE_2__*) ; 
 int /*<<< orphan*/  space_map_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  space_map_iterate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  space_map_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  space_map_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iterate_through_spacemap_logs(spa_t *spa, zdb_log_sm_cb_t cb, void *arg)
{
	if (!spa_feature_is_active(spa, SPA_FEATURE_LOG_SPACEMAP))
		return;

	spa_config_enter(spa, SCL_CONFIG, FTAG, RW_READER);
	for (spa_log_sm_t *sls = avl_first(&spa->spa_sm_logs_by_txg);
	    sls; sls = AVL_NEXT(&spa->spa_sm_logs_by_txg, sls)) {
		space_map_t *sm = NULL;
		VERIFY0(space_map_open(&sm, spa_meta_objset(spa),
		    sls->sls_sm_obj, 0, UINT64_MAX, SPA_MINBLOCKSHIFT));

		unflushed_iter_cb_arg_t uic = {
			.uic_spa = spa,
			.uic_txg = sls->sls_txg,
			.uic_arg = arg,
			.uic_cb = cb
		};

		VERIFY0(space_map_iterate(sm, space_map_length(sm),
		    iterate_through_spacemap_logs_cb, &uic));
		space_map_close(sm);
	}
	spa_config_exit(spa, SCL_CONFIG, FTAG);
}