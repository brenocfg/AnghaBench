#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spacemap_zap ;
struct TYPE_8__ {int /*<<< orphan*/  spa_sm_logs_by_txg; } ;
typedef  TYPE_1__ spa_t ;
struct TYPE_9__ {int /*<<< orphan*/  sls_sm_obj; } ;
typedef  TYPE_2__ spa_log_sm_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT0 (int) ; 
 TYPE_2__* AVL_NEXT (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  DMU_POOL_DIRECTORY_OBJECT ; 
 int /*<<< orphan*/  DMU_POOL_LOG_SPACEMAP_ZAP ; 
 int ENOENT ; 
 TYPE_2__* avl_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mos_obj_refd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_meta_objset (TYPE_1__*) ; 
 int zap_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mos_leak_log_spacemaps(spa_t *spa)
{
	uint64_t spacemap_zap;
	int error = zap_lookup(spa_meta_objset(spa),
	    DMU_POOL_DIRECTORY_OBJECT, DMU_POOL_LOG_SPACEMAP_ZAP,
	    sizeof (spacemap_zap), 1, &spacemap_zap);
	if (error == ENOENT)
		return;
	ASSERT0(error);

	mos_obj_refd(spacemap_zap);
	for (spa_log_sm_t *sls = avl_first(&spa->spa_sm_logs_by_txg);
	    sls; sls = AVL_NEXT(&spa->spa_sm_logs_by_txg, sls))
		mos_obj_refd(sls->sls_sm_obj);
}