#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  spa_checkpoint_discard_zthr; scalar_t__ spa_checkpoint_txg; } ;
typedef  TYPE_1__ spa_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_6__ {TYPE_1__* dp_spa; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMU_POOL_DIRECTORY_OBJECT ; 
 int /*<<< orphan*/  DMU_POOL_ZPOOL_CHECKPOINT ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 TYPE_4__* dmu_tx_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_history_log_internal (TYPE_1__*,char*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  spa_meta_objset (TYPE_1__*) ; 
 int /*<<< orphan*/  zap_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zthr_wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
spa_checkpoint_discard_sync(void *arg, dmu_tx_t *tx)
{
	spa_t *spa = dmu_tx_pool(tx)->dp_spa;

	VERIFY0(zap_remove(spa_meta_objset(spa), DMU_POOL_DIRECTORY_OBJECT,
	    DMU_POOL_ZPOOL_CHECKPOINT, tx));

	spa->spa_checkpoint_txg = 0;

	zthr_wakeup(spa->spa_checkpoint_discard_zthr);

	spa_history_log_internal(spa, "spa discard checkpoint", tx,
	    "started discarding checkpointed state from the pool");
}