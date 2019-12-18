#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  krwlock_t ;
struct TYPE_13__ {TYPE_7__* ds_dir; } ;
typedef  TYPE_1__ dsl_dataset_t ;
struct TYPE_14__ {scalar_t__ dn_objset; } ;
typedef  TYPE_2__ dnode_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_15__ {scalar_t__ drica_os; scalar_t__ drica_blk_birth; int /*<<< orphan*/ * drica_tx; } ;
typedef  TYPE_3__ dbuf_remap_impl_callback_arg_t ;
struct TYPE_16__ {scalar_t__ blk_birth; } ;
typedef  TYPE_4__ blkptr_t ;
struct TYPE_17__ {scalar_t__ dd_origin_txg; int /*<<< orphan*/  dd_pending_allocs; int /*<<< orphan*/  dd_pending_frees; int /*<<< orphan*/  dd_livelist; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  BP_IS_EMBEDDED (TYPE_4__*) ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  SPA_FEATURE_LIVELIST ; 
 int /*<<< orphan*/  bplist_append (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  dbuf_remap_impl_callback ; 
 TYPE_1__* dmu_objset_ds (scalar_t__) ; 
 int /*<<< orphan*/ * dmu_objset_spa (scalar_t__) ; 
 scalar_t__ dsl_deadlist_is_open (int /*<<< orphan*/ *) ; 
 int dsl_dir_is_clone (TYPE_7__*) ; 
 int dsl_pool_sync_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 int spa_feature_is_enabled (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_get_dsl (int /*<<< orphan*/ *) ; 
 scalar_t__ spa_meta_objset (int /*<<< orphan*/ *) ; 
 scalar_t__ spa_remap_blkptr (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static void
dbuf_remap_impl(dnode_t *dn, blkptr_t *bp, krwlock_t *rw, dmu_tx_t *tx)
{
	blkptr_t bp_copy = *bp;
	spa_t *spa = dmu_objset_spa(dn->dn_objset);
	dbuf_remap_impl_callback_arg_t drica;

	ASSERT(dsl_pool_sync_context(spa_get_dsl(spa)));

	drica.drica_os = dn->dn_objset;
	drica.drica_blk_birth = bp->blk_birth;
	drica.drica_tx = tx;
	if (spa_remap_blkptr(spa, &bp_copy, dbuf_remap_impl_callback,
	    &drica)) {
		/*
		 * If the blkptr being remapped is tracked by a livelist,
		 * then we need to make sure the livelist reflects the update.
		 * First, cancel out the old blkptr by appending a 'FREE'
		 * entry. Next, add an 'ALLOC' to track the new version. This
		 * way we avoid trying to free an inaccurate blkptr at delete.
		 * Note that embedded blkptrs are not tracked in livelists.
		 */
		if (dn->dn_objset != spa_meta_objset(spa)) {
			dsl_dataset_t *ds = dmu_objset_ds(dn->dn_objset);
			if (dsl_deadlist_is_open(&ds->ds_dir->dd_livelist) &&
			    bp->blk_birth > ds->ds_dir->dd_origin_txg) {
				ASSERT(!BP_IS_EMBEDDED(bp));
				ASSERT(dsl_dir_is_clone(ds->ds_dir));
				ASSERT(spa_feature_is_enabled(spa,
				    SPA_FEATURE_LIVELIST));
				bplist_append(&ds->ds_dir->dd_pending_frees,
				    bp);
				bplist_append(&ds->ds_dir->dd_pending_allocs,
				    &bp_copy);
			}
		}

		/*
		 * The db_rwlock prevents dbuf_read_impl() from
		 * dereferencing the BP while we are changing it.  To
		 * avoid lock contention, only grab it when we are actually
		 * changing the BP.
		 */
		if (rw != NULL)
			rw_enter(rw, RW_WRITER);
		*bp = bp_copy;
		if (rw != NULL)
			rw_exit(rw);
	}
}