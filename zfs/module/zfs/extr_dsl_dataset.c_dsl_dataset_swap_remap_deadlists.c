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
struct TYPE_10__ {int /*<<< orphan*/  dp_meta_objset; } ;
typedef  TYPE_1__ dsl_pool_t ;
struct TYPE_11__ {int /*<<< orphan*/  ds_remap_deadlist; } ;
typedef  TYPE_2__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 TYPE_1__* dmu_tx_pool (int /*<<< orphan*/ *) ; 
 scalar_t__ dsl_dataset_get_remap_deadlist_object (TYPE_2__*) ; 
 int /*<<< orphan*/  dsl_dataset_set_remap_deadlist_object (TYPE_2__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_unset_remap_deadlist_object (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_deadlist_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_deadlist_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dsl_pool_sync_context (TYPE_1__*) ; 

__attribute__((used)) static void
dsl_dataset_swap_remap_deadlists(dsl_dataset_t *clone,
    dsl_dataset_t *origin, dmu_tx_t *tx)
{
	uint64_t clone_remap_dl_obj, origin_remap_dl_obj;
	dsl_pool_t *dp = dmu_tx_pool(tx);

	ASSERT(dsl_pool_sync_context(dp));

	clone_remap_dl_obj = dsl_dataset_get_remap_deadlist_object(clone);
	origin_remap_dl_obj = dsl_dataset_get_remap_deadlist_object(origin);

	if (clone_remap_dl_obj != 0) {
		dsl_deadlist_close(&clone->ds_remap_deadlist);
		dsl_dataset_unset_remap_deadlist_object(clone, tx);
	}
	if (origin_remap_dl_obj != 0) {
		dsl_deadlist_close(&origin->ds_remap_deadlist);
		dsl_dataset_unset_remap_deadlist_object(origin, tx);
	}

	if (clone_remap_dl_obj != 0) {
		dsl_dataset_set_remap_deadlist_object(origin,
		    clone_remap_dl_obj, tx);
		dsl_deadlist_open(&origin->ds_remap_deadlist,
		    dp->dp_meta_objset, clone_remap_dl_obj);
	}
	if (origin_remap_dl_obj != 0) {
		dsl_dataset_set_remap_deadlist_object(clone,
		    origin_remap_dl_obj, tx);
		dsl_deadlist_open(&clone->ds_remap_deadlist,
		    dp->dp_meta_objset, origin_remap_dl_obj);
	}
}