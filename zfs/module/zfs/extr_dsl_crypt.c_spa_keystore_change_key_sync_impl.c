#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_43__   TYPE_8__ ;
typedef  struct TYPE_42__   TYPE_7__ ;
typedef  struct TYPE_41__   TYPE_6__ ;
typedef  struct TYPE_40__   TYPE_5__ ;
typedef  struct TYPE_39__   TYPE_3__ ;
typedef  struct TYPE_38__   TYPE_2__ ;
typedef  struct TYPE_37__   TYPE_24__ ;
typedef  struct TYPE_36__   TYPE_1__ ;
typedef  struct TYPE_35__   TYPE_14__ ;

/* Type definitions */
struct TYPE_39__ {scalar_t__ za_first_integer; } ;
typedef  TYPE_3__ zap_cursor_t ;
typedef  TYPE_3__ zap_attribute_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  dsl_wrapping_key_t ;
struct TYPE_40__ {int /*<<< orphan*/  dp_meta_objset; TYPE_14__* dp_spa; } ;
typedef  TYPE_5__ dsl_pool_t ;
struct TYPE_41__ {char* dd_myname; int /*<<< orphan*/  dd_crypto_obj; } ;
typedef  TYPE_6__ dsl_dir_t ;
struct TYPE_42__ {TYPE_2__* ds_dir; } ;
typedef  TYPE_7__ dsl_dataset_t ;
struct TYPE_43__ {int /*<<< orphan*/ * dck_wkey; } ;
typedef  TYPE_8__ dsl_crypto_key_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_38__ {scalar_t__ dd_object; } ;
struct TYPE_37__ {int /*<<< orphan*/  dd_clones; int /*<<< orphan*/  dd_child_dir_zapobj; } ;
struct TYPE_36__ {int /*<<< orphan*/  sk_wkeys_lock; } ;
struct TYPE_35__ {TYPE_1__ spa_keystore; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  DSL_CRYPTO_KEY_ROOT_DDOBJ ; 
 int ENOENT ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  RW_WRITE_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 TYPE_5__* dmu_tx_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_crypto_key_sync (TYPE_8__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_hold_obj (TYPE_5__*,scalar_t__,int /*<<< orphan*/ ,TYPE_7__**) ; 
 int /*<<< orphan*/  dsl_dataset_rele (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int dsl_dir_get_encryption_root_ddobj (TYPE_6__*,scalar_t__*) ; 
 int /*<<< orphan*/  dsl_dir_hold_obj (TYPE_5__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_6__**) ; 
 scalar_t__ dsl_dir_is_clone (TYPE_6__*) ; 
 TYPE_24__* dsl_dir_phys (TYPE_6__*) ; 
 int /*<<< orphan*/  dsl_dir_rele (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_wrapping_key_hold (int /*<<< orphan*/ *,TYPE_8__*) ; 
 int /*<<< orphan*/  dsl_wrapping_key_rele (int /*<<< orphan*/ *,TYPE_8__*) ; 
 TYPE_3__* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (TYPE_3__*,int) ; 
 int /*<<< orphan*/  spa_keystore_dsl_key_hold_dd (TYPE_14__*,TYPE_6__*,int /*<<< orphan*/ ,TYPE_8__**) ; 
 int /*<<< orphan*/  spa_keystore_dsl_key_rele (TYPE_14__*,TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zap_cursor_advance (TYPE_3__*) ; 
 int /*<<< orphan*/  zap_cursor_fini (TYPE_3__*) ; 
 int /*<<< orphan*/  zap_cursor_init (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zap_cursor_retrieve (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  zap_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
spa_keystore_change_key_sync_impl(uint64_t rddobj, uint64_t ddobj,
    uint64_t new_rddobj, dsl_wrapping_key_t *wkey, boolean_t skip,
    dmu_tx_t *tx)
{
	int ret;
	zap_cursor_t *zc;
	zap_attribute_t *za;
	dsl_pool_t *dp = dmu_tx_pool(tx);
	dsl_dir_t *dd = NULL;
	dsl_crypto_key_t *dck = NULL;
	uint64_t curr_rddobj;

	ASSERT(RW_WRITE_HELD(&dp->dp_spa->spa_keystore.sk_wkeys_lock));

	/* hold the dd */
	VERIFY0(dsl_dir_hold_obj(dp, ddobj, NULL, FTAG, &dd));

	/* ignore special dsl dirs */
	if (dd->dd_myname[0] == '$' || dd->dd_myname[0] == '%') {
		dsl_dir_rele(dd, FTAG);
		return;
	}

	ret = dsl_dir_get_encryption_root_ddobj(dd, &curr_rddobj);
	VERIFY(ret == 0 || ret == ENOENT);

	/*
	 * Stop recursing if this dsl dir didn't inherit from the root
	 * or if this dd is a clone.
	 */
	if (ret == ENOENT ||
	    (!skip && (curr_rddobj != rddobj || dsl_dir_is_clone(dd)))) {
		dsl_dir_rele(dd, FTAG);
		return;
	}

	/*
	 * If we don't have a wrapping key just update the dck to reflect the
	 * new encryption root. Otherwise rewrap the entire dck and re-sync it
	 * to disk. If skip is set, we don't do any of this work.
	 */
	if (!skip) {
		if (wkey == NULL) {
			VERIFY0(zap_update(dp->dp_meta_objset,
			    dd->dd_crypto_obj,
			    DSL_CRYPTO_KEY_ROOT_DDOBJ, 8, 1,
			    &new_rddobj, tx));
		} else {
			VERIFY0(spa_keystore_dsl_key_hold_dd(dp->dp_spa, dd,
			    FTAG, &dck));
			dsl_wrapping_key_hold(wkey, dck);
			dsl_wrapping_key_rele(dck->dck_wkey, dck);
			dck->dck_wkey = wkey;
			dsl_crypto_key_sync(dck, tx);
			spa_keystore_dsl_key_rele(dp->dp_spa, dck, FTAG);
		}
	}

	zc = kmem_alloc(sizeof (zap_cursor_t), KM_SLEEP);
	za = kmem_alloc(sizeof (zap_attribute_t), KM_SLEEP);

	/* Recurse into all child dsl dirs. */
	for (zap_cursor_init(zc, dp->dp_meta_objset,
	    dsl_dir_phys(dd)->dd_child_dir_zapobj);
	    zap_cursor_retrieve(zc, za) == 0;
	    zap_cursor_advance(zc)) {
		spa_keystore_change_key_sync_impl(rddobj,
		    za->za_first_integer, new_rddobj, wkey, B_FALSE, tx);
	}
	zap_cursor_fini(zc);

	/*
	 * Recurse into all dsl dirs of clones. We utilize the skip parameter
	 * here so that we don't attempt to process the clones directly. This
	 * is because the clone and its origin share the same dck, which has
	 * already been updated.
	 */
	for (zap_cursor_init(zc, dp->dp_meta_objset,
	    dsl_dir_phys(dd)->dd_clones);
	    zap_cursor_retrieve(zc, za) == 0;
	    zap_cursor_advance(zc)) {
		dsl_dataset_t *clone;

		VERIFY0(dsl_dataset_hold_obj(dp, za->za_first_integer,
		    FTAG, &clone));
		spa_keystore_change_key_sync_impl(rddobj,
		    clone->ds_dir->dd_object, new_rddobj, wkey, B_TRUE, tx);
		dsl_dataset_rele(clone, FTAG);
	}
	zap_cursor_fini(zc);

	kmem_free(za, sizeof (zap_attribute_t));
	kmem_free(zc, sizeof (zap_cursor_t));

	dsl_dir_rele(dd, FTAG);
}