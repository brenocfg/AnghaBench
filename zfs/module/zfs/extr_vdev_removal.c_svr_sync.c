#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__* svr_bytes_done; } ;
typedef  TYPE_2__ spa_vdev_removal_t ;
struct TYPE_6__ {int /*<<< orphan*/  sr_copied; } ;
struct TYPE_8__ {TYPE_1__ spa_removing_phys; TYPE_2__* spa_vdev_removal; } ;
typedef  TYPE_3__ spa_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int TXG_MASK ; 
 int dmu_tx_get_txg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_sync_removing_state (TYPE_3__*,int /*<<< orphan*/ *) ; 

void
svr_sync(spa_t *spa, dmu_tx_t *tx)
{
	spa_vdev_removal_t *svr = spa->spa_vdev_removal;
	int txgoff = dmu_tx_get_txg(tx) & TXG_MASK;

	if (svr == NULL)
		return;

	/*
	 * This check is necessary so that we do not dirty the
	 * DIRECTORY_OBJECT via spa_sync_removing_state() when there
	 * is nothing to do.  Dirtying it every time would prevent us
	 * from syncing-to-convergence.
	 */
	if (svr->svr_bytes_done[txgoff] == 0)
		return;

	/*
	 * Update progress accounting.
	 */
	spa->spa_removing_phys.sr_copied += svr->svr_bytes_done[txgoff];
	svr->svr_bytes_done[txgoff] = 0;

	spa_sync_removing_state(spa, tx);
}