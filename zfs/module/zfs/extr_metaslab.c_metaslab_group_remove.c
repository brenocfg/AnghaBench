#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  multilist_sublist_t ;
struct TYPE_11__ {TYPE_2__* ms_group; int /*<<< orphan*/  ms_class_txg_node; int /*<<< orphan*/  ms_lock; } ;
typedef  TYPE_1__ metaslab_t ;
struct TYPE_12__ {int /*<<< orphan*/  mg_lock; TYPE_3__* mg_class; int /*<<< orphan*/  mg_metaslab_tree; } ;
typedef  TYPE_2__ metaslab_group_t ;
struct TYPE_13__ {int /*<<< orphan*/  mc_metaslab_txg_list; } ;
typedef  TYPE_3__ metaslab_class_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  avl_remove (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  metaslab_group_histogram_remove (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ multilist_link_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * multilist_sublist_lock_obj (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  multilist_sublist_remove (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  multilist_sublist_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
metaslab_group_remove(metaslab_group_t *mg, metaslab_t *msp)
{
	mutex_enter(&msp->ms_lock);
	metaslab_group_histogram_remove(mg, msp);
	mutex_exit(&msp->ms_lock);

	mutex_enter(&mg->mg_lock);
	ASSERT(msp->ms_group == mg);
	avl_remove(&mg->mg_metaslab_tree, msp);

	metaslab_class_t *mc = msp->ms_group->mg_class;
	multilist_sublist_t *mls =
	    multilist_sublist_lock_obj(mc->mc_metaslab_txg_list, msp);
	if (multilist_link_active(&msp->ms_class_txg_node))
		multilist_sublist_remove(mls, msp);
	multilist_sublist_unlock(mls);

	msp->ms_group = NULL;
	mutex_exit(&mg->mg_lock);
}