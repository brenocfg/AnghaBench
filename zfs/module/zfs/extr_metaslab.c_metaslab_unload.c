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
typedef  int /*<<< orphan*/  multilist_sublist_t ;
struct TYPE_9__ {TYPE_1__* ms_group; int /*<<< orphan*/  ms_class_txg_node; int /*<<< orphan*/  ms_weight; scalar_t__ ms_activation_weight; int /*<<< orphan*/  ms_unload_time; scalar_t__ ms_loaded; int /*<<< orphan*/  ms_allocatable; int /*<<< orphan*/  ms_lock; } ;
typedef  TYPE_2__ metaslab_t ;
struct TYPE_10__ {int /*<<< orphan*/  mc_metaslab_txg_list; } ;
typedef  TYPE_3__ metaslab_class_t ;
struct TYPE_8__ {TYPE_3__* mg_class; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ B_FALSE ; 
 int /*<<< orphan*/  METASLAB_ACTIVE_MASK ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gethrtime () ; 
 int /*<<< orphan*/  metaslab_recalculate_weight_and_sort (TYPE_2__*) ; 
 scalar_t__ multilist_link_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * multilist_sublist_lock_obj (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  multilist_sublist_remove (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  multilist_sublist_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  range_tree_vacate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
metaslab_unload(metaslab_t *msp)
{
	ASSERT(MUTEX_HELD(&msp->ms_lock));

	/*
	 * This can happen if a metaslab is selected for eviction (in
	 * metaslab_potentially_evict) and then unloaded during spa_sync (via
	 * metaslab_class_evict_old).
	 */
	if (!msp->ms_loaded)
		return;

	range_tree_vacate(msp->ms_allocatable, NULL, NULL);
	msp->ms_loaded = B_FALSE;
	msp->ms_unload_time = gethrtime();

	msp->ms_activation_weight = 0;
	msp->ms_weight &= ~METASLAB_ACTIVE_MASK;

	if (msp->ms_group != NULL) {
		metaslab_class_t *mc = msp->ms_group->mg_class;
		multilist_sublist_t *mls =
		    multilist_sublist_lock_obj(mc->mc_metaslab_txg_list, msp);
		if (multilist_link_active(&msp->ms_class_txg_node))
			multilist_sublist_remove(mls, msp);
		multilist_sublist_unlock(mls);
	}

	/*
	 * We explicitly recalculate the metaslab's weight based on its space
	 * map (as it is now not loaded). We want unload metaslabs to always
	 * have their weights calculated from the space map histograms, while
	 * loaded ones have it calculated from their in-core range tree
	 * [see metaslab_load()]. This way, the weight reflects the information
	 * available in-core, whether it is loaded or not.
	 *
	 * If ms_group == NULL means that we came here from metaslab_fini(),
	 * at which point it doesn't make sense for us to do the recalculation
	 * and the sorting.
	 */
	if (msp->ms_group != NULL)
		metaslab_recalculate_weight_and_sort(msp);
}