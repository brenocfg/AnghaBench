#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint64_t ;
typedef  int /*<<< orphan*/  space_map_t ;
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_7__ {int /*<<< orphan*/  ms_synchist; int /*<<< orphan*/ * ms_deferhist; int /*<<< orphan*/ * ms_sm; TYPE_2__* ms_group; } ;
typedef  TYPE_3__ metaslab_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_6__ {TYPE_1__* mg_vd; } ;
struct TYPE_5__ {int /*<<< orphan*/ * vdev_spa; } ;

/* Variables and functions */
 size_t TXG_DEFER_SIZE ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 size_t spa_syncing_txg (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
metaslab_aux_histograms_update_done(metaslab_t *msp, boolean_t defer_allowed)
{
	spa_t *spa = msp->ms_group->mg_vd->vdev_spa;
	space_map_t *sm = msp->ms_sm;

	if (sm == NULL) {
		/*
		 * We came here from metaslab_init() when creating/opening a
		 * pool, looking at a metaslab that hasn't had any allocations
		 * yet.
		 */
		return;
	}

	/*
	 * This is similar to the actions that we take for the ms_freed
	 * and ms_defer trees in metaslab_sync_done().
	 */
	uint64_t hist_index = spa_syncing_txg(spa) % TXG_DEFER_SIZE;
	if (defer_allowed) {
		bcopy(msp->ms_synchist, msp->ms_deferhist[hist_index],
		    sizeof (msp->ms_synchist));
	} else {
		bzero(msp->ms_deferhist[hist_index],
		    sizeof (msp->ms_deferhist[hist_index]));
	}
	bzero(msp->ms_synchist, sizeof (msp->ms_synchist));
}