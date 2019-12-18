#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_7__ {int /*<<< orphan*/  dl_lock; int /*<<< orphan*/  dl_object; int /*<<< orphan*/  dl_os; int /*<<< orphan*/  dl_tree; scalar_t__ dl_oldfmt; } ;
typedef  TYPE_1__ dsl_deadlist_t ;
struct TYPE_8__ {int /*<<< orphan*/  dle_bpobj; int /*<<< orphan*/  dle_mintxg; } ;
typedef  TYPE_2__ dsl_deadlist_entry_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  SPA_OLD_MAXBLOCKSIZE ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avl_add (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  bpobj_alloc_empty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpobj_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_deadlist_load_tree (TYPE_1__*) ; 
 TYPE_2__* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_add_int_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
dsl_deadlist_add_key(dsl_deadlist_t *dl, uint64_t mintxg, dmu_tx_t *tx)
{
	uint64_t obj;
	dsl_deadlist_entry_t *dle;

	if (dl->dl_oldfmt)
		return;

	dle = kmem_alloc(sizeof (*dle), KM_SLEEP);
	dle->dle_mintxg = mintxg;

	mutex_enter(&dl->dl_lock);
	dsl_deadlist_load_tree(dl);

	obj = bpobj_alloc_empty(dl->dl_os, SPA_OLD_MAXBLOCKSIZE, tx);
	VERIFY0(bpobj_open(&dle->dle_bpobj, dl->dl_os, obj));
	avl_add(&dl->dl_tree, dle);

	VERIFY0(zap_add_int_key(dl->dl_os, dl->dl_object,
	    mintxg, obj, tx));
	mutex_exit(&dl->dl_lock);
}