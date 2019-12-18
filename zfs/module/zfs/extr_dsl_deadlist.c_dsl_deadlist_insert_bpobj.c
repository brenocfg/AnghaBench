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
typedef  scalar_t__ uint64_t ;
struct TYPE_12__ {int /*<<< orphan*/  dl_tree; TYPE_1__* dl_phys; int /*<<< orphan*/  dl_dbuf; int /*<<< orphan*/  dl_os; int /*<<< orphan*/  dl_lock; } ;
typedef  TYPE_2__ dsl_deadlist_t ;
struct TYPE_13__ {scalar_t__ dle_mintxg; } ;
typedef  TYPE_3__ dsl_deadlist_entry_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  bpobj_t ;
typedef  int /*<<< orphan*/  avl_index_t ;
struct TYPE_11__ {int /*<<< orphan*/  dl_uncomp; int /*<<< orphan*/  dl_comp; int /*<<< orphan*/  dl_used; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVL_BEFORE ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 TYPE_3__* avl_find (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* avl_nearest (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpobj_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpobj_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bpobj_space (int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  dle_enqueue_subobj (TYPE_2__*,TYPE_3__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_buf_will_dirty (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_deadlist_load_tree (TYPE_2__*) ; 

__attribute__((used)) static void
dsl_deadlist_insert_bpobj(dsl_deadlist_t *dl, uint64_t obj, uint64_t birth,
    dmu_tx_t *tx)
{
	dsl_deadlist_entry_t dle_tofind;
	dsl_deadlist_entry_t *dle;
	avl_index_t where;
	uint64_t used, comp, uncomp;
	bpobj_t bpo;

	ASSERT(MUTEX_HELD(&dl->dl_lock));

	VERIFY0(bpobj_open(&bpo, dl->dl_os, obj));
	VERIFY0(bpobj_space(&bpo, &used, &comp, &uncomp));
	bpobj_close(&bpo);

	dsl_deadlist_load_tree(dl);

	dmu_buf_will_dirty(dl->dl_dbuf, tx);
	dl->dl_phys->dl_used += used;
	dl->dl_phys->dl_comp += comp;
	dl->dl_phys->dl_uncomp += uncomp;

	dle_tofind.dle_mintxg = birth;
	dle = avl_find(&dl->dl_tree, &dle_tofind, &where);
	if (dle == NULL)
		dle = avl_nearest(&dl->dl_tree, where, AVL_BEFORE);
	dle_enqueue_subobj(dl, dle, obj, tx);
}