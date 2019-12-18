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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  multilist_t ;
typedef  int /*<<< orphan*/  multilist_sublist_t ;
struct TYPE_8__ {scalar_t__ ms_selected_txg; scalar_t__ ms_selected_time; int /*<<< orphan*/  ms_lock; int /*<<< orphan*/  ms_class_txg_node; } ;
typedef  TYPE_1__ metaslab_t ;
struct TYPE_9__ {int /*<<< orphan*/ * mc_metaslab_txg_list; } ;
typedef  TYPE_2__ metaslab_class_t ;

/* Variables and functions */
 scalar_t__ MSEC2NSEC (int /*<<< orphan*/ ) ; 
 scalar_t__ gethrtime () ; 
 int /*<<< orphan*/  metaslab_evict (TYPE_1__*,scalar_t__) ; 
 scalar_t__ metaslab_unload_delay ; 
 int /*<<< orphan*/  metaslab_unload_delay_ms ; 
 int multilist_get_num_sublists (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  multilist_link_active (int /*<<< orphan*/ *) ; 
 TYPE_1__* multilist_sublist_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * multilist_sublist_lock (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* multilist_sublist_next (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  multilist_sublist_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void
metaslab_class_evict_old(metaslab_class_t *mc, uint64_t txg)
{
	multilist_t *ml = mc->mc_metaslab_txg_list;
	for (int i = 0; i < multilist_get_num_sublists(ml); i++) {
		multilist_sublist_t *mls = multilist_sublist_lock(ml, i);
		metaslab_t *msp = multilist_sublist_head(mls);
		multilist_sublist_unlock(mls);
		while (msp != NULL) {
			mutex_enter(&msp->ms_lock);

			/*
			 * If the metaslab has been removed from the list
			 * (which could happen if we were at the memory limit
			 * and it was evicted during this loop), then we can't
			 * proceed and we should restart the sublist.
			 */
			if (!multilist_link_active(&msp->ms_class_txg_node)) {
				mutex_exit(&msp->ms_lock);
				i--;
				break;
			}
			mls = multilist_sublist_lock(ml, i);
			metaslab_t *next_msp = multilist_sublist_next(mls, msp);
			multilist_sublist_unlock(mls);
			if (txg >
			    msp->ms_selected_txg + metaslab_unload_delay &&
			    gethrtime() > msp->ms_selected_time +
			    (uint64_t)MSEC2NSEC(metaslab_unload_delay_ms)) {
				metaslab_evict(msp, txg);
			} else {
				/*
				 * Once we've hit a metaslab selected too
				 * recently to evict, we're done evicting for
				 * now.
				 */
				mutex_exit(&msp->ms_lock);
				break;
			}
			mutex_exit(&msp->ms_lock);
			msp = next_msp;
		}
	}
}