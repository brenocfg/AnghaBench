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
struct TYPE_8__ {int /*<<< orphan*/  dl_lock; int /*<<< orphan*/  dl_os; int /*<<< orphan*/  dl_tree; scalar_t__ dl_oldfmt; } ;
typedef  TYPE_1__ dsl_deadlist_t ;
struct TYPE_9__ {scalar_t__ dle_mintxg; } ;
typedef  TYPE_2__ dsl_deadlist_entry_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 TYPE_2__* AVL_NEXT (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  SPA_OLD_MAXBLOCKSIZE ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 TYPE_2__* avl_first (int /*<<< orphan*/ *) ; 
 scalar_t__ bpobj_alloc_empty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ dsl_deadlist_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_deadlist_load_tree (TYPE_1__*) ; 
 int /*<<< orphan*/  dsl_deadlist_regenerate (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_add_int_key (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 

uint64_t
dsl_deadlist_clone(dsl_deadlist_t *dl, uint64_t maxtxg,
    uint64_t mrs_obj, dmu_tx_t *tx)
{
	dsl_deadlist_entry_t *dle;
	uint64_t newobj;

	newobj = dsl_deadlist_alloc(dl->dl_os, tx);

	if (dl->dl_oldfmt) {
		dsl_deadlist_regenerate(dl->dl_os, newobj, mrs_obj, tx);
		return (newobj);
	}

	mutex_enter(&dl->dl_lock);
	dsl_deadlist_load_tree(dl);

	for (dle = avl_first(&dl->dl_tree); dle;
	    dle = AVL_NEXT(&dl->dl_tree, dle)) {
		uint64_t obj;

		if (dle->dle_mintxg >= maxtxg)
			break;

		obj = bpobj_alloc_empty(dl->dl_os, SPA_OLD_MAXBLOCKSIZE, tx);
		VERIFY0(zap_add_int_key(dl->dl_os, newobj,
		    dle->dle_mintxg, obj, tx));
	}
	mutex_exit(&dl->dl_lock);
	return (newobj);
}