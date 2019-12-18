#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_11__ {int /*<<< orphan*/  dp_spa; int /*<<< orphan*/  dp_config_rwlock; int /*<<< orphan*/ * dp_meta_objset; } ;
typedef  TYPE_1__ dsl_pool_t ;
struct TYPE_12__ {scalar_t__ dd_crypto_obj; int /*<<< orphan*/  dd_myname; struct TYPE_12__* dd_parent; int /*<<< orphan*/  dd_object; } ;
typedef  TYPE_2__ dsl_dir_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  size_t dd_used_t ;
struct TYPE_13__ {scalar_t__ dd_child_dir_zapobj; scalar_t__ dd_props_zapobj; scalar_t__ dd_clones; int /*<<< orphan*/  dd_deleg_zapobj; int /*<<< orphan*/ * dd_used_breakdown; int /*<<< orphan*/  dd_reserved; int /*<<< orphan*/  dd_used_bytes; int /*<<< orphan*/  dd_head_dataset_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DD_FIELD_FILESYSTEM_COUNT ; 
 size_t DD_USED_NUM ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RRW_WRITE_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_object_free_zapified (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* dmu_tx_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_crypto_key_destroy_sync (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_deleg_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dir_hold_obj (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__**) ; 
 TYPE_6__* dsl_dir_phys (TYPE_2__*) ; 
 int /*<<< orphan*/  dsl_dir_rele (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dir_set_reservation_sync_impl (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_fs_ss_count_adjust (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_keystore_unload_wkey_impl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zap_destroy (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_remove (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dsl_dir_destroy_sync(uint64_t ddobj, dmu_tx_t *tx)
{
	dsl_dir_t *dd;
	dsl_pool_t *dp = dmu_tx_pool(tx);
	objset_t *mos = dp->dp_meta_objset;
	dd_used_t t;

	ASSERT(RRW_WRITE_HELD(&dmu_tx_pool(tx)->dp_config_rwlock));

	VERIFY0(dsl_dir_hold_obj(dp, ddobj, NULL, FTAG, &dd));

	ASSERT0(dsl_dir_phys(dd)->dd_head_dataset_obj);

	/* Decrement the filesystem count for all parent filesystems. */
	if (dd->dd_parent != NULL)
		dsl_fs_ss_count_adjust(dd->dd_parent, -1,
		    DD_FIELD_FILESYSTEM_COUNT, tx);

	/*
	 * Remove our reservation. The impl() routine avoids setting the
	 * actual property, which would require the (already destroyed) ds.
	 */
	dsl_dir_set_reservation_sync_impl(dd, 0, tx);

	ASSERT0(dsl_dir_phys(dd)->dd_used_bytes);
	ASSERT0(dsl_dir_phys(dd)->dd_reserved);
	for (t = 0; t < DD_USED_NUM; t++)
		ASSERT0(dsl_dir_phys(dd)->dd_used_breakdown[t]);

	if (dd->dd_crypto_obj != 0) {
		dsl_crypto_key_destroy_sync(dd->dd_crypto_obj, tx);
		(void) spa_keystore_unload_wkey_impl(dp->dp_spa, dd->dd_object);
	}

	VERIFY0(zap_destroy(mos, dsl_dir_phys(dd)->dd_child_dir_zapobj, tx));
	VERIFY0(zap_destroy(mos, dsl_dir_phys(dd)->dd_props_zapobj, tx));
	if (dsl_dir_phys(dd)->dd_clones != 0)
		VERIFY0(zap_destroy(mos, dsl_dir_phys(dd)->dd_clones, tx));
	VERIFY0(dsl_deleg_destroy(mos, dsl_dir_phys(dd)->dd_deleg_zapobj, tx));
	VERIFY0(zap_remove(mos,
	    dsl_dir_phys(dd->dd_parent)->dd_child_dir_zapobj,
	    dd->dd_myname, tx));

	dsl_dir_rele(dd, FTAG);
	dmu_object_free_zapified(mos, ddobj, tx);
}