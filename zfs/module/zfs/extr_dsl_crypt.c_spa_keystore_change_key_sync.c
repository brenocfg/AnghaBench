#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_24__ {int /*<<< orphan*/  sk_wkeys_lock; int /*<<< orphan*/  sk_wkeys; } ;
struct TYPE_25__ {TYPE_1__ spa_keystore; } ;
typedef  TYPE_2__ spa_t ;
struct TYPE_26__ {int /*<<< orphan*/  skcka_dsname; TYPE_7__* skcka_cp; } ;
typedef  TYPE_3__ spa_keystore_change_key_args_t ;
struct TYPE_27__ {int /*<<< orphan*/  wk_refcnt; int /*<<< orphan*/  wk_ddobj; } ;
typedef  TYPE_4__ dsl_wrapping_key_t ;
struct TYPE_28__ {TYPE_2__* dp_spa; } ;
typedef  TYPE_5__ dsl_pool_t ;
struct TYPE_29__ {TYPE_9__* ds_dir; int /*<<< orphan*/  ds_is_snapshot; } ;
typedef  TYPE_6__ dsl_dataset_t ;
struct TYPE_30__ {char* cp_keylocation; scalar_t__ cp_cmd; TYPE_4__* cp_wkey; } ;
typedef  TYPE_7__ dsl_crypto_params_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  avl_index_t ;
struct TYPE_31__ {int /*<<< orphan*/  dd_object; struct TYPE_31__* dd_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ASSERT0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B_FALSE ; 
 scalar_t__ DCP_CMD_FORCE_INHERIT ; 
 scalar_t__ DCP_CMD_FORCE_NEW_KEY ; 
 scalar_t__ DCP_CMD_INHERIT ; 
 scalar_t__ DCP_CMD_NEW_KEY ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFS_PROP_KEYLOCATION ; 
 int /*<<< orphan*/  ZPROP_SRC_LOCAL ; 
 int /*<<< orphan*/  ZPROP_SRC_NONE ; 
 TYPE_4__* avl_find (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avl_insert (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avl_remove (int /*<<< orphan*/ *,TYPE_4__*) ; 
 TYPE_5__* dmu_tx_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_hold (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__**) ; 
 int /*<<< orphan*/  dsl_dataset_rele (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dir_get_encryption_root_ddobj (TYPE_9__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_prop_set_sync_impl (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_wrapping_key_free (TYPE_4__*) ; 
 int /*<<< orphan*/  dsl_wrapping_key_rele (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_keystore_change_key_sync_impl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_keystore_wkey_hold_dd (TYPE_2__*,TYPE_9__*,int /*<<< orphan*/ ,TYPE_4__**) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  zfs_prop_to_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_refcount_count (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
spa_keystore_change_key_sync(void *arg, dmu_tx_t *tx)
{
	dsl_dataset_t *ds;
	avl_index_t where;
	dsl_pool_t *dp = dmu_tx_pool(tx);
	spa_t *spa = dp->dp_spa;
	spa_keystore_change_key_args_t *skcka = arg;
	dsl_crypto_params_t *dcp = skcka->skcka_cp;
	dsl_wrapping_key_t *wkey = NULL, *found_wkey;
	dsl_wrapping_key_t wkey_search;
	char *keylocation = dcp->cp_keylocation;
	uint64_t rddobj, new_rddobj;

	/* create and initialize the wrapping key */
	VERIFY0(dsl_dataset_hold(dp, skcka->skcka_dsname, FTAG, &ds));
	ASSERT(!ds->ds_is_snapshot);

	if (dcp->cp_cmd == DCP_CMD_NEW_KEY ||
	    dcp->cp_cmd == DCP_CMD_FORCE_NEW_KEY) {
		/*
		 * We are changing to a new wkey. Set additional properties
		 * which can be sent along with this ioctl. Note that this
		 * command can set keylocation even if it can't normally be
		 * set via 'zfs set' due to a non-local keylocation.
		 */
		if (dcp->cp_cmd == DCP_CMD_NEW_KEY) {
			wkey = dcp->cp_wkey;
			wkey->wk_ddobj = ds->ds_dir->dd_object;
		} else {
			keylocation = "prompt";
		}

		if (keylocation != NULL) {
			dsl_prop_set_sync_impl(ds,
			    zfs_prop_to_name(ZFS_PROP_KEYLOCATION),
			    ZPROP_SRC_LOCAL, 1, strlen(keylocation) + 1,
			    keylocation, tx);
		}

		VERIFY0(dsl_dir_get_encryption_root_ddobj(ds->ds_dir, &rddobj));
		new_rddobj = ds->ds_dir->dd_object;
	} else {
		/*
		 * We are inheritting the parent's wkey. Unset any local
		 * keylocation and grab a reference to the wkey.
		 */
		if (dcp->cp_cmd == DCP_CMD_INHERIT) {
			VERIFY0(spa_keystore_wkey_hold_dd(spa,
			    ds->ds_dir->dd_parent, FTAG, &wkey));
		}

		dsl_prop_set_sync_impl(ds,
		    zfs_prop_to_name(ZFS_PROP_KEYLOCATION), ZPROP_SRC_NONE,
		    0, 0, NULL, tx);

		rddobj = ds->ds_dir->dd_object;
		VERIFY0(dsl_dir_get_encryption_root_ddobj(ds->ds_dir->dd_parent,
		    &new_rddobj));
	}

	if (wkey == NULL) {
		ASSERT(dcp->cp_cmd == DCP_CMD_FORCE_INHERIT ||
		    dcp->cp_cmd == DCP_CMD_FORCE_NEW_KEY);
	}

	rw_enter(&spa->spa_keystore.sk_wkeys_lock, RW_WRITER);

	/* recurse through all children and rewrap their keys */
	spa_keystore_change_key_sync_impl(rddobj, ds->ds_dir->dd_object,
	    new_rddobj, wkey, B_FALSE, tx);

	/*
	 * All references to the old wkey should be released now (if it
	 * existed). Replace the wrapping key.
	 */
	wkey_search.wk_ddobj = ds->ds_dir->dd_object;
	found_wkey = avl_find(&spa->spa_keystore.sk_wkeys, &wkey_search, NULL);
	if (found_wkey != NULL) {
		ASSERT0(zfs_refcount_count(&found_wkey->wk_refcnt));
		avl_remove(&spa->spa_keystore.sk_wkeys, found_wkey);
		dsl_wrapping_key_free(found_wkey);
	}

	if (dcp->cp_cmd == DCP_CMD_NEW_KEY) {
		avl_find(&spa->spa_keystore.sk_wkeys, wkey, &where);
		avl_insert(&spa->spa_keystore.sk_wkeys, wkey, where);
	} else if (wkey != NULL) {
		dsl_wrapping_key_rele(wkey, FTAG);
	}

	rw_exit(&spa->spa_keystore.sk_wkeys_lock);

	dsl_dataset_rele(ds, FTAG);
}