#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  spacemap_zap ;
struct TYPE_8__ {int /*<<< orphan*/  sus_nblocks; } ;
struct TYPE_9__ {TYPE_1__ spa_unflushed_stats; int /*<<< orphan*/  spa_sm_logs_by_txg; int /*<<< orphan*/  spa_metaslabs_by_flushed; } ;
typedef  TYPE_2__ spa_t ;
struct TYPE_10__ {scalar_t__ sls_txg; scalar_t__ sls_nblocks; int /*<<< orphan*/  sls_sm_obj; int /*<<< orphan*/  sls_mscount; } ;
typedef  TYPE_3__ spa_log_sm_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  metaslab_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMU_POOL_DIRECTORY_OBJECT ; 
 int /*<<< orphan*/  DMU_POOL_LOG_SPACEMAP_ZAP ; 
 int ENOENT ; 
 int /*<<< orphan*/  VERIFY0 (int) ; 
 void* avl_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avl_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avl_remove (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  kmem_free (TYPE_3__*,int) ; 
 scalar_t__ metaslab_unflushed_txg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * spa_meta_objset (TYPE_2__*) ; 
 int /*<<< orphan*/  space_map_free_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int zap_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,scalar_t__*) ; 
 int zap_remove_int (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 

void
spa_cleanup_old_sm_logs(spa_t *spa, dmu_tx_t *tx)
{
	objset_t *mos = spa_meta_objset(spa);

	uint64_t spacemap_zap;
	int error = zap_lookup(mos, DMU_POOL_DIRECTORY_OBJECT,
	    DMU_POOL_LOG_SPACEMAP_ZAP, sizeof (spacemap_zap), 1, &spacemap_zap);
	if (error == ENOENT) {
		ASSERT(avl_is_empty(&spa->spa_sm_logs_by_txg));
		return;
	}
	VERIFY0(error);

	metaslab_t *oldest = avl_first(&spa->spa_metaslabs_by_flushed);
	uint64_t oldest_flushed_txg = metaslab_unflushed_txg(oldest);

	/* Free all log space maps older than the oldest_flushed_txg. */
	for (spa_log_sm_t *sls = avl_first(&spa->spa_sm_logs_by_txg);
	    sls && sls->sls_txg < oldest_flushed_txg;
	    sls = avl_first(&spa->spa_sm_logs_by_txg)) {
		ASSERT0(sls->sls_mscount);
		avl_remove(&spa->spa_sm_logs_by_txg, sls);
		space_map_free_obj(mos, sls->sls_sm_obj, tx);
		VERIFY0(zap_remove_int(mos, spacemap_zap, sls->sls_txg, tx));
		spa->spa_unflushed_stats.sus_nblocks -= sls->sls_nblocks;
		kmem_free(sls, sizeof (spa_log_sm_t));
	}
}