#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_10__ {scalar_t__ ub_version; } ;
struct TYPE_11__ {int /*<<< orphan*/  spa_root_vdev; TYPE_1__ spa_uberblock; } ;
typedef  TYPE_2__ spa_t ;
typedef  int /*<<< orphan*/  longlong_t ;
struct TYPE_12__ {scalar_t__ tx_txg; } ;
typedef  TYPE_3__ dmu_tx_t ;
struct TYPE_13__ {TYPE_2__* dp_spa; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int SPA_VERSION_IS_SUPPORTED (scalar_t__) ; 
 scalar_t__ TXG_INITIAL ; 
 TYPE_8__* dmu_tx_pool (TYPE_3__*) ; 
 int /*<<< orphan*/  spa_history_log_internal (TYPE_2__*,char*,TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_version (TYPE_2__*) ; 
 int /*<<< orphan*/  vdev_config_dirty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
spa_sync_version(void *arg, dmu_tx_t *tx)
{
	uint64_t *versionp = arg;
	uint64_t version = *versionp;
	spa_t *spa = dmu_tx_pool(tx)->dp_spa;

	/*
	 * Setting the version is special cased when first creating the pool.
	 */
	ASSERT(tx->tx_txg != TXG_INITIAL);

	ASSERT(SPA_VERSION_IS_SUPPORTED(version));
	ASSERT(version >= spa_version(spa));

	spa->spa_uberblock.ub_version = version;
	vdev_config_dirty(spa->spa_root_vdev);
	spa_history_log_internal(spa, "set", tx, "version=%lld",
	    (longlong_t)version);
}