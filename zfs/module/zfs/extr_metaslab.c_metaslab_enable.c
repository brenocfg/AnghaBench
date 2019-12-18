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
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_7__ {scalar_t__ ms_disabled; int /*<<< orphan*/  ms_lock; TYPE_3__* ms_group; } ;
typedef  TYPE_2__ metaslab_t ;
struct TYPE_8__ {int /*<<< orphan*/  mg_ms_disabled_lock; int /*<<< orphan*/  mg_ms_disabled_cv; int /*<<< orphan*/  mg_ms_disabled; TYPE_1__* mg_vd; } ;
typedef  TYPE_3__ metaslab_group_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_6__ {int /*<<< orphan*/ * vdev_spa; } ;

/* Variables and functions */
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  metaslab_unload (TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_get_dsl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txg_wait_synced (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
metaslab_enable(metaslab_t *msp, boolean_t sync, boolean_t unload)
{
	metaslab_group_t *mg = msp->ms_group;
	spa_t *spa = mg->mg_vd->vdev_spa;

	/*
	 * Wait for the outstanding IO to be synced to prevent newly
	 * allocated blocks from being overwritten.  This used by
	 * initialize and TRIM which are modifying unallocated space.
	 */
	if (sync)
		txg_wait_synced(spa_get_dsl(spa), 0);

	mutex_enter(&mg->mg_ms_disabled_lock);
	mutex_enter(&msp->ms_lock);
	if (--msp->ms_disabled == 0) {
		mg->mg_ms_disabled--;
		cv_broadcast(&mg->mg_ms_disabled_cv);
		if (unload)
			metaslab_unload(msp);
	}
	mutex_exit(&msp->ms_lock);
	mutex_exit(&mg->mg_ms_disabled_lock);
}