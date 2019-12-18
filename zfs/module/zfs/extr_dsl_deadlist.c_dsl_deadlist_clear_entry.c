#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_12__ {int /*<<< orphan*/  dl_lock; int /*<<< orphan*/  dl_object; TYPE_1__* dl_phys; int /*<<< orphan*/  dl_dbuf; int /*<<< orphan*/ * dl_os; } ;
typedef  TYPE_2__ dsl_deadlist_t ;
struct TYPE_15__ {scalar_t__ bpo_object; } ;
struct TYPE_13__ {TYPE_7__ dle_bpobj; int /*<<< orphan*/  dle_mintxg; } ;
typedef  TYPE_3__ dsl_deadlist_entry_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_14__ {scalar_t__ dp_empty_bpobj; } ;
struct TYPE_11__ {int /*<<< orphan*/  dl_uncomp; int /*<<< orphan*/  dl_comp; int /*<<< orphan*/  dl_used; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPA_OLD_MAXBLOCKSIZE ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 scalar_t__ bpobj_alloc_empty (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpobj_close (TYPE_7__*) ; 
 int /*<<< orphan*/  bpobj_decr_empty (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpobj_free (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpobj_is_empty (TYPE_7__*) ; 
 int /*<<< orphan*/  bpobj_open (TYPE_7__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  bpobj_space (TYPE_7__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  dmu_buf_will_dirty (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_6__* dmu_objset_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_add_int_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_remove_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
dsl_deadlist_clear_entry(dsl_deadlist_entry_t *dle, dsl_deadlist_t *dl,
    dmu_tx_t *tx)
{
	uint64_t new_obj, used, comp, uncomp;
	objset_t *os = dl->dl_os;

	mutex_enter(&dl->dl_lock);
	VERIFY0(zap_remove_int(os, dl->dl_object, dle->dle_mintxg, tx));
	VERIFY0(bpobj_space(&dle->dle_bpobj, &used, &comp, &uncomp));
	dmu_buf_will_dirty(dl->dl_dbuf, tx);
	dl->dl_phys->dl_used -= used;
	dl->dl_phys->dl_comp -= comp;
	dl->dl_phys->dl_uncomp -= uncomp;
	if (dle->dle_bpobj.bpo_object == dmu_objset_pool(os)->dp_empty_bpobj)
		bpobj_decr_empty(os, tx);
	else
		bpobj_free(os, dle->dle_bpobj.bpo_object, tx);
	bpobj_close(&dle->dle_bpobj);
	new_obj = bpobj_alloc_empty(os, SPA_OLD_MAXBLOCKSIZE, tx);
	VERIFY0(bpobj_open(&dle->dle_bpobj, os, new_obj));
	VERIFY0(zap_add_int_key(os, dl->dl_object, dle->dle_mintxg,
	    new_obj, tx));
	ASSERT(bpobj_is_empty(&dle->dle_bpobj));
	mutex_exit(&dl->dl_lock);
}