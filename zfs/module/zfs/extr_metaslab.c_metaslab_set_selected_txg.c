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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  multilist_sublist_t ;
struct TYPE_9__ {int /*<<< orphan*/  ms_selected_time; int /*<<< orphan*/  ms_selected_txg; int /*<<< orphan*/  ms_class_txg_node; TYPE_1__* ms_group; int /*<<< orphan*/  ms_lock; } ;
typedef  TYPE_2__ metaslab_t ;
struct TYPE_10__ {int /*<<< orphan*/  mc_metaslab_txg_list; } ;
typedef  TYPE_3__ metaslab_class_t ;
struct TYPE_8__ {TYPE_3__* mg_class; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gethrtime () ; 
 scalar_t__ multilist_link_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  multilist_sublist_insert_tail (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * multilist_sublist_lock_obj (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  multilist_sublist_remove (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  multilist_sublist_unlock (int /*<<< orphan*/ *) ; 

void
metaslab_set_selected_txg(metaslab_t *msp, uint64_t txg)
{
	ASSERT(MUTEX_HELD(&msp->ms_lock));
	metaslab_class_t *mc = msp->ms_group->mg_class;
	multilist_sublist_t *mls =
	    multilist_sublist_lock_obj(mc->mc_metaslab_txg_list, msp);
	if (multilist_link_active(&msp->ms_class_txg_node))
		multilist_sublist_remove(mls, msp);
	msp->ms_selected_txg = txg;
	msp->ms_selected_time = gethrtime();
	multilist_sublist_insert_tail(mls, msp);
	multilist_sublist_unlock(mls);
}