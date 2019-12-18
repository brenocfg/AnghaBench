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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_8__ {int /*<<< orphan*/  ms_unflushed_txg; TYPE_2__* ms_group; } ;
typedef  TYPE_3__ metaslab_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_7__ {TYPE_1__* mg_vd; } ;
struct TYPE_6__ {int /*<<< orphan*/ * vdev_spa; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPA_FEATURE_LOG_SPACEMAP ; 
 int /*<<< orphan*/  metaslab_update_ondisk_flush_data (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_feature_is_active (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
metaslab_set_unflushed_txg(metaslab_t *ms, uint64_t txg, dmu_tx_t *tx)
{
	spa_t *spa = ms->ms_group->mg_vd->vdev_spa;

	if (!spa_feature_is_active(spa, SPA_FEATURE_LOG_SPACEMAP))
		return;

	ms->ms_unflushed_txg = txg;
	metaslab_update_ondisk_flush_data(ms, tx);
}