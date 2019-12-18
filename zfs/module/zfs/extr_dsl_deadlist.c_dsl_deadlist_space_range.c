#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_10__ {int /*<<< orphan*/  dl_lock; int /*<<< orphan*/  dl_tree; int /*<<< orphan*/  dl_cache; int /*<<< orphan*/  dl_bpobj; scalar_t__ dl_oldfmt; } ;
typedef  TYPE_1__ dsl_deadlist_t ;
struct TYPE_11__ {scalar_t__ dlce_mintxg; scalar_t__ dlce_bytes; scalar_t__ dlce_comp; scalar_t__ dlce_uncomp; } ;
typedef  TYPE_2__ dsl_deadlist_cache_entry_t ;
typedef  int /*<<< orphan*/  avl_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  AVL_AFTER ; 
 TYPE_2__* AVL_NEXT (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 TYPE_2__* avl_find (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* avl_nearest (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpobj_space_range (int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  dsl_deadlist_load_cache (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void
dsl_deadlist_space_range(dsl_deadlist_t *dl, uint64_t mintxg, uint64_t maxtxg,
    uint64_t *usedp, uint64_t *compp, uint64_t *uncompp)
{
	dsl_deadlist_cache_entry_t *dlce;
	dsl_deadlist_cache_entry_t dlce_tofind;
	avl_index_t where;

	if (dl->dl_oldfmt) {
		VERIFY0(bpobj_space_range(&dl->dl_bpobj,
		    mintxg, maxtxg, usedp, compp, uncompp));
		return;
	}

	*usedp = *compp = *uncompp = 0;

	mutex_enter(&dl->dl_lock);
	dsl_deadlist_load_cache(dl);
	dlce_tofind.dlce_mintxg = mintxg;
	dlce = avl_find(&dl->dl_cache, &dlce_tofind, &where);

	/*
	 * If this mintxg doesn't exist, it may be an empty_bpobj which
	 * is omitted from the sparse tree.  Start at the next non-empty
	 * entry.
	 */
	if (dlce == NULL)
		dlce = avl_nearest(&dl->dl_cache, where, AVL_AFTER);

	for (; dlce && dlce->dlce_mintxg < maxtxg;
	    dlce = AVL_NEXT(&dl->dl_tree, dlce)) {
		*usedp += dlce->dlce_bytes;
		*compp += dlce->dlce_comp;
		*uncompp += dlce->dlce_uncomp;
	}

	mutex_exit(&dl->dl_lock);
}