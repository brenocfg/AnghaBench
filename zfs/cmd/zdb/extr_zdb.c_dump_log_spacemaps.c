#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_longlong_t ;
typedef  int /*<<< orphan*/  space_map_t ;
struct TYPE_9__ {int /*<<< orphan*/  spa_meta_objset; int /*<<< orphan*/  spa_sm_logs_by_txg; } ;
typedef  TYPE_1__ spa_t ;
struct TYPE_10__ {scalar_t__ sls_txg; scalar_t__ sls_sm_obj; } ;
typedef  TYPE_2__ spa_log_sm_t ;

/* Variables and functions */
 TYPE_2__* AVL_NEXT (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  SPA_FEATURE_LOG_SPACEMAP ; 
 int /*<<< orphan*/  SPA_MINBLOCKSHIFT ; 
 int /*<<< orphan*/  UINT64_MAX ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 TYPE_2__* avl_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_spacemap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  spa_feature_is_active (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_meta_objset (TYPE_1__*) ; 
 int /*<<< orphan*/  space_map_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  space_map_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_log_spacemaps(spa_t *spa)
{
	if (!spa_feature_is_active(spa, SPA_FEATURE_LOG_SPACEMAP))
		return;

	(void) printf("\nLog Space Maps in Pool:\n");
	for (spa_log_sm_t *sls = avl_first(&spa->spa_sm_logs_by_txg);
	    sls; sls = AVL_NEXT(&spa->spa_sm_logs_by_txg, sls)) {
		space_map_t *sm = NULL;
		VERIFY0(space_map_open(&sm, spa_meta_objset(spa),
		    sls->sls_sm_obj, 0, UINT64_MAX, SPA_MINBLOCKSHIFT));

		(void) printf("Log Spacemap object %llu txg %llu\n",
		    (u_longlong_t)sls->sls_sm_obj, (u_longlong_t)sls->sls_txg);
		dump_spacemap(spa->spa_meta_objset, sm);
		space_map_close(sm);
	}
	(void) printf("\n");
}