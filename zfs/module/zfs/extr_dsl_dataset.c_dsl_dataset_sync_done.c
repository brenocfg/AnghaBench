#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/ * os_next_write_raw; scalar_t__ os_encrypted; int /*<<< orphan*/ * os_synced_dnodes; } ;
typedef  TYPE_1__ objset_t ;
struct TYPE_18__ {int /*<<< orphan*/  ds_dbuf; TYPE_7__* ds_dir; int /*<<< orphan*/  ds_deadlist; int /*<<< orphan*/  ds_pending_deadlist; TYPE_1__* ds_objset; } ;
typedef  TYPE_2__ dsl_dataset_t ;
struct TYPE_19__ {size_t tx_txg; } ;
typedef  TYPE_3__ dmu_tx_t ;
struct TYPE_20__ {int /*<<< orphan*/  dd_livelist; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ASSERT0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 size_t TXG_MASK ; 
 int /*<<< orphan*/  bplist_iterate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  dmu_buf_rele (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  dmu_objset_is_dirty (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_get_txg (TYPE_3__*) ; 
 int /*<<< orphan*/  dsl_bookmark_sync_done (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  dsl_deadlist_insert_alloc_cb ; 
 scalar_t__ dsl_deadlist_is_open (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dir_remove_livelist (TYPE_7__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_flush_pending_livelist (TYPE_2__*,TYPE_3__*) ; 
 scalar_t__ dsl_livelist_should_disable (TYPE_2__*) ; 
 int /*<<< orphan*/  multilist_destroy (int /*<<< orphan*/ *) ; 

void
dsl_dataset_sync_done(dsl_dataset_t *ds, dmu_tx_t *tx)
{
	objset_t *os = ds->ds_objset;

	bplist_iterate(&ds->ds_pending_deadlist,
	    dsl_deadlist_insert_alloc_cb, &ds->ds_deadlist, tx);

	if (dsl_deadlist_is_open(&ds->ds_dir->dd_livelist)) {
		dsl_flush_pending_livelist(ds, tx);
		if (dsl_livelist_should_disable(ds)) {
			dsl_dir_remove_livelist(ds->ds_dir, tx, B_TRUE);
		}
	}

	dsl_bookmark_sync_done(ds, tx);

	if (os->os_synced_dnodes != NULL) {
		multilist_destroy(os->os_synced_dnodes);
		os->os_synced_dnodes = NULL;
	}

	if (os->os_encrypted)
		os->os_next_write_raw[tx->tx_txg & TXG_MASK] = B_FALSE;
	else
		ASSERT0(os->os_next_write_raw[tx->tx_txg & TXG_MASK]);

	ASSERT(!dmu_objset_is_dirty(os, dmu_tx_get_txg(tx)));

	dmu_buf_rele(ds->ds_dbuf, ds);
}