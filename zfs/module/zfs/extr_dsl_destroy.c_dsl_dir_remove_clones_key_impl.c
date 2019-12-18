#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_19__ ;
typedef  struct TYPE_21__   TYPE_15__ ;

/* Type definitions */
struct TYPE_24__ {int /*<<< orphan*/  za_first_integer; } ;
typedef  TYPE_2__ zap_cursor_t ;
typedef  TYPE_2__ zap_attribute_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  list_t ;
struct TYPE_25__ {TYPE_19__* dd_pool; } ;
typedef  TYPE_4__ dsl_dir_t ;
struct TYPE_26__ {int /*<<< orphan*/  ds_remap_deadlist; int /*<<< orphan*/  ds_deadlist; TYPE_1__* ds_dir; } ;
typedef  TYPE_5__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_23__ {int /*<<< orphan*/  dd_origin_txg; } ;
struct TYPE_22__ {int /*<<< orphan*/ * dp_meta_objset; } ;
struct TYPE_21__ {scalar_t__ dd_clones; } ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dataset_hold_obj (TYPE_19__*,int /*<<< orphan*/ ,void*,TYPE_5__**) ; 
 int /*<<< orphan*/  dsl_dataset_rele (TYPE_5__*,void*) ; 
 scalar_t__ dsl_dataset_remap_deadlist_exists (TYPE_5__*) ; 
 int /*<<< orphan*/  dsl_deadlist_remove_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_15__* dsl_dir_phys (TYPE_4__*) ; 
 TYPE_2__* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (TYPE_2__*,int) ; 
 int /*<<< orphan*/  list_insert_head (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rck_alloc (TYPE_5__*) ; 
 int /*<<< orphan*/  zap_cursor_advance (TYPE_2__*) ; 
 int /*<<< orphan*/  zap_cursor_fini (TYPE_2__*) ; 
 int /*<<< orphan*/  zap_cursor_init (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ zap_cursor_retrieve (TYPE_2__*,TYPE_2__*) ; 

__attribute__((used)) static void
dsl_dir_remove_clones_key_impl(dsl_dir_t *dd, uint64_t mintxg, dmu_tx_t *tx,
    list_t *stack, void *tag)
{
	objset_t *mos = dd->dd_pool->dp_meta_objset;

	/*
	 * If it is the old version, dd_clones doesn't exist so we can't
	 * find the clones, but dsl_deadlist_remove_key() is a no-op so it
	 * doesn't matter.
	 */
	if (dsl_dir_phys(dd)->dd_clones == 0)
		return;

	zap_cursor_t *zc = kmem_alloc(sizeof (zap_cursor_t), KM_SLEEP);
	zap_attribute_t *za = kmem_alloc(sizeof (zap_attribute_t), KM_SLEEP);

	for (zap_cursor_init(zc, mos, dsl_dir_phys(dd)->dd_clones);
	    zap_cursor_retrieve(zc, za) == 0;
	    zap_cursor_advance(zc)) {
		dsl_dataset_t *clone;

		VERIFY0(dsl_dataset_hold_obj(dd->dd_pool,
		    za->za_first_integer, tag, &clone));

		if (clone->ds_dir->dd_origin_txg > mintxg) {
			dsl_deadlist_remove_key(&clone->ds_deadlist,
			    mintxg, tx);

			if (dsl_dataset_remap_deadlist_exists(clone)) {
				dsl_deadlist_remove_key(
				    &clone->ds_remap_deadlist, mintxg, tx);
			}

			list_insert_head(stack, rck_alloc(clone));
		} else {
			dsl_dataset_rele(clone, tag);
		}
	}
	zap_cursor_fini(zc);

	kmem_free(za, sizeof (zap_attribute_t));
	kmem_free(zc, sizeof (zap_cursor_t));
}